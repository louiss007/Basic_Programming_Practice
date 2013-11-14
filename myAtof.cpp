#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;

double myAtof(char *s)
{
	if(s==NULL)
	{
		cout<<"string is NULL."<<endl;
		exit(1);
		//return NULL;
	}
	int len=strlen(s);
	int inter=0;
	double floater=0.0;
	int i=0,j=len-1;
	while(s[i]!='.')
	{
		if(s[i]<='9'&&s[i]>='0')
		{
			inter=inter*10+s[i]-'0';
			i++;
		}
		else
		{
			cout<<"illegal string!"<<endl;
			exit(1);
			//return NULL;
		}
	}
	while(s[j]!='.')
	{
		if(s[j]<='9'&&s[j]>='0')
		{
			floater=floater/10+s[j]-'0';
			j--;
		}
		else
		{
			cout<<"illegal string!"<<endl;
			exit(1);
			//return NULL;
		}
	}
	double t=inter+floater/10;
	return t;
}

int main()
{
	int lenth;
	cin>>lenth;
	char *s=new char[lenth+1];
	memset(s,'0',lenth+1);
	cout<<"please input a string:";
	scanf("%s",s);
	double t=myAtof(s);
	cout<<t<<endl;
	delete[] s;

	return 0;
}
