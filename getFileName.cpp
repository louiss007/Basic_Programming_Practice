#include<iostream>
#include<io.h>
#include<direct.h>
#include<string>
#include<vector>
#include<iomanip>
#include<ctime>
using   namespace   std;

void getFiles( string, vector<string>& );

int   main()
{   
    vector<string> files;
    char *path=new char[64];
    memset(path,0,64);
    cout<<"请输入文件路径： "<<endl;
    scanf("%s",path);
    getFiles(path, files);
    printf("%s包含的文件列表：\n",path);
    // print the files get
    for(int j=0; j<files.size(); ++j)
        cout<<files[j]<<endl;

    delete path;
    return   0;
}

void getFiles(string path, vector<string>& files)
{
    //文件句柄
    long handle_file = 0;
    //文件信息
    struct _finddata_t file_info;
    string p;
    if((handle_file = _findfirst(p.assign(path).append("\\*").c_str(),&file_info)) != -1)
    {
        while(_findnext(handle_file, &file_info) == 0)
        {
            //如果是目录,迭代之
            //如果不是,加入列表
            if ((file_info.attrib & _A_SUBDIR))
            {
                if(strcmp(file_info.name,".") != 0  &&  strcmp(file_info.name,"..") != 0)
                {
                    getFiles( p.assign(path).append("\\").append(file_info.name), files);
                    if(file_info.attrib!=_A_SUBDIR)
                        files.push_back(p.assign(path).append("\\").append(file_info.name));
                }
            }
            else
            {
                files.push_back(p.assign(path).append("\\").append(file_info.name));
            }
        }

        _findclose(handle_file);
    }
}