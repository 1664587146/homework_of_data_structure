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

int BiTreeEmpty(BiTree* tree)
{
	if (*tree == 0) return(4);
	else return (-4);
}

int BiTreeDepth(BiTree tree)
{
	int depth;
	if(tree == 0 )
	return (0);
	if (tree->lchild == 0 && tree->rchild == 0)
	{
		depth = 1;
	}
	else
	{
		if (BiTreeDepth(tree->lchild) >= BiTreeDepth(tree->rchild))
		{
			depth = BiTreeDepth(tree->lchild) + 1;
		}
		else
		{
			depth = BiTreeDepth(tree->rchild) + 1;
		}

	}
	return(depth);
}

int Root(BiTree tree)
{
	if (tree == 0) return(4);
	else return (tree->data.data);
}

int Value(BiTree tree, BiTNode *e)
{
	int i = 0;
	if (tree == e)
		i = tree ->data.data;
	else
	{
		if (Value(tree->lchild, e))
			i = Value(tree->lchild, e);
		else if (Value(tree->rchild, e))
			i = Value(tree->rchild, e);
		else i = 0;
	}
	return i;
}
//i == 0 û��e

int Assign(BiTree tree, BiTNode* node, TElemType value)
//ʵ����Ӧʹ��ָ��
{
	if (&tree == 0 || node == 0)
	{
		return (0);
	}
	else
	{
		if (tree == node)
		{
			tree->data = value;
		}
		else if (tree->lchild)
		{
			Assign(tree->lchild, node, value);
		}
		else if (tree->rchild)
		{
			Assign(tree->rchild, node, value);
		}
	}
	return (5);
}

BiTNode* Parent(BiTree tree, BiTNode e)
{
	BiTNode* node = 0;
	//data�ĵȺ�Ӧ�к�������
	if (tree == 0 || &e == 0 || tree->data.data == e.data.data) { return(0); }
	if (tree->lchild->data.data == e.data.data)
	{
		node = tree->lchild;
	}
	else if (tree->rchild->data.data == e.data.data)
	{
		node = tree->rchild;
	}
	else if (tree->lchild)
	{
		node = Parent(tree->lchild, e);
	}
	else if (tree->rchild)
	{
		node = Parent(tree->rchild, e);
	}
	return(node);
}

BiTree LeftChild(BiTree tree, BiTNode* node)
{
	BiTree lchild = 0;
	if (tree == 0 || node == 0) return (0);
	else
	{
		if (tree == node)
		{
			lchild = tree->lchild;
		}
		else
		{
			if (LeftChild(tree->lchild, node))
				lchild = LeftChild(tree->lchild, node);
			if (LeftChild(tree->rchild, node))
				lchild = LeftChild(tree->rchild, node);
		}
	}
	return (lchild);
}

BiTree RightChild(BiTree tree, BiTNode* node)
{
	BiTree rchild = 0;
	if (tree == 0 || node == 0) return (0);
	else
	{
		if (tree == node)
		{
			rchild = tree->rchild;
		}
		else
		{
			if (RightChild(tree->lchild, node))
				rchild = RightChild(tree->lchild, node);
			if (RightChild(tree->rchild, node))
				rchild = RightChild(tree->rchild, node);
		}
	}
	return (rchild);
}

BiTree LeftSibling(BiTree tree, BiTNode* node)
{
	BiTree LSibling = 0;
	BiTNode* parent;
	if (tree == 0 || node == 0 || tree == node);
	else
	{
		parent = Parent(tree, *node);
		if (parent->rchild == node)
		{
			if (parent->lchild)
				LSibling = parent->lchild;
		}
	}
	return (LSibling);
}

BiTree RightSibling(BiTree tree, BiTNode* node)
{
	BiTree RSibling = 0;
	BiTNode* parent;
	if (tree == 0 || node == 0 || tree == node);
	else
	{
		parent = Parent(tree, *node);
		if (parent->lchild == node)
		{
			if (parent->rchild)
				RSibling = parent->rchild;
		}
	}
	return (RSibling);
}

int InsertChild(BiTree tree, BiTNode* parent, int LR, BiTree c)
//��0��1
{
	BiTree child;
	if (tree == 0 || parent == 0 || c == 0) return 0;
	else
	{
		if (LR == 0)
		{
			child = parent->lchild;
			parent->lchild = c;
			c->rchild = child;
		}
		else
		{
			child = parent->rchild;
			parent->rchild = c;
			c->rchild = child;
		}
	}
	return (6);
}

int DeleteChild(BiTree tree, BiTNode* parent, int LR)//LRӦ��bool�� ��cû��������int
//��0��1
{
	if (tree == 0 || parent == 0) return (0);
	else
	{
		if (LR == 0)
		{
			ClearBiTree(&(parent->lchild));
		}
		else
		{
			ClearBiTree(&(parent->rchild));
		}

	}
	return (7);
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

int InOrderTraverse(BiTree tree, int (*visit)(TElemType))
{
	if (tree == 0) return 0;
	else
	{
		InOrderTraverse(tree->lchild, visit);
		visit(tree->data);
		InOrderTraverse(tree->rchild, visit);
		return (9);
	}
}

int PostOrderTraverse(BiTree tree, int (*visit)(TElemType))
{
	if (tree == 0) return 0;
	else
	{
		PostOrderTraverse(tree->lchild, visit);
		PostOrderTraverse(tree->rchild, visit);
		visit(tree->data);
		return (10);
	}
}



int LevelOrderTraverse(BiTree tree, int (*visit)(TElemType))
//��Ҫ���и���
{

	BiTNode *queue[MaxQ] = { 0 };
	int front = 0, rear = 0;
	if (tree == 0) return(0);
	visit(tree->data);
	if (tree->lchild)
	{
		queue[rear] = tree->lchild;
		rear = (rear + 1) % MaxQ;
	}
	if (tree->rchild)
	{
		queue[rear] = tree->rchild;
		rear = (rear + 1) % MaxQ;
	}
	while (rear != front)
	{
		visit(queue[front]->data);
		if (queue[front]->lchild)
		{
			queue[rear] = queue[front]->lchild;
			rear = (rear + 1) % MaxQ;
		}
		if (queue[front]->rchild)
		{
			queue[rear] = queue[front]->rchild;
			rear = (rear + 1) % MaxQ;
		}
		front = (front + 1) % MaxQ;
	}
}

//���Ժ���
int main()
{
	BiTree *tree = NULL,*c = 0;
	BiTNode *node = 0,*parent = 0;
	TElemType elem;
	InitBiTree(&tree);
	printf("%d\n", BiTreeEmpty(tree));
	CreateTree(tree);
	printf("Depth��%d\n", BiTreeDepth(*tree));
	printf("Root:%d\n",Root(*tree));
	printf("����\n");
	PreOrderTraverse(*tree, visit);
	printf("����\n");
	InOrderTraverse(*tree, visit);
	printf("����\n");
	PostOrderTraverse(*tree, visit);
	printf("����\n");
	LevelOrderTraverse(*tree, visit);
	printf("\n");
	node = (*tree) -> lchild;
	printf("�����node��tree���������ĸ���value:%d\n",Value(*tree,node));
	elem.data = 100;
	printf("���ｫ��������node��ֵ100��%d\n",Assign(*tree,node,elem));
	PreOrderTraverse(*tree, visit);
	printf("����ǰ�����\n");
	PreOrderTraverse(LeftChild(*tree,node), visit);
	printf("�Һ���ǰ�����\n");
	PreOrderTraverse(RightChild(*tree,node), visit);
	printf("parent\n");
	parent = Parent(*tree,*node);
	printf("parent`s data:%d",parent -> data . data);
	printf("���ֵ�ǰ�����\n");
	PreOrderTraverse(LeftSibling(*tree,node),visit);
	node = (*tree) -> rchild;
	printf("�����node��tree���������ĸ�,��������������ֵ�\n");
	printf("���¶�Ҫ�������������");
	PreOrderTraverse(LeftSibling(*tree,node),visit);
	printf("��c��" );
	InitBiTree(&c);
	CreateTree(c);
	printf("��������node\n" );
	InsertChild(*tree,node,1,*c);
	PreOrderTraverse(*tree, visit);
	printf("ɾ������node��������\n" );
	DeleteChild(*tree,node,1);
	PreOrderTraverse(*tree, visit);
	ClearBiTree(tree);
	printf("%d\n", BiTreeEmpty(tree));
	system("pause");
	return (0);
}