#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;
#define SEC 5
//transfer char * to string, just assign char * to string; transfer string to char *, could use string.c_str() function

/*************************************************
 *source file:
 *我 在 这 不是 很 累 呀  (channel1_1214_12141062)
 *功夫 不负 苦心 人 祝贺 你 终于 成功 了  (channel1_1236_12361113)
 *target file:
 *我 在 这 不 是 很 累    (1214-12141062)
 *功 夫 不 负 苦 心 人 祝 贺 你 终 于 成 功       (1236-12361113)
 *************************************************/
int main()
{
    ifstream fin("input.txt");
	//ofstream fout;
	//fout.open("output.txt",std::ofstream::app|std::ofstream::binary);
	if(!fin.is_open())
	{
		printf("open file error!\n");
		fin.close();
		exit(1);
	}
	string line;
 
	int len;
	while(getline(fin,line,'\n'))
	{
		char *p[SEC];
		int ii=0;
		char *inner=NULL;
		char *buf=NULL;
		buf=(char *)line.c_str();
		while((p[ii]=strtok_s(buf,"\t",&inner))!=NULL)
		{
			buf=NULL;
			ii++;
		}
		string line1="";
		string line2="";
		string line2_rec="";
		line1=p[0];
		line2=p[1];
		int len2=line2.length();
		int pos=line2.find("_");
		line2_rec="("+line2.substr(pos+1,len2-pos-1);
		char *wav_line=new char[128];
		memset(wav_line,0,128);
		int len3=line2_rec.length();
		for(int w=0;w<len3;w++)
		{
			if(line2_rec.c_str()[w]=='_')
			wav_line[w]='-';
			else
			wav_line[w]=line2_rec.c_str()[w];
		}
		string line2_final="";
		line2_final=wav_line;
		len=line1.length();
		if(line1.c_str()!=NULL)
		{
			string line_new="";
			string res_line="";
			char *c_line=new char[1024];
			memset(c_line,0,1024);
			for(int i=0;i<len;)
			{
				if(line1.c_str()[i]==' ')
					i++;
				else
				{
					line_new+=line1.substr(i,2);
					i += 2;
				}
			}
			int len_new=line_new.length();
			for(int k=0,j=0;j<len_new-2;k +=3,j += 2)
			{
				c_line[k]=line_new.c_str()[j];
				c_line[k+1]=line_new.c_str()[j+1];
				c_line[k+2]=' ';
			}
			res_line=c_line;
			cout<<res_line<<'\t'<<line2_final<<endl;
			delete c_line;
		}
		else
		{
			fin.close();
			exit(1);
		}
		delete wav_line;
	}

	fin.close();
	return 0;
}