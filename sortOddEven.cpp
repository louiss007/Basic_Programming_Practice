/****************************************************
 *问题：将一个数组中的偶数降序排序，奇数升序排序，但奇数和偶数原来所在数组中的位置不能串
 ******************************************************/
#include<iostream>
#include<cmath>
using namespace std;

void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void selectSort(int a[],int size)
{
	int i,j;
	int min,max;
	int flag,flah;
	for(i=0;i<size;i++)
	{
		if(abs(a[i])%2==1)
		{
			min=a[i];
			for(j=i+1;j<size;j++)
			{
				if(a[j]%2==1&&min>a[j])
				{
					min=a[j];
					flag=j;
				}
			}
			if(min!=a[i])
				swap(&a[i],&a[flag]);
		}
		else
		{
			max=a[i];
			for(j=i+1;j<size;j++)
			{
				if(a[j]%2==0&&max<a[j])
				{
					max=a[j];
					flah=j;
				}
			}
			if(max!=a[i])
				swap(&a[i],&a[flah]);
		}
	}
}

int main()
{
	int t;
	while(cin>>t)
	{
		for(int i=0;i<t;i++)
		{
			int n;
			cin>>n;
			int *a=new int[n];
			for(int j=0;j<n;j++)
				cin>>a[j];
			selectSort(a,n);
			cout<<"Case #"<<i+1<<":";
			for(int k=0;k<n;k++)
				cout<<a[k]<<" ";
			cout<<endl;
		}
	}
	return 0;
}
