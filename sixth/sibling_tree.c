//建树直接使用二叉树的
#include<stdio.h>
#include<stdlib.h>
#define     MaxQ 100//队列长度
//先这么大，不够再说，或者将前面的queue的做个.h
typedef struct TElemType
{
	int data;//用int先表示
}TElemType;

typedef struct BiTNode
{
	TElemType data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;//无头结点

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
//递归 后序删除
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
	//创建树 左右孩子一起完成 所以如果data ==; 则表示空
	BiTNode* NewBase;
	NewBase = (BiTNode*)calloc(1, sizeof(BiTNode));
	//Using calloc ,so we don`t need to handle the child trees.
	TElemType root;
	printf("请输入数据: 如不想以;结尾\n");//一次一个
	scanf("%d", &root.data);
	if (getchar() != ';')
	{
		NewBase->data = root;
		*tree = NewBase;
		CreateTree(&((*tree)->lchild));//建左孩子
		CreateTree(&((*tree)->rchild));//右左孩子        
		//因为是先根处理所以一切输入要先根输入。
	} //else直接return
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
	if (printf("这个数据是:%d\n", e.data))
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
//i表示第几层
//用递归处理

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

//测试函数
int main()
{
	BiTree *tree = NULL;
	TElemType elem;
    int i;
	InitBiTree(&tree);
	CreateTree(tree);
    printf("请输入要第几层:,根是0层\n");
    scanf("%d",&i);
    Sibling_Traverse(*tree, i);
    ClearBiTree(tree);
	system("pause");
	return (0);
}