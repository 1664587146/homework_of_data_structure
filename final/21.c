/*
    21����4��ƽ���������������ʾ��ѡ���� �����ң�
    [��������]
    ����ƽ�������ʵ��һ����̬���ұ�
    [����Ҫ��]
    ��1�� ʵ�ֶ�̬���ұ�����ֻ������ܣ����ҡ������ɾ����
    ��2�� ��Ŀ�����ϰ���P168 6.4��
*/

#include<stdio.h>  
#include<stdlib.h> 
//����������������һ
#define LH 1
//��������������һ����
#define EH 0
//����������������һ
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
 
//	����
void leftRotate(BSTree *root) 
{
	BSTree rc = (*root) -> rchild;
	(*root) -> rchild = rc -> lchild;
	rc -> lchild = *root;
	*root = rc;
}

//	����
void rightRotate(BSTree *root) 
{
	BSTree lc = (*root) -> lchild;
	(*root) -> lchild = lc -> rchild;
	lc -> rchild = *root;
	*root = lc;
}

//	�Զ�����root������ƽ�⴦��(LL�ͺ�LR��)
void leftBalance(BSTree *root) 
{
	BSTree lc = (*root) -> lchild;
	switch (lc -> bf) 
	{
		//LL�͵�ֻ��Ҫ������������
	case LH:
		//����֮���������������ƽ���
		(*root) -> bf = EH;
		lc -> bf = EH;
		//��������
		rightRotate(root);
		break;
		//LR�͵���Ҫ��������������Ȼ����������
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

//	���ܣ��Զ�����root������ƽ�⴦��(RR�ͺ�RL��)
void rightBalance(BSTree *root) 
{
	BSTree rc = (*root) ->rchild;
	switch (rc->bf) 
	{
		//RR��ֻ��Ҫ����������
	case RH:
		(*root) -> bf = EH;
		rc ->bf = EH;
		//��������
		leftRotate(root);
		break;
		//RL����Ҫ��������������Ȼ������������
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

//	���ܣ���Ԫ��data����ƽ�������root��
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
		//��Ԫ���Ѿ���ƽ��������д�����
		if (data == (*root) ->data) 
		{
			taller = false;
			return false;
		}
		//����������
		else if (data < (*root) ->data) 
		{
			if (!insert(&(*root) ->lchild, data, taller)) 
			{
				return false;
			}
			//����ɹ��������������
			if (taller) 
			{
				switch ((*root)->bf) 
				{
				case LH:
					leftBalance(root);
					//ƽ�������������ƽ�������
					//����û�б仯����taller = false
					*taller = false;
					break;
				case EH:
					(*root)->bf = LH;
					//ԭ����ƽ��Ĺʲ���һ��Ԫ�غ�
					//���߱�Ȼ���
					*taller = true;
					break;
				case RH:
					(*root)->bf = EH;
					//ԭ�������������������ߣ����ǵ�����������
					//����һ��Ԫ�ص�ʱ������ƽ���ˣ���taller = false
					*taller = false;
					break;
				default:
					break;
				}
			}
		}
		//����������
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
//   ��ƽ��������в���int�ڵ�
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
//	���ܣ����ƽ��������е����е�Ԫ�أ�С->�����������
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
//	���ܣ��ͷ�ƽ��������Ŀռ�
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
			printf("û���������\n");
			return(0);
		}
		if (EQ(key, (*T)->data))	//�ҵ�����Ҫɾ���Ľ��
		{
			//����ý���lchild ��
			//rchild ������һ��ΪNULL
			//��󹦸�ɣ����������
			//�·�����
			BSTree q = (*T);
			if (!(*T)->lchild)//����ý���lchild ΪNULL
			{
				q = (*T);
				(*T) = (*T)->rchild;
				free(q);
				*shorter = true;
				return 1;
			}
			else if (!(*T)->rchild)
            {//����ý���rchild Ϊ NULL
				q = (*T);
				(*T) = (*T)->lchild;
				free(q);
				*shorter = true;
				return 1;
			}
			else 
            {
				//ɾ��һ�����Һ��Ӷ���Ϊ�յĽ��
				//ʹ�ý���ֱ��ǰ��p��data�滻�ý���data
				//Ȼ��ı�key=p.data
				BSTree s = (*T) ->lchild;
				while (s->rchild)
					s = s->rchild;
				(*T)->data = s->data;
				key = s->data;//Now, delete the vertice whose data was the new key
			}
		}
		if (LQ(key, (*T)->data))
        {//������InsertAVL��ͬ
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
	printf("       ���˵�        \n");  
	printf("1:������������ ����0��������  \n");  
	printf("2:��������                    \n");  
	printf("3:ɾ���ض�����                 \n");  
	printf("4:�����ǰ���                     \n"); 
    printf("5:��������                     \n");
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
				printf("��������� ������0��������\n");
				while(scanf("%d",&n))
				{
					if(n==0) break;
					else insert(&(root),n, &taller);
				}
				break;
			case 2: 
				printf("������Ҫ��ѯ����\n");
				scanf("%d",&n);
				int *p;
				p=search(root,n);
				if (p==NULL) 
				{
					printf("�Բ��� û���ҵ� %d!\n",n);
				}
				else 
				{
					printf("��ϲ�� �����д��� %d!\n",n);
				}
				break;  
			case 3: 
				printf("������Ҫɾ��������\n");
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
				printf("����������\n");
				scanf("%d",&num);
			}	
		}
	}
	system("pause");
	return 0;
}
