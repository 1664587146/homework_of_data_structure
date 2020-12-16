#include<stdio.h>
#include<stdlib.h>
 
//定义一个树的结构体
typedef struct BiTNode
{
	int data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;
 
//函数声明
void CreateBST(BiTree* T, int a[], int n);
void outputBST(BiTree T);
int InsertBST(BiTree* T, int key);
int DeleteBST(BiTree*T,int key);
int Delete(BiTree *p);
 
//二叉排序树的查找函数定义
int SearchBST(BiTree T,int key,BiTree f,BiTree *p)
{
	if (!T)
	{
		*p = f;
		return (0);
	}
	else if (key==T->data)
	{
		*p = T;
		return (1);
	}
	else if (key<T->data)
	{
		return SearchBST(T->lchild,key,T,p);
	}
	else
	{
		return SearchBST(T->rchild,key,T,p);
	}
}
 
//二叉排序树的插入函数定义
int InsertBST(BiTree *T,int key)
{
	BiTree p=NULL, s=NULL;
	if (!SearchBST(*T,key,NULL,&p))
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if (!p)
			* T = s;
		else if (key < p->data)
			p->lchild = s;
		else
			p->rchild = s;
		return (1);
	}
	return (0);
}
 
//二叉排序树的删除操作函数定义
int DeleteBST(BiTree* T, int key)
{
	if (!*T)
		return (0);
	else
	{
		if (key == (*T)->data)
		{
			return Delete(T);
		}
		else if (key<(*T)->data)
		{
			return DeleteBST(&(*T)->lchild,key);
		}
		else
		{
			return DeleteBST(&(*T)->rchild,key);
		}
	}
}
 
//根据节点的三种情况来删除节点
int Delete(BiTree* p)
{
	BiTree q, s;
	if ((*p)->rchild==NULL)
	{
		q = *p; *p = (*p)->lchild; free(q);
	}
	else if ((*p)->lchild==NULL)
	{
		q = *p; *p = (*p)->rchild; free(q);
	}
	else
	{
		q = *p; s = (*p)->lchild;
		while (s->rchild)
		{
			q = s; s = s->rchild;
		}
		(*p)->data = s->data;
		if (q != *p)
			q->rchild = s->lchild;
		else
			q->lchild = s->lchild;
		free(s);
	}
	return (1);
}
 
//通过一个数组来创建二叉排序树
void CreateBST(BiTree*T, int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		InsertBST(T, a[i]);
	}
}
 
//把一个二叉排序树中序遍历打印
void outputBST(BiTree T)
{
	if (T == NULL)
	{
		return;
	}
	outputBST(T->lchild);
	printf(" %d ",T->data);
	outputBST(T->rchild);
}
 
//主函数
int main()
{
	int a[] = { 62,88,58,47,35,73,51,99,37,93 };
	BiTree T = NULL;
	//创建二叉排序树
	CreateBST(&T, a, 10);
	printf("建树:\n");
	outputBST(T);
	printf("\n");
	//在二叉排序树中插入95
	InsertBST(&T, 95);
	printf("插入95：\n");
	outputBST(T);
	printf("\n");
	//在二叉排序树中查找节点
	int b = 95;
	BiTree p = NULL;
	if (!SearchBST(T, b, NULL, &p))
		printf("没有找到\n");
	else
	{
		printf("%d查找结果的指针为0x%x\n",b , p);
	}
	//在二叉排序树中删除88节点
	printf("输出88:\n");
	DeleteBST(&T, 88);
	//验证上述的插入和删除操作
	outputBST(T);
	printf("\n");
	system("pause");
 	free(T);
	return 0;
}
