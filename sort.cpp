/******************************************************
 *Some common sort algorithms
 ******************************************************/
#include<iostream>
using namespace std;
#define K 5

void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

/******************************************************************************
 *No.1 Insertion Sort
 *idea: put the current element of rest in the array into the correct position of the sorted part array each time.
 *insertSort is one kind of in-place sort, 
 *that is there are limited numbers outside the array which is sorted in the sorting process
 *******************************************************************************/
void insertSort(int a[],int size)
{
	int i,j;
	int temp;// 在每次循环前，记录当前要排序的元素，使其与已排序的元素进行比较，然后插入已排序数组的正确位置 
	for(i=1;i<size;i++)
	{
		temp=a[i];
		for(j=i-1;j>=0;j--)
		{
			if(temp<a[j])
			{
				a[j+1]=a[j];
			}
			else
				break;
		}
		a[j+1]=temp;
	}
}

/******************************************
 *No.2 Selection Sort
 *idea: select the max element or min element in the rest array each time, put it into the tail of the sorted part array. 
 *selectSort is one kind of in-place sort too
 ******************************************/
void selectSort(int a[],int size)
{
	int i,j;
	int min;
	int flag;
	for(i=0;i<size-1;i++)
	{
		min=a[i];
		for(j=i+1;j<size;j++)
		{
			if(min>a[j])
			{
				min=a[j];
				flag=j;//因为涉及到数组内元素交换，所以需要设置标志位，记录最小元素在数组内的位置
			}
		}
		if(min!=a[i])
			swap(&a[i],&a[flag]);
			//swap(&a[i],&min);
	}
}

/*************************************
 *No.3 Bubble Sort
 *idea: put one element in a correct position each loop, so you only need n-1 loops for n-element array.
 *bubbleSort is another in-place sort way
 *************************************/
void bubbleSort(int a[], int size)
{
	int i,j;

	for(i=0;i<size-1;i++)
	{
		for(j=size-1;j>i;j--)
		{
			if(a[j]<a[j-1])
				swap(&a[j],&a[j-1]);
		}
	}
}

/******************************************
 *No.4 QuickSort-Method one
 *idea: take advantage of divide and conquer and recursive method. 
 *partitionL is a function which can divide the array into two part, the number less than pivot,lie on the left, 
 *the number greater than pivot,lie on the right,
 *which is a subrouine of quickSort and then recursive call the same function
 *Both method one and method two j is greater than i initially, j-i=1,when loops, j is always equal or greater than i.
 **********************************************/
int partitionL(int a[],int left,int right)//right=K-1
{
	int i,j;
	int pivot=a[left];
	i=left;//i起标记作用，标记下一个被交换元素的前一位置
	for(j=left+1;j<=right;j++)//因为最左边的那个元素为轴，所以循环到right
	{
		if(a[j]<=pivot)
		{
			i++;
			if(i!=j)//加上此句只是为了避免自己与自己交换而浪费性能
			    swap(&a[i],&a[j]);	//如果条件成立，则交换
		}
	}
	swap(&a[i],&a[left]);
	return i;
}

void quickSortL(int a[],int left,int right)
{
	int pivot;
	if(left<right)
	{
		pivot=partitionL(a,left,right);
		quickSortL(a,left,pivot-1);
		quickSortL(a,pivot+1,right);
	}
}

/*******************************************************
 *No.4 QuickSort-Method two
 *partitionR is a function which can divide the array into two part, the number less than pivot,lie on the left, 
 *the number greater than pivot,lie on the right,
 *and then recursive call the same function
 ********************************************************/
int partitionR(int a[],int left,int right)//right=K-1
{
	int i,j;
	int pivot=a[right];
	i=left-1;
	for(j=left;j<=right-1;j++)//因为最右边的那个元素为轴，所以循环到right-1
	{
		if(a[j]<=pivot)
		{
			i++;
			if(i!=j)//加上此句只是为了避免自己与自己交换而浪费性能
			    swap(&a[i],&a[j]);
		}
	}
	swap(&a[i+1],&a[right]);
	return i+1;
}

void quickSortR(int a[],int left, int right)
{
	int pivot;
	if(left<right)
	{
		pivot=partitionR(a,left,right);
		quickSortR(a,left,pivot-1);
		quickSortR(a,pivot+1,right);
	}
}

/******************************************
 *No.4 QuickSort-Method three
 *quickSort,the mid number is pivot,but this routine is a little error!
 ******************************************/
int partition(int a[], int left, int right)
{
	int i,j;
	int mid=(left+right)/2;
	int pivot=a[mid];
	for(i=left,j=right;;)
	{
		if(a[i]<=pivot)
			i++;
		if(a[j]>pivot)
			j--;
		if(i>=j)
			break;
		if(a[i]>=pivot&&a[j]<=pivot&&i<j)
		{
			swap(&a[i],&a[j]);
			i++;
			j--;
		}
		if(i>=j)
			break;
	}
	return i;
}

void quickSort(int a[], int left, int right)
{
	int pivot;
	if(left<right)
	{
		pivot=partition(a,left,right);
		quickSort(a,left,pivot-1);
		quickSort(a,pivot+1,right);
	}
}

/**********************************************
 *No.5 MergeSort
 *idea: the same to Quick Sort, make use of divide and conquer and recursive method.
 *mergeSort
 **********************************************/
bool merge(int a[], int left, int mid, int right)
{	
	int i=left,j=mid+1;
	//int m=mid,n=right;
	int *tmp=new int[right+1];
	if(!tmp)
		return false;
	int k=0;
	while(i<=mid&&j<=right)
	{
		if(a[i]<=a[j])
			tmp[k++]=a[i++];
		else
			tmp[k++]=a[j++];
	}
	while(i<=mid)
		tmp[k++]=a[i++];
	while(j<=right)
		tmp[k++]=a[j++];
	//cout<<"test whether right==k?: "<<right<<"	"<<k<<endl;
	for(int t=0;t<k;t++)	//上限为k
		a[left+t]=tmp[t];
	delete[] tmp;
	return true;
}

void mergeSort(int a[], int left, int right)
{
	int q;
	if(left<right)
	{
		q=(left+right)/2;
		mergeSort(a,left,q);
		mergeSort(a,q+1,right);
		merge(a,left,q,right);//合并最后两个长度为n/2的有序数组
	}
}

/***************************************
 *No.5 MergeSort Method two
 ****************************************/
typedef int elem_t;
static void merge_v2(elem_t a[], elem_t tmp[], const int start, const int end)
{
	int i, j, k;
	int mid=(start+end)/2;
	for(i=0;i<end;i++)
		tmp[i]=a[i];
	for(i=start, j=mid, k=start;i<mid&&j<end;k++)
	{
		if(tmp[i]<tmp[j])
			a[k]=tmp[i++];
		else
			a[k]=tmp[j++];
	}
	while(i<mid)
		a[k++]=tmp[i++];
	while(j<end)
		a[k++]=tmp[j++];
}

void merge_sort(elem_t a[], elem_t tmp[], const int start, const int end)
{
	if(start<end-1)
	{
		const int mid=(start + end)/2;
		merge_sort(a,tmp,start,mid);
		merge_sort(a,tmp,mid,end);
		merge_v2(a,tmp,start,end);
	}
}

//将有二个有序数列a[first...mid]和a[mid+1...last]合并。
/*bool merge(int a[], int low, int mid, int high)
{
	int i = low, j = mid + 1;
	int m = mid, n = high;
	int k = 0;
	int *temp=new int[n+1];
	if(!temp)
		return false;
	
	while (i <= m && j <= n)
	{
		if (a[i] <= a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}
	
	while (i <= m)
		temp[k++] = a[i++];
	
	while (j <= n)
		temp[k++] = a[j++];
	
	for (i = 0; i < k; i++)	//上限为k,不要写成right+1
		a[low + i] = temp[i];
	delete[] temp;
	return true;
}
void mergeSort(int a[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;
		mergeSort(a, left, mid);    //左边有序
		mergeSort(a, mid + 1, right); //右边有序
		merge(a, left, mid, right); //再将二个有序数列合并
	}
}*/

/***************************************************
 *No.6 Heap Sort
 *idea: make use of the attribude of heap, that is root node is the min element or max element in heap or sub heap,also use the recursive method.
 *unstable sort method, fit to a lot of numbers.
 ***************************************************/
void heapAdjust(int *a,int i,int size)  //调整堆 
{
    int lchild=2*i+1;       //i的左孩子节点序号 
    int rchild=2*i+2;     //i的右孩子节点序号 
    int max=i;            //临时变量 
    if(i<=size/2)          //如果i是叶节点就不用进行调整,不是不调整叶节点，而是与其父节点进行调整；递归到非叶结点即可，因为叶节点无左右孩子节点 
    {
        if(lchild<=size&&a[lchild]>a[max])
        {
            max=lchild;
        }    
        if(rchild<=size&&a[rchild]>a[max])
        {
            max=rchild;
        }
        if(max!=i)
        {
            swap(a[i],a[max]);
            heapAdjust(a,max,size);    //避免调整之后以max为父节点的子树不是堆 
        }
    }        
}

void buildHeap(int *a,int size)    //建立堆 
{
    int i;
    for(i=size/2;i>=0;i--)    //非叶节点最大序号值为size/2 
    {
        heapAdjust(a,i,size);    
    }    
} 

void heapSort(int *a,int size)    //堆排序 
{
    int i;
    buildHeap(a,size);
    for(i=size-1;i>=0;i--)
    {
        //cout<<a[1]<<" ";
        swap(a[0],a[i]);           //交换堆顶和最后一个元素，即每次将剩余元素中的最大者放到最后面 
          //BuildHeap(a,i-1);        //将余下元素重新建立为大顶堆 
        heapAdjust(a,0,i-1);      //重新调整堆顶节点成为大顶堆
    }
} 

/*******************************************
 *No.7 Shell Sort
 *idea: That is an improved insertoin sort
 *******************************************/
void shellSort(int a[], int size)
{
	int gap;
	int tmp;
	int i,j,k;
	for(gap=size/2;gap>0;gap /=2)
	{
		for(j=gap;j<size;j +=gap)
		{
			tmp=a[j];
			for(k=j-gap;k>=0;k -= gap)
			{
				if(tmp<a[k])				
					a[k+gap]=a[k];
				else
					break;
			}
			a[k+gap]=tmp;
		}
	}
}

/******************************************************
 *No.8 counting Sort
 *idea: for each element in the array, such as x, we firstly find the number, elements less than x,
 *and then put x in a appropriate position of new output array.
 *Introduction to Algorithm P109 Chinese third edition
 ******************************************************/
void countingSort(int a[], int b[], int max_k, int n)
{
	int *c=new int[max_k+1];
	//int length_a=sizeof(a)/sizeof(int);//数组退化为指针，不能怎么求数组长度
	for(int i=0;i<=max_k;i++)
		c[i]=0;
	for(int j=0;j<n;j++)  
		c[a[j]]=c[a[j]]+1;
	for(int i=1;i<=max_k;i++)
		c[i]=c[i]+c[i-1];
	for(int j=n-1; j>=0;j--)
	{
		b[c[a[j]]-1]=a[j];//因为输出数组位置0，代表第一个元素，所以c[a[j]]-1
		c[a[j]]=c[a[j]]-1;
	}
}

/*Test Case*/
int main()
{
	int n;
	int b[K];
	int tmp[K]; //just for merge_sort() function
	printf("Please input %d numbers:",K);
	for(n=0;n<K;n++)
		scanf("%d",&b[n]);
	
	int ch;
	printf("Please choose one sort:\n");
	printf("1.insertSort\n2.selectSort\n3.bubbleSort\n4.quickSortR\n5.quickSortL\n6.quickSort \
	\n7.mergeSort\n8.heapSort\n9.shellSort\n10.mergeSort_v2\n11.countingSort\n");
	printf("Your choose is:");
	scanf("%d",&ch);
	switch(ch)
	{
	case 1: insertSort(b,K);
		break;
	case 2: selectSort(b,K); 
		break;
	case 3: bubbleSort(b,K);
		break;
	case 4: quickSortR(b,0,K-1);
		break;
	case 5: quickSortL(b,0,K-1);
		break;
	case 6: quickSort(b,0,K-1);
		break;
	case 7: mergeSort(b,0,K-1);
		break;
	case 8: heapSort(b,K);
		break;
	case 9: shellSort(b,K);
		break;
	case 10: merge_sort(b,tmp,0,K);
		break;
	case 11: 
		int max_k;
		cout<<"Please input the upper limit-the maximum integer: ";
		cin>>max_k;
		countingSort(b,tmp,max_k,K);
		break;
	default:
		break;
	}
	int m;
	if(ch!=11)
	{
		for(m=0;m<K;m++)
			printf("%d\t",b[m]);
		printf("\n");
	}
	else
	{
		for(m=0;m<K;m++)
			printf("%d\t",tmp[m]);
		printf("\n");
	}
	
	return 0;
}
