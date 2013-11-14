/*********************************************************
 *problem: put the character except letter onto the head of string, letter behind. 
 *But can not change the relative order between letters.
 *************************************************************/
#include <iostream>
#include<cstdio>
#include<cstring>

using namespace std;

void swap(char &a, char &b)
{
	char tmp=a;
	a=b;
	b=tmp;
}

void shiftString(char *str)
{
	int n=strlen(str);
	int i=n-1;
	int j=0;
	int index=i;
	for(;i>=0;)
	{
		if(str[i]=='*')
		{
			index=i;
			i--;
			j=i;
			while(j>=0)
			{
				if(str[j]!='*')
				{
					swap(str[j],str[index]);
					break;
				}
				else
					j--;
			}
		}
		else
			i--;
		
	}
}

int main() {
	int t;
	cout<<"please input the length of string:";
	cin>>t;
	//直接赋值的字符串属于const char*型，即字符串常量，所以不支持对该字符串的任何修改性动作，
	//包括再次对该变量赋值，交换字符串间的字符等操作,所以需要动态开辟一个字符串空间，以用来以上操作
	char *s=new char[t+1];
	memset(s,'\0',t+1);
	scanf("%s",s);
	shiftString(s);
	cout<<s<<endl;
	delete s;
	
	return 0;
}
