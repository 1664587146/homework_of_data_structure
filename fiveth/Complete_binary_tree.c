#include<stdio.h>
#include<stdlib.h>
#define     MaxQ 100//队列长度
//先这么大，不够再说，或者将前面的queue的做个.h
#define Node 2 ^ ( 10 ) - 1 + 1
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

static int sum = 0;//节点总数

int CreateArray(BiTree tree , int *help , int i)
{
	if (tree == 0) return (0);
    else
    {
        
        help[i] = 1;
        sum ++ ;
        CreateArray(tree ->lchild , help ,2 * i);
        CreateArray(tree ->rchild , help ,2 * i + 1);
        return (18);
    }  
}


int function(BiTree tree)
//看是非为完全二叉树
//用数组帮助，参考二叉树的线性存储
{
    int Help[Node]={0};//帮助（辅助）数组  
    int i = 1 , total = 0, state = 0;
    CreateArray(tree , Help , 1);
    for(i = 1; i <= sum ; i ++ )
    {
        if(Help[i] != 0)
        {
            total ++ ;
        }
        if(Help[i] == 0 && total != sum)
        {
            return (0);
        }
    }
    if(total == sum)
    {
    return (1);
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

//测试函数
int main()
{
	BiTree *tree = NULL,*c = 0;
	BiTNode *node = 0,*parent = 0;
	TElemType elem;
	InitBiTree(&tree);
    CreateTree(tree);
	printf("先序\n");
	PreOrderTraverse(*tree, visit);
    printf("判断是否为完全二叉树\n");
	if(function(*tree))
    {
        printf("是\n");
    }
    else
    {
        printf("不是\n");
    } 
	ClearBiTree(tree);
	system("pause");
	return (0);
}