#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100 //初始地址大小
#define STACKINCREMENT 10//增量
//定义 如果栈空错误 ，就返回0
//自定义用户数据类 （先内含int栈示
//递归和层次遍历在binary上，已写所以主要负责非层次
//树的几个

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

int DestoryTree(BiTree* tree)
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

//要用栈 

typedef struct
{
	BiTree data;
}SElemType;

typedef struct SqStack
{
	SElemType* top;
	SElemType* base;
	int StackSize;
}SqStack;

int InitStack(SqStack* stack)
{
	//if(stack != 0) free(stack);
	SElemType* newbase;
	newbase = (SElemType*)(malloc(STACK_INIT_SIZE * sizeof(SElemType)));
	if (!newbase) exit(0);//系统错误，直接退出
	else
	{
		stack->base = newbase;
		stack->top = newbase;
		stack->StackSize = STACK_INIT_SIZE;
		return 1;
	}
}//创建栈 成功一
//空栈 ：top = base + 1

int DestroyStack(SqStack* stack)
{
	if (stack == 0) return(0);
	else
	{
		free(stack->base);
		stack->base = stack->top = 0;
		stack->StackSize = 0;
		return 2;
	}
	return -2;
}//销毁栈 成功2 未知失败 -2

int ClearStack(SqStack* stack)
{
	if (stack == 0) return(0);
	else
	{
		stack->top = stack->base;
		return 3;
	}
	return -3;
}//清空栈 成功3 未知失败 -3

int StackEmpty(SqStack stack)
{
	if (&stack == 0) return(0);
	if (stack.base == stack.top) return 4;
	else { return -4; }
}//判断栈空 4空 -4不空

int StackLength(SqStack stack)
{
	if (&stack == 0) return(0);
	return (stack.top - stack.base);
}//栈长 返回长度

int GetTop(SqStack stack, SElemType* elem)
{
	if (&stack == 0) return(0);
	if (elem->data = (stack.top - 1)->data)
	{
		return (5);
	}
	else
	{
		return (-5);
	}
}//得栈头 成功5 失败-5

int Push(SqStack* stack, SElemType e)
{
	if (&stack == 0) return(0);
	if (stack->base == stack->top)
	{
		if ((stack->base)->data = e.data)
		{
			stack->top++;
			return 6;
		}
	}
	if (((stack->top)->data = e.data) || e.data == NULL)
	{
		stack->top++;
		return 6;
	}
	else
	{
		return -6;
	}
}//入栈 成功6 失败-6

int Pop(SqStack* stack, SElemType* elem)
{
	if (&stack == 0) return(0);
	if (elem->data = (((stack->top)--) - 1)->data)
	{
		return (7);
	}
	else
	{
		return (-7);
	}
}//删除栈头 成功7 失败-7

int visit(TElemType e)
{
	if (printf("这个数据是:%d\n", e.data))
		return (1);
	else return (0);
}

//先序遍历
//x先向左，遇到节点就输出，然后对右子树一样
int PreOrderTraverse(BiTree tree, int (*visit)(TElemType))
{
	SqStack s;
	SElemType elem, elem1;
	elem.data = tree;
	InitStack(&s);
	Push(&s, elem);
	while (StackEmpty(s) == -4)
	{
		while (GetTop(s, &elem) && elem.data)//getTop  就输出 
		{
			if (!visit(elem.data->data)) return(0);
			elem1.data = elem.data->lchild;
			Push(&s, elem1);
		}
		Pop(&s, &elem);//pop叶节点
		if (StackEmpty(s) == -4)
		{
			Pop(&s, &elem);
			elem1.data = elem.data->rchild;
			Push(&s, elem1);
		}
	}
	DestroyStack(&s);
	return(11);
}

//中序遍历
int InOrderTraverse(BiTree tree, int (*visit)(TElemType))
{
	SqStack s;
	SElemType elem, elem1;
	elem.data = tree;
	InitStack(&s);
	Push(&s, elem);
	while (StackEmpty(s) == -4)
	{
		while (GetTop(s, &elem) && elem.data)
		{
			elem1.data = elem.data->lchild;
			Push(&s, elem1);
		}
		Pop(&s, &elem);
		if (StackEmpty(s) == -4)
		{
			Pop(&s, &elem);
			if (!visit(elem.data->data)) return(0);
			if (elem.data->rchild)
				elem1.data = elem.data->rchild;
			Push(&s, elem1);
		}
	}
	DestroyStack(&s);
	return(12);
}

//后序遍历
//x先向左，然后对右子树处理完输出根，
// 后序遍历
int PostOrderTraverse(BiTree tree, int (*visit)(TElemType))
{
	if (tree == NULL)
		return 0;
	SqStack s;
	InitStack(&s);
	//pCur:当前访问节点，pLastVisit:上次访问节点
	SElemType pCur, pLastVisit,baige;

	pCur.data = tree;
	pLastVisit.data = NULL;
	//先把pCur移动到左子树最下边
	while (pCur.data)
	{
		Push(&s, pCur);
		pCur.data = pCur.data->lchild;
	}
	while (StackEmpty(s) == -4)
	{
		//走到这里，pCur都是空，并已经遍历到左子树底端(看成扩充二叉树，则空，亦是某棵树的左孩子)
		GetTop(s, &pCur);
		Pop(&s, &pCur);
		//一个根节点被访问的前提是：无右子树或右子树已被访问过
		if (pCur.data != NULL && (pCur.data->rchild == NULL || pCur.data->rchild == pLastVisit.data))
		{
			visit(pCur.data->data);
			//修改最近被访问的节点
			pLastVisit.data = pCur.data;
		}
		if(pCur . data -> lchild == pLastVisit.data || (!pCur.data->lchild) && pCur.data != pLastVisit.data)
		{
            //上面或后面的正则表达式分别叶子节点和只有右子树的树
			//根节点再次入栈
			//进入右子树，且可肯定右子树一定不为空
			//下面要排除叶节点
			Push(&s, pCur);
			if (pCur.data)//如果不是叶节点
			{
				pCur.data = pCur.data->rchild;
			}
			while (pCur.data)
			{
				Push(&s, pCur);
				pCur.data = pCur.data->lchild;
			}
		}
	}
	DestroyStack(&s);
	return(13);
}

int main()
{
	BiTree* tree = NULL, * c = 0;
	BiTNode* node = 0, * parent = 0;
	TElemType elem;
	InitBiTree(&tree);
	CreateTree(tree);
	printf("先序\n");
	PreOrderTraverse(*tree, visit);
	printf("中序\n");
	InOrderTraverse(*tree, visit);
	printf("后序\n");
	PostOrderTraverse(*tree, visit);
	DestoryTree(tree);
	system("pause");
	return (0);
}



