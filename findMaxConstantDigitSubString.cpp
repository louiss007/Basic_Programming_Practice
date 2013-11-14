/*************************************
 *20130918创新工场笔试题第三大题
 *寻找字符串中数字连续递增的最大子串
 **************************************/
#include<iostream>
#include<string.h>
#include<cctype>
using namespace std;

char* findMaxLong(char *s)
{
	int n=strlen(s);
	int max=0;
	int index=0;
	int count1=0;
	int count=0;
	int index2=0;
	for(int i=0;i<n;i++)
		if(isdigit(s[i]))
			count1++;
	if(count1==0)
		return "no digits!";

	for(int i=0;i<n;i++)
	{
		if(s[i]<='9'&&s[i]>='0')
		{
			index=i;
			count++;
			if(s[i+1]>='0'&&s[i+1]<='9'&&s[i+1]>s[i])
			{
				continue;
			}
			else
			{
				if(max<count)
				{
					max=count;
					index2=index-max+1;
				}
				count=0;
			}
		}
	}
	char *result=new char[max+1];//多开辟一个空间，字符串最后一位用‘0’结尾，防止产生乱码
	memset(result,0,max+1);
	for(int j=0;j<max;j++)
		result[j]=s[index2+j];
	return result;
}

int main()
{
	char s[]="ab345678AB456a12342567A8B9";
	char s1[]="abAAKLJ13AJFAOI";
	char *l=NULL;
	char *l1=NULL;
	l=findMaxLong(s);
	l1=findMaxLong(s1);
	cout<<l<<endl;
	cout<<l1<<endl;

	return 0;
}
