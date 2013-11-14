/************************************************************
 *Problem: Find Top K number in a given int array 
 *Implementation: Based on partition function, solve the problem
 *Time complexity: O(Kn) 
 ************************************************************/
#include<iostream>
using namespace std;

void swap(int *a, int *b)
{
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}

int partition(int *a,int left,int right)
{
	int pivot=a[left];
	int i=left;
	for(int j=left+1;j<=right;j++)
	{
		if(a[j]>=pivot)
		{
			i++;
			if(i!=j)
				swap(&a[i],&a[j]);
		}
	}
	swap(a[left],a[i]);
	return i;
}

void topK(int *a, int n, int *output, int k)
{
	if(a==NULL||output==NULL||k>n||n<=0||k<0)
		return ;
	int start=0;
	int end=n-1;
	int index=partition(a,start,end);
	while(index != k-1)
	{
		if(index>k-1)//discard the right part of array
		{
			end=index-1;
			index=partition(a,start,end);
		}
		else//discard the left part of array
		{
			start=index+1;
			index=partition(a,start,end);
		}
	}

	for(int i=0;i<k;i++)
		output[i]=a[i];
}

int main()
{
	int n;
	cin>>n;
	int *a=new int[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	int k;
	cin>>k;
	int *output=new int[k];
	topK(a,n,output,k);
	for(int i=0;i<k;i++)
		cout<<output[i]<<" ";
	cout<<endl;
	return 0;
}
