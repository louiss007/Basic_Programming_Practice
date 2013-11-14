/************************************************************
 * Some operations on Single List.
 ************************************************************/
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<conio.h>

using namespace std;

typedef struct ListNode
{
    int data;
	struct ListNode *next;
}Node;

/*注：只要链表不为空，对链表进行任何操作后，必须将head指向链表的第一个节点！！！*/
Node *creatList()
{
	Node *head,*p,*s;
	int x,cycle=1;
	head=(Node*)malloc(sizeof(Node));
	p=head;//利用指针p创建一个链表，所以初始时，应使p指向链表头结点
	while(cycle)
	{
		printf("please input the data:");
		scanf("%d",&x);
		if(x!=0)
		{
			s=(Node*)malloc(sizeof(Node));
			s->data=x;
			printf("%d\n",s->data);
			p->next=s;//使p的next指针指向当前所创建节点s上
			p=s;//然后将指针p向后移动到当前节点（即最末节点）上
		}
		else
			cycle=0;
	}
	head=head->next;//如果链表为空，则head-next=NULL,即链表只有一个head节点；否则使head指向链表的第一个节点，即head所指向的地址与链表的第一个元素指向的地址相同
	p->next=NULL;
	printf("yyy %d\n",head->data);
	return head;
}

int listLength(Node *head)
{
	int n=0;
	Node *p;
	p=head;
	while(p!=NULL)
	{
		p=p->next;
		n++;
	}
	return n;
}

Node *delNode(Node *head, int num)
{
	Node *p1,*p2;//声明两个指针
	p1=head;//使p1指向链表头部
	while(num!=p1->data&&p1->next!=NULL)
	{
		p2=p1;//即如果找到等于num的节点，则p1就是要删除的节点，此时p2指向p1的前一节点，所以删除时就让p2->next指向p1->next即可，p2记录p1当前位置
		p1=p1->next;
	}
	if(num==p1->data)
	{
		if(p1==head)//判断删除的是否为第一个节点（即也是head节点指向的节点）
		{
			head=p1->next;
			free(p1);
		}
		else
			p2->next=p1->next;
	}
	else
		printf("%d could not been found!\n",num);
	return head;
}

Node *insertNode(Node* head, int num)
{
	Node *p0,*p1,*p2;
	p1=head;
	p0=(Node*)malloc(sizeof(Node));//p0即要插入的那个节点，需要临时动态开辟空间
	p0->data=num;
	while(p0->data>p1->data&&p1->next!=NULL)
	{
		p2=p1;//记录p1当前遍历所在链表中的位置,以供插入时使用
		p1=p1->next;
	}
	if(p0->data<=p1->data)//因为上面循环可能是由于p1->next=NULL而终止的，所以此处需要进行判断一下
	{
		if(head==p1)//判断是否在头结点处插入
		{
			p0->next=p1;
			head=p0;
		}
		else
		{
			p2->next=p0;
			p0->next=p1;
		}
	}
	else
	{
		p1->next=p0;
		p0->next=NULL;
	}
	return head;
}

/*********************************************************************
 *链表排序思想：中心思想，即交换各个节点之间的数据以达到排序目的，
 *无需对链进行操作，例如断链，重组等，同时可结合数组排序相关算法
 **********************************************************************/
Node *sortList(Node *head)
{
	Node *p;
	int n;
	int temp;
	n=listLength(head);
	if(head==NULL||head->next==NULL)//判断空链表或者只有一个节点的链表，则直接返回，无需排序
		return head;
	p=head;
	for(int j=1;j<n;j++)//因为一次排序一个节点，所以循环n-1次，就可以
	{
		p=head;
		for(int i=0;i<n-j;++i)//循环到倒数第二节点就可以
		{
			if(p->data > p->next->data)
			{
				temp=p->data;
				p->data=p->next->data;
				p->next->data=temp;
			}
			p=p->next;
		}
	}
	return head;
}

/****************************************************************************
 *思想：每次两个节点之间逆置，然后将p1和p2向后平移，直到p2==NULL为止
 ****************************************************************************/
Node *reverseList(Node *head)
{
	Node *p1,*p2,*p3;
	if(head==NULL||head->next==NULL)//判断是否空链表或者一个节点的链表，成立则直接返回，无需逆置
		return head;
	p1=head;//初始时，p1指向链表的第一个节点（也即head节点）
	p2=p1->next;//p2指向p1的下一个节点
	while(p2)
	{
		p3=p2->next;//用p3记录p2指向的下一个节点
		p2->next=p1;
		p1=p2;//平移p1和p2指针，将p1移动到p2的位置，将p2移动到p3的位置上
		p2=p3;//可以与循环第一步合并，写为p2=p2->next;
	}
	head->next=NULL;//将新链表的最后一个节点即原链表的第一个节点的next置为NULL
	head=p1;//此时p1已指向新的链表的第一个节点，即原来链表的最后一个节点，所以将新链表的第一个节点赋值给head

	return head;
}

/*Node *reverseList(Node *head)
{
	if(head==NULL||head->next==NULL)
		return head;
	Node *p1=head;
	Node *p2=p1->next;
	Node *p3=p2->next;

	p1->next=NULL;
	while(p3!=NULL)
	{
		p2->next=p1;
		p1=p2;
		p2=p3;
		p3=p3->next;
	}
	p2->next=p1;
	head=p2;

	return head;
}*/

void printList(Node *head)
{
	Node *p;
	//int n;
	//n=listLength(head);
	//printf("Now, these %d records are:\n",n);
	p=head;
	if(head!=NULL)
		while(p!=NULL)
		{
			printf("uuu %d\n",p->data);
			p=p->next;
		}
		//printf("\n");
}
	
int main()
{
	Node *head;
	int length;
	head=creatList();
	length=listLength(head);
	printf("list length is %d\n",length);
	printList(head);
	int c;
	printf("you can do some actions on list:\n");
	printf("1.delete a node\n2.insert a node\n3.sort a list\n4.reverse a list\n");
	printf("Please make your choice:\n");
	/*注：使用说明，如果对链表执行了逆序操作后，则再对链表执行排序，插入和删除操作都将失效*/
	while((c=getchar())!='q')//getchar()返回的是整型，但需要用字符与之判断，case后的选项需要时字符型
	{
		//Node *new_head=(Node*)malloc(sizeof(Node));
		switch(c)
		{
		case '1':
			{
				//Node *new_head=(Node*)malloc(sizeof(Node));
				int num;
				printf("please input the deletion data:");
				scanf("%d",&num);
				delNode(head,num);
				printList(head);
				break;
			}
		case '2':
			{
				//new_head=(Node*)malloc(sizeof(Node));
				int num;
				printf("please input the insertion data:");
				scanf("%d",&num);
				insertNode(head,num);
				printList(head);
				break;
			}
		case '3':
			{
				//Node *new_head=(Node*)malloc(sizeof(Node));
				sortList(head);
				printList(head);
				break;
			}
		case '4':
			{
				Node *new_head=(Node*)malloc(sizeof(Node));
				new_head=reverseList(head);
				printList(new_head);
				break;
			}
		default:
			break;
		}
	}

	return 0;
}
