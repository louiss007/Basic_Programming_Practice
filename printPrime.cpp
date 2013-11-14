/*******************************************
 *糯米网笔试题第二题
 *print all the prime number less than n you input.
 *******************************************/
#include<iostream>
#include<cmath>
using namespace std;

void printPrime(int n)
{
	int i;
	int j;
	for(i=2;i<n;i++)
	{
		for(j=2;j<=(int)sqrt((double)i);j++)
		{
			if((i%j)==0)
				break;
		}
		if(j>(int)sqrt((double)i))
			cout<<i<<" ";
	}
}

int main()
{
	int n;
	cout<<"please input a number: ";
	cin>>n;
	printPrime(n);

	return 0;
}
