/*************************************************
 *常考面试题之重建二叉树
 *根据前序遍历序列和中序遍历序列，重新构建二叉树
 *参考资料：剑指offer P55
 *注：要想重建二叉树，必须给出中序遍历序列
 *************************************************/
#include<iostream>
using namespace std;

class BinTreeNode
{
public:
	friend BinTreeNode *construct(int *preorder, int *inorder, int length);
	friend BinTreeNode *constructCore(int *startPreorder, int *endPreorder,
		int *startInorder, int *endInorder);
	friend void preorderPrint(BinTreeNode *root);
	friend void inorderPrint(BinTreeNode *root);
	friend void postorderPrint(BinTreeNode *root);

	BinTreeNode()
	{
		m_pLeft=m_pRight=NULL;
	}
	//BinTreeNode(int value, BinTreeNode *pLeft, BinTreeNode *pRight)
	//{
	//	new_node=new BinTreeNode();
	//	new_node->m_nValue=0;
	//	new_node->m_pLeft=NULL;
	//	new_node->m_pRight=NULL;
	//}
	//~BinTreeNode()
	//{
	//	delete new_node;
	//}
private:
	BinTreeNode *new_node;
	int m_nValue;
	BinTreeNode *m_pLeft;
	BinTreeNode *m_pRight;
};

BinTreeNode *construct(int *preorder, int *inorder, int length)
{
	if(preorder==NULL||inorder==NULL||length<=0)
		return NULL;

	return constructCore(preorder, preorder+length-1,inorder, inorder+length-1);
}

BinTreeNode *constructCore(int *startPreorder, int *endPreorder,
		int *startInorder, int *endInorder)
{
	//
	int rootValue=startPreorder[0];
	BinTreeNode *root=new BinTreeNode();
	root->m_nValue=rootValue;

	if(startPreorder==endPreorder)
	{
		if(startInorder==endInorder&&*startPreorder==*startInorder)
			return root;
		else
			throw std::exception("Invalid input.");
	}

	//
	int *rootInorder=startInorder;
	while(rootInorder<=endInorder&&*rootInorder != rootValue)
		++rootInorder;

	if(rootInorder==endInorder && *rootInorder != rootValue)
		throw std::exception("Invalid input.");

	int leftLength=rootInorder-startInorder;
	int *leftPreorderEnd=startPreorder+leftLength;
	if(leftLength>0)
		//construct left sub tree.
		root->m_pLeft=constructCore(startPreorder+1,leftPreorderEnd, startInorder,rootInorder-1);
	if(leftLength<endPreorder-startPreorder)
		//construct right sub tree.
		root->m_pRight=constructCore(leftPreorderEnd+1,endPreorder,rootInorder+1,endInorder);

	return root;
}

//前序遍历
void preorderPrint(BinTreeNode *root)
{
	if(root!=NULL)
	{
		cout<<root->m_nValue<<" ";
		preorderPrint(root->m_pLeft);
		preorderPrint(root->m_pRight);
	}
}

//中序遍历
void inorderPrint(BinTreeNode *root)
{
	if(root!=NULL)
	{
		inorderPrint(root->m_pLeft);
		cout<<root->m_nValue<<" ";
		inorderPrint(root->m_pRight);
	}
}

//后续遍历
void postorderPrint(BinTreeNode *root)
{
	if(root!=NULL)
	{		
		postorderPrint(root->m_pLeft);
		postorderPrint(root->m_pRight);
		cout<<root->m_nValue<<" ";
	}
}

int main()
{
	int seq1[]={1,2,4,7,3,5,6,8};
	int seq2[]={4,7,2,1,5,3,8,6};
	int length=sizeof(seq1)/sizeof(int);
	BinTreeNode *root=new BinTreeNode();
	root=construct(seq1,seq2,length);
	//preorderPrint(root);
	postorderPrint(root);
	cout<<endl;

	delete root;

	return 0;
}

/***************************************************
 *                   1
 *                2     3
 *              4     5   6
 *                7      8
 * ************************************************/
