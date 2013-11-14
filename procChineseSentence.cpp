#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;

//transfer char * to string, just assign char * to string; transfer string to char *, could use string.c_str() function
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
        len=line.length();
        if(line.c_str()!=NULL)
        {
            string line_new="";
            string res_line="";
            char *c_line=new char[1024];
            memset(c_line,0,1024);
            for(int i=0;i<len;)
            {
                if(line.c_str()[i]==' ')
                    i++;
                else
                {
                    line_new+=line.substr(i,2);
                    i += 2;
                }
            }
            int len_new=line_new.length();
            for(int k=0,j=0;j<len_new;k +=3,j += 2)
            {
                c_line[k]=line_new.c_str()[j];
                c_line[k+1]=line_new.c_str()[j+1];
                c_line[k+2]=' ';
            }
            res_line=c_line;
            cout<<res_line<<endl;
            delete c_line;
        }
        else
        {
            fin.close();
            exit(1);
        }
    }
    
    fin.close();
    return 0;
}