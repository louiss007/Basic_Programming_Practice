/**********************************************************
 *String Match Algorithm
 *KMP Algorithm
 *Introduction to Algorithm P1005
 ***********************************************************/
#include<iostream>
#include<cstring>
using namespace std;

int *computePrefixFunction(const char *p)//*p="ABCDABD"
{
	int m=strlen(p);
	int *pi=new int[m];//记录已匹配模式串子串的自己匹配自己的前缀开始位置 such as ABCDAB position is 4th.
	pi[0]=0;
	int k=0;
	for(int q=1;q<m;q++)
	{
		while(k>0&&p[k]!=p[q])
			k=pi[k];
		if(p[k]==p[q])
			k++;
		pi[q]=k;
	}
	return pi;
}

void kmpMatch(const char *t, const char *p, int *pi)
{
	int n=strlen(t);
	int m=strlen(p);
	//因为在一个函数中，无法直接调用（使用）另一个函数返回的结果，所以将其写进形参中，利用主函数得到另一个函数的结果，然后将其再传递给函数中
	//pi=computePrefixFunction(p);
	int q=0;
	int i;
	for(i=0;i<n;i++)// traverse the text string t
	{
		while(q>0&&p[q]!=t[i]) //此步意在模拟下一个字符匹配失败时，模式串移动的位移量，以及在已经匹配前缀的基础上，继续匹配
			q=pi[q-1];           
		if(p[q]==t[i])
			q++;
		
		if(q==m)
		{
			cout<<i-m+1<<endl;
			//cout<<t[i-m+1]<<endl;
			q=pi[q-1];	
		}
	}
}

int main()
{
	char *t="BBC ABCDAB ABCDABCDABDE";
	char *p="ABCDABD";//pi[]={0,0,0,0,1,2,0}

	int *pi=computePrefixFunction(p);
	kmpMatch(t,p,pi);

	return 0;
}
