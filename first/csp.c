#include<stdio.h>
#include<stdlib.h>
//��Ϊ�����ƶ�����������

typedef struct LinkNode
{  
    int number; 
    struct LinkNode *next;
}LinkNode,*LinkList;


int InitList_ll(LinkList *l)
{
    {
        *l = (LinkList )malloc(sizeof(LinkList));
        if(l == 0)
        {
            return (-1);
        }
        (*l) -> next  =0;
    } 
    return (1);
}//������ �ɹ�����1 ʧ�ܷ���-1

int DestroyList_ll(LinkList *l)
{
    int state = 0;
    if(*l == 0 )
    {
        return 0;
    }
    LinkNode *p,*q;
    p = (*l) -> next; 
    {
        while (p != 0 )
        {
            q = p;
            p = p -> next;
            free(q);
        }
        free(*l);
        state = 1;
    }
    if(state = 1)
    {
        return (2);
    }
    if(state = 1)
    {
        return (-2);
    }
}//�ݻٱ� �ޱ�ͷ0 �ɹ�2 δ֪ԭ��ʧ��-2

int ClearList_ll(LinkList l)
{
    int state = 0;
    if(l == 0 )
    {
        return 0;
    }
    LinkNode *p,*q;
    p = (l) -> next; 
    {
        while (p != 0 )
        {
            q = p;
            p = p -> next;
            free(q);
        }
        (l) ->next =0;
        state = 1;
    }
    if(state = 1)
    {
        return (2);
    }
    if(state = 1)
    {
        return (-2);
    }    
}//��ձ� �ޱ�ͷ0 �ɹ�2 δ֪ԭ��ʧ��-2

int ListEmpty_ll(LinkList l)
{
    if(l == 0 )
    {
        return 0;
    }
    if( l -> next == 0 )
    return 3;
    else
    {
        return -3;
    }    
}//�ж��Ƿ�Ϊ�� �ޱ�ͷ0 �ձ�3 ����-3

int ListLength_ll(LinkList l)
{
    if(l == 0) return 0;
    int i = 0;
    LinkNode *p;
    for(p = (l) -> next;p != NULL;p = p -> next,i++);
    return i;

}//����������i                  ��Ч�� 0

int GetElem_ll(LinkList l, int i, int *d)
{
    if( i > ListLength_ll(l) || i < 1)
    {
        return (-5);
    }
    int j;
    LinkNode *p = (l) -> next;
    for(j = 1 ; j < i ; p = p -> next , j++) ;
    *d = p ->number;
    return (5);
}//�õ�Ԫ�� �ɹ�5 ʧ��-5

int compare(int d1,int d2)
{
    if(d1== d2 )return (1);
    else return (0);
}
int LocateElem_ll(LinkList l, int e,int(*compare)(int , int))
{
    if(l == 0)
    {
        return 0;
    }
    int j = 1;
    LinkNode *p = l -> next;
    for(; p != 0; p = p -> next,j++)
    {
        if(compare(p->number,e))
        {
            break;
        }
    }
    if(p != NULL)
    {
        return (j);
    }
    else
    {
        return(-6);
    }
}//��λ ��Ч��0 �з���λ�� ����-6

int PriorElem_ll(LinkList l, int cur_e,int *pre_e,int(*compare)(int , int))
{
    if(l == 0) return(0);
    LinkNode *p = l -> next;
    int state = 0;
    for(;p != 0; p = p -> next)
    {
        if(compare((p->next) ->number, cur_e))
        {
            state = 1;
            break;
            
        }
    }
    if(state == 1)
    {
    *pre_e = p ->number;
    return (7);
    }
    else
    {
        return (-7);
    }
    
}//��ǰ�� ��Ч��0 �з���7 ����-7

int NextElem_ll(LinkList l, int cur_e,int *next_e,int(*compare)(int , int))
{
    if(l == 0) return(0);
    LinkNode *p = (l) -> next;
    int state = 0;
    for(;p != 0; p = p -> next)
    {
        if(compare(p ->number, cur_e))
        {
            state = 1;
            break;
        }
    }
    if(state == 1)
    {
    *next_e = (p -> next) ->number;
    return (8);
    }
    else
    {
        return (-8);
    }
}//��ǰ�� ��Ч��0 �з���8 ����-8

int ListInsert_ll(LinkList l,int i,int e)
//iǰ
{
    if(l == 0 || i < 1 || i > ListLength_ll(l) + 1) return(0);
    LinkNode *p,*r;
    int j = 1;
    p = (LinkNode*)malloc(sizeof(LinkNode));
    if(p){  p ->number = e;}
    else{return (-9);}
    if((l) -> next != 0)
    {
        if(i != 1)
        {
            for(r = (l) -> next;j < i-1 ; j++,r = r->next) ;
        }
        else
        {
            r = l;
        }
        p ->next =r ->next; 
        r->next = p ;
        return 9;
    }
    if((l) -> next == 0)
    {
        (l) ->next = p;
        p ->next =0;
        return 9;
    }
}//���� ��Ч��0 �ɹ�9 ��ʧ��-9

int ListDelete_ll(LinkList l,int i,int* e)
{
    if(l == 0 || i < 1 || i > ListLength_ll(l)) return(0);
    LinkNode *p,* r;
    int j = 1;
    if(i == 1)
    {
        p = l;
        r = p ->next ;   
        p ->next = r->next;
        *e = r -> number;
        free(r);
        return (10);
    }
    for(p = (l)->next;j < i-1 ; j++,p = p->next) ;
    r = p ->next ;   
    p ->next = r->next;
    *e = r -> number;
    free(r);
    return (10);
}//ɾ�� ��Ч��0 �ɹ�10 ��ʧ��-10

int ListTraverse_ll(LinkList l )
{
    LinkNode *p ;
    for(p = l -> next; p != 0 ; p = p -> next)
    {
            if(!printf("���Ԫ���� : %d\n", (p ->number)))
        {
            exit (-11);
        }
    }
    return 11;
}

//����Ϊ����Ļ�������
int main()
{
    LinkList l;
    int m,n,k,i,j,a,node;
    InitList_ll(&l);
    printf("����������");
    scanf("%d",&n);
    while(n < 0 )
    {
        printf("����������������");
        scanf("%d",&n);
        if( n < 0)
        {
            break;
        }
    }
    for(k = n ;k > 0 ; k --)
    {
        ListInsert_ll(l,1,k);
    }
    printf("�������������");
    scanf("%d",&m);
    while(m < 0 )
    {
        printf("����������������");
        scanf("%d",&m);
        if( m < 0)
        {
            break;
        }
    }
    ListTraverse_ll(l);
    for(k = 0 ; k < m ; k++)
    {
        printf("������ѧ�ź�λ��");
        scanf("%d %d",&i, &j);
        a = LocateElem_ll(l,i,compare);
        if( a )
        {
            while(a+j<1 || a + j >n)
            {
                printf("����������������λ��");
                scanf("%d",&j);  
            }
            ListDelete_ll(l,a,&node);
            ListInsert_ll(l,a+j,node);
            //ListTraverse_ll(l);
        }
        else{
            printf("�޴�ѧ��");
        }
    }
    ListTraverse_ll(l);
    system("pause");
    return 0;
}
