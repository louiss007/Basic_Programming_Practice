#include<iostream>
#include<stdio.h>
#include<string.h>
#include<conio.h>

using namespace std;

typedef struct student
{
    int data;
	struct student *next;
	struct student *pre;
}dNode;

dNode *creatDoubleList()
{
	dNode *head,*p,*s;
	int x,cycle=1;
	head=(dNode*)malloc(sizeof(dNode));
	p=head;
	while(cycle)
	{
		printf("please input the data:");
		scanf("%d",&x);
		if(x!=0)
		{
			s=(dNode*)malloc(sizeof(dNode));
			s->data=x;
			printf("%d\n",s->data);
			p->next=s;
			s->pre=p;
			p=s;
		}
		else
			cycle=0;
	}
	head=head->next;
	head->pre=NULL;
	p->next=NULL;
	printf("yyy %d\n",head->data);
	return head;
}

int dListLength(dNode *head)
{
	int n=0;
	dNode *p;
	p=head;
	while(p)
	{
		n++;
		p=p->next;
	}
	return n;
}

dNode* delDNode(dNode *head, int num)
{
	dNode *p1,*p2;
	//p2=new student();
	p1=head;
	while(p1->data!=num&&p1->next!=NULL)
	{
		p2=p1;
		p1=p1->next;
	}
	if(p1->data==num)
	{
		if(p1==head)
		{
			head=head->next;
			head->pre=NULL;
			free(p1);
		}
		else if(p1->next==NULL)
		{
			p1->pre->next=NULL;
			free(p1);
		}
		else
		{
			p2->next=p1->next;
			p1->next->pre=p2;
			/*声明一个变量的时候用下面方法*/
	/*		p1->next->pre=p1->pre;
			p1->pre->next=p1->next;*/
		}
	}
	else
		printf("%d could not been found!\n",num);
	return head;
}

dNode* insertDNode(dNode *head, int num)
{
	dNode *p0,*p1;
	p1=head;
	p0=(dNode*)malloc(sizeof(dNode));
	p0->data=num;
	while(p0->data > p1->data&&p1->next!=NULL)
		p1=p1->next;
	if(p0->data<=p1->data)
	{
		if(p1==head)
		{
			p0->next=p1;
			p1->pre=p0;
			head=p0;
		}
		else
		{
			p0->next=p1;
			p1->pre->next=p0;
			p0->pre=p1->pre;
			p1->pre=p0;
		}
	}
	else
	{
		p1->next=p0;
		p0->pre=p1;
		p0->next=NULL;
	}
	return head;
}

void printDList(dNode *head)
{
	dNode *p;
	int n=dListLength(head);
	p=head;
	printf("Now, there are %d records:\n",n);
	if(head!=NULL)
		while(p!=NULL)
		{
			printf("uuu %d\n",p->data);
			p=p->next;
		}
}

int main()
{
	dNode *head;
	int num1,num2;
	head=creatDoubleList();
	printDList(head);
	printf("please input your deletion number:");
	scanf("%d",&num1);
	delDNode(head,num1);
	printDList(head);
	printf("please input your insertion number:");
	scanf("%d",&num2);
	insertDNode(head,num2);
	printDList(head);

	return 0;
}