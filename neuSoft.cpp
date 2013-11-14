/***********************
 *This problem is very intresting.
 ************************/
#include<iostream>
using namespace std;

int main()
{
	int *p;
	int a[10]={0};
	p=a;
	*(p+11)=5;
	cout<<p[11]<<endl;
	return 0;
}