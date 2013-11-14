/*******************************************
 *implement stack with array
 *参考资料： 大话数据结构 P92
 ******************************************/
#include<iostream>
#define MAXSIZE 100
using namespace std;

typedef int SElemType;

typedef struct
{
	SElemType data[MAXSIZE];
	int top;
}sqStack;

bool push(sqStack *s, SElemType e)
{
	bool flag=false;
	if(s->top==MAXSIZE-1)
	{
		cout<< "stack is full"<<endl;
		return flag;
	}
	s->top++;
	s->data[s->top]=e;
	flag=true;
	return flag;
}

bool pop(sqStack *s, SElemType *e)
{
	bool flag=false;
	if(s->top==-1)
	{
		cout<<"stack is empty"<<endl;
		return flag;
	}
	*e=s->data[s->top];
	s->top--;
	return flag;
}

int main()
{
	sqStack *s=new sqStack();//错误声明方式 sqStack *s=NULL;
	s->top=-1;
	int i;
	for(i=0;i<10;i++)
		push(s,i);
	cout<<"*****************push stack***************"<<endl;
	for(i=0;i<10;i++)
		cout<<s->data[i]<<" ";
	cout<<endl;
	cout<<"*****************pop stack****************"<<endl;
	int *e=new int[10];
	for(i=0;i<10;i++)
		pop(s,&e[i]);
	for(int j=0;j<10;j++)
		cout<<e[j]<<" ";
	cout<<endl;

	delete s;
	delete[] e;

	return 0;
}
