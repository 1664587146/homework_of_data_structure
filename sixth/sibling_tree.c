//����ֱ��ʹ�ö�������
#include<stdio.h>
#include<stdlib.h>
#define     MaxQ 100//���г���
//����ô�󣬲�����˵�����߽�ǰ���queue������.h
typedef struct TElemType
{
	int data;//��int�ȱ�ʾ
}TElemType;

typedef struct BiTNode
{
	TElemType data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;//��ͷ���

int InitBiTree(BiTree* (*tree))
{
	BiTree* NewBase = (BiTree*)malloc(sizeof(BiTree));
	if (NewBase)
	{
		*NewBase = 0;
		*tree = NewBase;
		return (1);
	}
	else
	{
		exit(0);
	}

}

int DestoryTree(BiTree *tree)
//�ݹ� ����ɾ��
{
	if (*tree == 0)
	{
		return (2);
	}
	else
	{
		DestoryTree(&((*tree)->lchild));
		DestoryTree(&((*tree)->rchild));
		free(*tree);
		*tree = NULL;
		return (2);
	}
}

int CreateTree(BiTree* tree)
{
	//������ ���Һ���һ����� �������data ==; ���ʾ��
	BiTNode* NewBase;
	NewBase = (BiTNode*)calloc(1, sizeof(BiTNode));
	//Using calloc ,so we don`t need to handle the child trees.
	TElemType root;
	printf("����������: �粻����;��β\n");//һ��һ��
	scanf("%d", &root.data);
	if (getchar() != ';')
	{
		NewBase->data = root;
		*tree = NewBase;
		CreateTree(&((*tree)->lchild));//������
		CreateTree(&((*tree)->rchild));//������        
		//��Ϊ���ȸ���������һ������Ҫ�ȸ����롣
	} //elseֱ��return
	return (2);
}

int ClearBiTree(BiTree* tree)
{
	if (tree == 0) return (3);
	else
	{
		if ((*tree)->lchild)
			ClearBiTree(&((*tree)->lchild));
		if ((*tree)->rchild)
			ClearBiTree(&((*tree)->rchild));
		free(*tree);
		*tree = 0;

		return(3);
	}
}

int visit(TElemType e)
{
	if (printf("���������:%d\n", e.data))
		return (1);
	else return (0);
}

int PreOrderTraverse(BiTree tree, int (*visit)(TElemType))
{
	if (tree == 0) return 0;
	else
	{
		visit(tree->data);
		PreOrderTraverse(tree->lchild, visit);
		PreOrderTraverse(tree->rchild, visit);
		return (8);
	}
}

int Sibling_Traverse(BiTree tree,int i)
//i��ʾ�ڼ���
//�õݹ鴦��

{
    int j ; 
    BiTNode *node;
    for (node = tree , j = 0; j != i; j++)
    {
        if(node -> rchild)
        {
            Sibling_Traverse(node -> rchild ,i - j);
        }
        node = node -> lchild;
    }
    if( j == i)
        PreOrderTraverse(node,visit);
    return 1;
}//

//���Ժ���
int main()
{
	BiTree *tree = NULL;
	TElemType elem;
    int i;
	InitBiTree(&tree);
	CreateTree(tree);
    printf("������Ҫ�ڼ���:,����0��\n");
    scanf("%d",&i);
    Sibling_Traverse(*tree, i);
    ClearBiTree(tree);
	system("pause");
	return (0);
}