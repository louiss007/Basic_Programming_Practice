#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <Windows.h>
#include <time.h> /*louis@20130805*/
#include "qisr.h"

using namespace std;

#define MSP_REC_STATUS_SPEECH_COMPLETE 0x05

#ifdef _WIN64
#pragma comment(lib,"./Release/msc_x64.lib")//x64
#else
#pragma comment(lib,"./Release/msc.lib")//x86
#endif

#define END_RECOG(reason) \
{ \
    ret=QISRSessionEnd(session_id,#reason); \
	if(MSP_SUCCESS!=ret) \
	{ \
	printf("QISRSessionEnd failed, error code is %d",ret); \
	} \
	\
	ret=QISRFini(); \
	if(MSP_SUCCESS!=ret) \
	{ \
	printf("QISRFini failed, error code is %d",ret); \
	} \
}

#define BLOCK_LEN 5*1024

/*wav音频文件格式数据结构*/
struct wav_struct
{
	unsigned long file_size; //文件大小
	unsigned short channel;  //通道数
	unsigned long frequency; //采样频率
	unsigned long Bps;   //Byte率
	unsigned short sample_num_bit; //一个样本的位数
	unsigned long data_size; //数据大小
	unsigned char *data;  //音频数据 ,这里要定义什么就看样本位数了，我这里只是单纯的复制数据
};

int main(int argc, char* argv[])
{
	const char* configs=NULL;
	const char* session_id=NULL;
	const char* recog_params=NULL;
	char recog_audio[BLOCK_LEN];
	//FILE* f_speech=NULL;
	int audio_status=0;
	int ep_status=0;
	int rec_status=0;
	int rslt_status=0;
	int count=0; //计算识别音频的数量
	double sum_speech_time=0; //所有音频文件的时间长度之和
	double sum_entry_time=0; //识别所有音频文件所花费的时间
	double sum_speech_rate;
	const char* rec_result;
	unsigned int audio_len=0;
	int ret=MSP_SUCCESS;

	printf(
	"==============================================================\n"
	"      Mobile Speech Platform 2.0 Client SDK Demo for IAT      \n"
	"==============================================================\n"
	);
	ofstream fout;
	fout.open("errorFile.txt",std::ofstream::out | std::ofstream::app); //识别失败的文件的输出文件louiss@20130808
	/*初始化*/
	configs="server_url=dev.voicecloud.cn/index.htm,coding_libs=speex.dll,vad_enable=true,appid=xxxxxxxx";
	ret=QISRInit(configs);
	if(MSP_SUCCESS!=ret)
	{
		printf("QISRInit failed, error code is %d\n",ret);
		return -1;
	}

	/*打开用来进行识别的语音文件，用户可以采用其他的获取音频的方式，比如实时采集音频*/
	char* file_list = argv[1];
	ifstream fs(file_list);
	if(!fs.is_open())
	{
		printf("%s can not open",file_list);
		fs.close();
		exit(1);
	}
	string line;
	while(getline(fs,line,'\n'))
	{
	/*注：一路会话只能进行一次识别或听写*/
	/*开始一路会话*/
	recog_params="ssm=1,sub=iat,aue=speex-wb;7,auf=audio/L16;rate=16000, \
		ent=sms16k,rst=plain,vad_speech_tail=1500";
	session_id=QISRSessionBegin(NULL,recog_params,&ret);
	if(MSP_SUCCESS!=ret)
	{
		printf("QISRSessionBegin failed, error code is %d\n",ret);
		return -1;
	}
	FILE *f_speech=NULL; //语音文件指针
	f_speech=fopen(line.c_str(),"rb");
	if(NULL==f_speech)
	{
		printf("Can not open file %s \n",line.c_str()); //去掉路径
		END_RECOG(open file);
		return -1;
	}
	//printf("DONE0\n");
	printf("%s\t",line.c_str());
	//fout<<line.c_str()<<'\t';

	audio_status = 0;
	ep_status=0;
	rec_status=0;
	rslt_status=0;

	/*计算识别时间*/
	double speech_rate; //实时识别率
	clock_t start,finish;
	double entry_time;
	start=clock();

	/*发送音频数据，获取语音听写结果*/
	while(MSP_AUDIO_SAMPLE_LAST!=audio_status)
	{
		audio_len=fread(recog_audio,1,BLOCK_LEN,f_speech);
		audio_status=(audio_len==BLOCK_LEN)? \
		MSP_AUDIO_SAMPLE_CONTINUE:MSP_AUDIO_SAMPLE_LAST;
		ret=QISRAudioWrite(session_id,recog_audio,audio_len, \
		audio_status,&ep_status,&rslt_status);
		if(MSP_SUCCESS!=ret)
		{
			printf("QISRSAudioWrite failed, error code is %d\n",ret);
			fout<<line.c_str()<<endl;
			rslt_status=MSP_REC_STATUS_SPEECH_COMPLETE;
			break;
		}
		//printf("write audio data ok!len=%d,status=%d\n",audio_len,audio_status);
  
		/*已经有结果缓存在MSC中了，可以获取了*/
		if(MSP_REC_STATUS_SUCCESS==rslt_status)
		{
		rec_result=QISRGetResult(session_id,&rslt_status,5000,&ret);
		if(MSP_SUCCESS!=ret)
		{
			printf("QISRGetResult failed, error code is %d\n",ret);
			fout<<line.c_str()<<endl; //识别失败的文件写入另一个文件列表
			//fout.write(line.c_str(),strlen(line.c_str()));
			rslt_status=MSP_REC_STATUS_SPEECH_COMPLETE;
			break;
		}

		if(NULL!=rec_result)
		{
			//printf("got a result:%s\n",rec_result);
			printf("%s ",rec_result);
			//fout<<rec_result;
		}

		/*全部结果已经获取完了*/
		if(MSP_REC_STATUS_SPEECH_COMPLETE==rslt_status)
		{
			//printf("the result has been got completely!\n");
			break;
		}
		}

		/*检查到音频后端点，结束音频发送*/
		if(MSP_EP_AFTER_SPEECH == ep_status)
		{
		//printf("end point of speech has been detected!\n");
		break;
		}

		Sleep(160);
		}
		fclose(f_speech);

		//printf("DONE1\n");

		/*获取余下的识别结果*/
		while(MSP_REC_STATUS_SPEECH_COMPLETE!=rslt_status)
		{
			rec_result=QISRGetResult(session_id,&rslt_status,5000,&ret);
			if(MSP_SUCCESS!=ret)
			{
				printf("QISRGetResult failed, error code is:%d\n",ret);
				fout<<line.c_str()<<endl;
				break;
			}

			if(NULL!=rec_result)
			{
				//printf("got a result:%s\n",rec_result);
				printf("%s\t",rec_result);
				//fout<<rec_result<<'\t';
			}

			/*sleep一下很有必要，防止MSC端无缓存的识别结果时浪费CPU资源*/
			Sleep(200);
		}
		finish=clock();
		entry_time=(double)(finish-start)/CLOCKS_PER_SEC;
		sum_entry_time += entry_time;

		/*计算音频实际时间长度*/
		double f_speech_time;
		wav_struct WAV;
		fstream fs_t;
		fs_t.open(line.c_str(),ios::binary|ios::in);

		//fs_t.seekg(0,ios::end);        //用c++常用方法获得文件大小
		//WAV.file_size=fs.tellg();

		fs_t.seekg(0x14);
		fs_t.read((char*)&WAV.channel,sizeof(WAV.channel));

		fs_t.seekg(0x18);
		fs_t.read((char*)&WAV.frequency,sizeof(WAV.frequency));

		//fs_t.seekg(0x1c);
		//fs_t.read((char*)&WAV.Bps,sizeof(WAV.Bps));

		fs_t.seekg(0x22);
		fs_t.read((char*)&WAV.sample_num_bit,sizeof(WAV.sample_num_bit));

		fs_t.seekg(0x28);
		fs_t.read((char*)&WAV.data_size,sizeof(WAV.data_size));

		//WAV.data=new unsigned char[WAV.data_size];

		//fs_t.seekg(0x2c);
		//fs_t.read((char *)WAV.data,sizeof(char)*WAV.data_size);

		f_speech_time=(double)WAV.data_size*8/(WAV.frequency*WAV.sample_num_bit*WAV.channel); //音频文件实际时间长度
		fs_t.close();
		sum_speech_time += f_speech_time;
		speech_rate=f_speech_time/entry_time;
		printf("%lf",speech_rate);
		//fout<<speech_rate<<endl;
		printf("\n");

		//printf("DONE2\n");
 
		/*结束会话，释放资源*/
		ret=QISRSessionEnd(session_id,"normal end");
		if(NULL==f_speech)
		{
			printf("QISRSessionEnd failed, error code is %d\n",ret);

		}

		count++;
	}
	sum_speech_rate=(double)sum_speech_time/sum_entry_time;
	printf("**************************************\n");
	//fout<<"**************************************"<<endl;
	printf("识别的音频文件个数：%d\n",count);
	//fout<<"识别的音频文件个数："<<count<<endl;
	printf("总平均实时识别率：%lf\n",sum_speech_rate);
	//fout<<"总平均实时识别率："<<sum_speech_rate<<endl;
	printf("**************************************\n");
	//fout<<"**************************************"<<endl;
	session_id=NULL; 
	ret=QISRFini();
	if(MSP_SUCCESS!=ret)
	{
		printf("QISRFini failed, error code is %d\n",ret);
	}

	fs.close();
	fout.close();
	return 0;
}

 