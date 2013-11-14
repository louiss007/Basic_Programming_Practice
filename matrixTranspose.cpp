#include<iostream>
#include<cstring>
using namespace std;

/************************************************************
 *matrixTranspose(): implement the transpose of matrix.
 *m is number of row of original matrix, n is number of  column of original matrix
 ************************************************************/
void matrixTranspose(int **matrixA, int m, int n, int **matrixB)
{
	int *tmp=new int[m*n+1];
	memset(tmp,0,m*n+1);
	int k=0;
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			tmp[k++]=matrixA[i][j];
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			matrixB[i][j]=tmp[i+j*n];
}

int main()
{
	int m,n;
	cout<<"please input m and n:";
	cin>>m>>n;
	int **A=new int *[m];
	int **B=new int *[n];
	for(int i=0;i<m;i++)
		A[i]=new int[n];
	for(int i=0;i<n;i++)
		B[i]=new int[m];
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			cin>>A[i][j];
	matrixTranspose(A,m,n,B);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			cout<<B[i][j]<<" ";
		cout<<endl;
	}

	return 0;
}
