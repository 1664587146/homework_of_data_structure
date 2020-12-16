/*
    21、【4】平衡二叉树操作的演示（选做） （查找）
    [问题描述]
    利用平衡二叉树实现一个动态查找表。
    [基本要求]
    （1） 实现动态查找表的三种基本功能：查找、插入和删除。
    （2） 题目详情见习题册P168 6.4。
*/

#include<stdio.h>  
#include<stdlib.h> 
//左子树比右子树高一
#define LH 1
//左子树和右子树一样高
#define EH 0
//左子树比右子树低一
#define RH -1
#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a) < (b))
#define LQ(a,b)((a) <= (b))
#define true 1
#define false 0


typedef struct BSTNode
{
	int data;
	int bf;
	BSTNode * lchild;
	BSTNode * rchild;
}BSTNode;
typedef BSTNode * BSTree;
 
//	左旋
void leftRotate(BSTree *root) 
{
	BSTree rc = (*root) -> rchild;
	(*root) -> rchild = rc -> lchild;
	rc -> lchild = *root;
	*root = rc;
}

//	右旋
void rightRotate(BSTree *root) 
{
	BSTree lc = (*root) -> lchild;
	(*root) -> lchild = lc -> rchild;
	lc -> rchild = *root;
	*root = lc;
}

//	对二叉树root进行左平衡处理(LL型和LR型)
void leftBalance(BSTree *root) 
{
	BSTree lc = (*root) -> lchild;
	switch (lc -> bf) 
	{
		//LL型的只需要进行右旋操作
	case LH:
		//右旋之后根和左子树都的平衡的
		(*root) -> bf = EH;
		lc -> bf = EH;
		//右旋操作
		rightRotate(root);
		break;
		//LR型的需要进行左旋操作，然后右旋操作
	case RH:
		BSTree rc = lc->rchild;
		switch (rc->bf) 
		{
		case LH:
			(*root) ->bf = RH;
			lc -> bf = EH;
			break;
		case EH:
			(*root) -> bf = EH;
			lc -> bf = EH;
			break;
		case RH:
			(*root) -> bf = EH;
			lc -> bf = LH;
			break;
		}
		rc -> bf = EH;
		leftRotate(&((*root) -> lchild));
		rightRotate(root);
		break;
	}
}

//	功能：对二叉树root进行左平衡处理(RR型和RL型)
void rightBalance(BSTree *root) 
{
	BSTree rc = (*root) ->rchild;
	switch (rc->bf) 
	{
		//RR型只需要做左旋操作
	case RH:
		(*root) -> bf = EH;
		rc ->bf = EH;
		//左旋操作
		leftRotate(root);
		break;
		//RL型需要先做右旋操作，然后做左旋操作
	case LH:
		BSTree lc = rc->lchild;
		switch (lc->bf) 
		{
		case LH:
			(*root) ->bf = EH;
			rc->bf = RH;
			break;
		case EH:
			(*root)->bf = EH;
			rc->bf = EH;
			break;
		case RH:
			(*root)->bf = LH;
			rc->bf = EH;
			break;
		}
		lc->bf = EH;
		rightRotate(&((*root)->rchild));
		leftRotate(root);
		break;
	}
}

//	功能：把元素data插入平衡二叉树root中
int  insert(BSTree (*root), int data, int  *taller) 
{
	if (NULL == *root) 
	{
		(*root) = (BSTree)malloc(sizeof(BSTNode));
		(*root)->rchild = NULL;
		(*root)->lchild = NULL;
		(*root)->data = data;
		(*root)->bf = EH;
		*taller = true;
	}
	else
	{
		//该元素已经在平衡二叉树中存在了
		if (data == (*root) ->data) 
		{
			taller = false;
			return false;
		}
		//插入左子树
		else if (data < (*root) ->data) 
		{
			if (!insert(&(*root) ->lchild, data, taller)) 
			{
				return false;
			}
			//插入成功，并且树变高了
			if (taller) 
			{
				switch ((*root)->bf) 
				{
				case LH:
					leftBalance(root);
					//平衡二叉树做完左平衡操作后
					//树高没有变化，故taller = false
					*taller = false;
					break;
				case EH:
					(*root)->bf = LH;
					//原来是平衡的故插入一个元素后
					//树高必然变高
					*taller = true;
					break;
				case RH:
					(*root)->bf = EH;
					//原来是右子树比左子树高，但是当向左子树中
					//插入一个元素的时候，树变平衡了，故taller = false
					*taller = false;
					break;
				default:
					break;
				}
			}
		}
		//插入右子树
		else 
		{
			if (!insert(&((*root)->rchild), data, taller)) 
			{
				return 0;
			}
			if (taller) 
			{
				switch ((*root)->bf) 
				{
				case LH:
					(*root)->bf = EH;
					*taller = false;
					break;
				case EH:
					(*root)->bf = RH;
					*taller = true;
					break;
				case RH:
					rightBalance(root);
					*taller = false;
					break;
				}
			}
		}
	}
	return true;
}
//   在平衡二叉树中查找int节点
int* search(BSTree root, int data) 
{
	if (root ==NULL) 
	{
		return NULL;
	}
	
	if (root->data == data) 
	{
		return &root->data;
	}
	else if (data < root->data) 
	{
		return search(root->lchild, data);
	} 
	else 
	{
		return search(root->rchild, data);
	}
}
//	功能：输出平衡二叉树中的所有的元素（小->大，中序遍历）
void print(BSTree root)
{
	if (NULL == root) 
	{
		return ;
	}
	
	print(root->lchild);
	printf("%d ",root->data);
	print(root->rchild);
}
//	功能：释放平衡二叉树的空间
void clear(BSTree *root) 
{
	if (NULL == *root) 
	{
		return ;
	}
	if ((*root)->lchild)
	{
		clear(&((*root)->lchild));
	}
	if ((*root)->rchild)
	{
		clear(&((*root)->rchild));
	}
	free((*root));
}
int DeleteAVL(BSTree *T, int key, int *shorter){
	if (!T)
	{//No such key
		*shorter = false;
		return 0;
	}

	else
	{
		if(!*T)
		{
			printf("没有这个数据\n");
			return(0);
		}
		if (EQ(key, (*T)->data))	//找到了需要删除的结点
		{
			//如果该结点的lchild 和
			//rchild 至少有一个为NULL
			//则大功告成，否则请参照
			//下方解释
			BSTree q = (*T);
			if (!(*T)->lchild)//如果该结点的lchild 为NULL
			{
				q = (*T);
				(*T) = (*T)->rchild;
				free(q);
				*shorter = true;
				return 1;
			}
			else if (!(*T)->rchild)
            {//如果该结点的rchild 为 NULL
				q = (*T);
				(*T) = (*T)->lchild;
				free(q);
				*shorter = true;
				return 1;
			}
			else 
            {
				//删除一个左右孩子都不为空的结点
				//使该结点的直接前驱p的data替换该结点的data
				//然后改变key=p.data
				BSTree s = (*T) ->lchild;
				while (s->rchild)
					s = s->rchild;
				(*T)->data = s->data;
				key = s->data;//Now, delete the vertice whose data was the new key
			}
		}
		if (LQ(key, (*T)->data))
        {//这里与InsertAVL不同
			if (!DeleteAVL(&((*T)->lchild), key, shorter)) return 0;
			if (shorter){
				switch((*T)->bf)
                {
                    case LH:
                    {
                        (*T)->bf = EH; 
                        *shorter = true;
                        break;
                    }
                    case EH:
                    {
                        (*T)->bf = RH;
                        *shorter = false;
                        break;
                    }
                    case RH:
                    {
                        rightBalance(T); 
                        if ((*T)->rchild->bf == EH)
                            *shorter = false;
                        else 
                            *shorter = true;
                            break;
                    }
				}
			}
		}
		else{
			if (!DeleteAVL(&((*T)->rchild), key, shorter)) 
                return 0;
			if (shorter)
            {
				switch((*T)->bf)
                {
				case LH:leftBalance(T);
				{
                    if ((*T)->lchild->bf == EH)
						*shorter = false;
					else 
						*shorter = true;
                        break;
                }
				case EH:
                {
                    (*T)->bf = LH; 
                    *shorter = false;
                    break;
                }
				case RH:
                {
                    (*T)->bf = EH; 
                    *shorter = true;
                    break;
                }
				}
			}
		}
	}
	return 1;
}//Delete

void menu()  
{  
	printf("       主菜单        \n");  
	printf("1:连续插入数据 输入0结束插入  \n");  
	printf("2:查找数据                    \n");  
	printf("3:删除特定数据                 \n");  
	printf("4:输出当前结果                     \n"); 
    printf("5:结束程序                     \n");
}  

int main()
{
	BSTree root = NULL;
	int num,n;
	int taller = false,shorter;
	while(1)  
	{  
		menu();
		scanf("%d",&num); 
		//if(num==5) break;
		switch (num)  
		{  
			case 1:
				printf("请插入数据 ，输入0结束插入\n");
				while(scanf("%d",&n))
				{
					if(n==0) break;
					else insert(&(root),n, &taller);
				}
				break;
			case 2: 
				printf("请输入要查询的数\n");
				scanf("%d",&n);
				int *p;
				p=search(root,n);
				if (p==NULL) 
				{
					printf("对不起 没有找到 %d!\n",n);
				}
				else 
				{
					printf("恭喜你 数据中存在 %d!\n",n);
				}
				break;  
			case 3: 
				printf("请输入要删除的数据\n");
				scanf("%d",&n);
				DeleteAVL(&(root),n,&shorter);
				break;
			case 4:
				print(root); 
				printf("\n");
				break;
			case 5:
				clear(&(root));
				return 0;
			default	:
			{
				printf("请重新输入\n");
				scanf("%d",&num);
			}	
		}
	}
	system("pause");
	return 0;
}
