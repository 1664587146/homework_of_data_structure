#include<stdio.h>
#include<stdlib.h>
 
//����һ�����Ľṹ��
typedef struct BiTNode
{
	int data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;
 
//��������
void CreateBST(BiTree* T, int a[], int n);
void outputBST(BiTree T);
int InsertBST(BiTree* T, int key);
int DeleteBST(BiTree*T,int key);
int Delete(BiTree *p);
 
//�����������Ĳ��Һ�������
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
 
//�����������Ĳ��뺯������
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
 
//������������ɾ��������������
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
 
//���ݽڵ�����������ɾ���ڵ�
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
 
//ͨ��һ����������������������
void CreateBST(BiTree*T, int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		InsertBST(T, a[i]);
	}
}
 
//��һ���������������������ӡ
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
 
//������
int main()
{
	int a[] = { 62,88,58,47,35,73,51,99,37,93 };
	BiTree T = NULL;
	//��������������
	CreateBST(&T, a, 10);
	printf("����:\n");
	outputBST(T);
	printf("\n");
	//�ڶ����������в���95
	InsertBST(&T, 95);
	printf("����95��\n");
	outputBST(T);
	printf("\n");
	//�ڶ����������в��ҽڵ�
	int b = 95;
	BiTree p = NULL;
	if (!SearchBST(T, b, NULL, &p))
		printf("û���ҵ�\n");
	else
	{
		printf("%d���ҽ����ָ��Ϊ0x%x\n",b , p);
	}
	//�ڶ�����������ɾ��88�ڵ�
	printf("���88:\n");
	DeleteBST(&T, 88);
	//��֤�����Ĳ����ɾ������
	outputBST(T);
	printf("\n");
	system("pause");
 	free(T);
	return 0;
}
