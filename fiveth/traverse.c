#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100 //��ʼ��ַ��С
#define STACKINCREMENT 10//����
//���� ���ջ�մ��� ���ͷ���0
//�Զ����û������� �����ں�intջʾ
//�ݹ�Ͳ�α�����binary�ϣ���д������Ҫ����ǲ��
//���ļ���

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

int DestoryTree(BiTree* tree)
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

//Ҫ��ջ 

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
	if (!newbase) exit(0);//ϵͳ����ֱ���˳�
	else
	{
		stack->base = newbase;
		stack->top = newbase;
		stack->StackSize = STACK_INIT_SIZE;
		return 1;
	}
}//����ջ �ɹ�һ
//��ջ ��top = base + 1

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
}//����ջ �ɹ�2 δ֪ʧ�� -2

int ClearStack(SqStack* stack)
{
	if (stack == 0) return(0);
	else
	{
		stack->top = stack->base;
		return 3;
	}
	return -3;
}//���ջ �ɹ�3 δ֪ʧ�� -3

int StackEmpty(SqStack stack)
{
	if (&stack == 0) return(0);
	if (stack.base == stack.top) return 4;
	else { return -4; }
}//�ж�ջ�� 4�� -4����

int StackLength(SqStack stack)
{
	if (&stack == 0) return(0);
	return (stack.top - stack.base);
}//ջ�� ���س���

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
}//��ջͷ �ɹ�5 ʧ��-5

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
}//��ջ �ɹ�6 ʧ��-6

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
}//ɾ��ջͷ �ɹ�7 ʧ��-7

int visit(TElemType e)
{
	if (printf("���������:%d\n", e.data))
		return (1);
	else return (0);
}

//�������
//x�����������ڵ�������Ȼ���������һ��
int PreOrderTraverse(BiTree tree, int (*visit)(TElemType))
{
	SqStack s;
	SElemType elem, elem1;
	elem.data = tree;
	InitStack(&s);
	Push(&s, elem);
	while (StackEmpty(s) == -4)
	{
		while (GetTop(s, &elem) && elem.data)//getTop  ����� 
		{
			if (!visit(elem.data->data)) return(0);
			elem1.data = elem.data->lchild;
			Push(&s, elem1);
		}
		Pop(&s, &elem);//popҶ�ڵ�
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

//�������
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

//�������
//x������Ȼ����������������������
// �������
int PostOrderTraverse(BiTree tree, int (*visit)(TElemType))
{
	if (tree == NULL)
		return 0;
	SqStack s;
	InitStack(&s);
	//pCur:��ǰ���ʽڵ㣬pLastVisit:�ϴη��ʽڵ�
	SElemType pCur, pLastVisit,baige;

	pCur.data = tree;
	pLastVisit.data = NULL;
	//�Ȱ�pCur�ƶ������������±�
	while (pCur.data)
	{
		Push(&s, pCur);
		pCur.data = pCur.data->lchild;
	}
	while (StackEmpty(s) == -4)
	{
		//�ߵ����pCur���ǿգ����Ѿ��������������׶�(�����������������գ�����ĳ����������)
		GetTop(s, &pCur);
		Pop(&s, &pCur);
		//һ�����ڵ㱻���ʵ�ǰ���ǣ������������������ѱ����ʹ�
		if (pCur.data != NULL && (pCur.data->rchild == NULL || pCur.data->rchild == pLastVisit.data))
		{
			visit(pCur.data->data);
			//�޸���������ʵĽڵ�
			pLastVisit.data = pCur.data;
		}
		if(pCur . data -> lchild == pLastVisit.data || (!pCur.data->lchild) && pCur.data != pLastVisit.data)
		{
            //���������������ʽ�ֱ�Ҷ�ӽڵ��ֻ������������
			//���ڵ��ٴ���ջ
			//�������������ҿɿ϶�������һ����Ϊ��
			//����Ҫ�ų�Ҷ�ڵ�
			Push(&s, pCur);
			if (pCur.data)//�������Ҷ�ڵ�
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
	printf("����\n");
	PreOrderTraverse(*tree, visit);
	printf("����\n");
	InOrderTraverse(*tree, visit);
	printf("����\n");
	PostOrderTraverse(*tree, visit);
	DestoryTree(tree);
	system("pause");
	return (0);
}



