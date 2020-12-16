#include<stdio.h>
#include<stdlib.h>
//����ͷ
typedef struct LinkNode
{  
    int data; 
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
    *d = p ->data;
    return (5);
}//�õ�Ԫ�� �ɹ�5 ʧ��-5

int compare(int d1,int d2)
{
    if(d1 == d2 )return (1);
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
        if(compare(p->data,e))
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
        if(compare((p->next) ->data, cur_e))
        {
            state = 1;
            break;
            
        }
    }
    if(state == 1)
    {
    *pre_e = p ->data;
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
        if(compare(p ->data, cur_e))
        {
            state = 1;
            break;
        }
    }
    if(state == 1)
    {
    *next_e = (p -> next) ->data;
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
    if(p){  p ->data = e;}
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
        *e = r -> data;
        free(r);
        return (10);
    }
    for(p = (l) -> next;j < i-1 ; j++,p = p->next) ;
    r = p ->next ;   
    p ->next = r->next;
    *e = r -> data;
    free(r);
    return (10);
}//ɾ�� ��Ч��0 �ɹ�10 ��ʧ��-10

int ListTraverse_ll(LinkList l )
{
    LinkNode *p ;
    for(p = l -> next; p != 0 ; p = p -> next)
    {
            if(!printf("���Ԫ���� : %d\n", (p ->data)))
        {
            exit (-11);
        }
    }
    return 11;
}
 
//��������
int order(LinkList l)
{
    LinkNode *pre,*cir;//cir==circulate
    int minNowData,position;
    if( l == 0 ) return (0);
    pre = l ;
    for( ;pre ->next; pre = pre -> next)
    {
        
        for(cir = pre -> next,minNowData =cir ->data;cir;cir = cir -> next)
        {
            if(cir ->data < minNowData)
            {
                minNowData = cir ->data;
            }
            position=LocateElem_ll(l,minNowData,compare);
            ListDelete_ll(l , position,&minNowData);
            ListInsert_ll(pre,1,minNowData);
        }
    }
    return (13);
}
//������ʱ������ ��ֹ��Ϊ����

//�󽻼�
int intersection(LinkList a,LinkList b,LinkList c)
{
    if( !a || !b || !c) exit(0);
    LinkNode *nodeA,*nodeB,*nodeC;
    int data;
    for(nodeA = a->next ,nodeB =b ->next, nodeC = c ; nodeA&&nodeB ;  )
    {
        if((nodeA) -> data > nodeB -> data ){ nodeB = nodeB -> next;  continue;    }
        if(nodeA -> data == nodeB -> data )
        {
            data =(nodeA) -> data ;
            ListInsert_ll(nodeC, 1 ,data);
            nodeC = nodeC -> next;
            nodeA = nodeA -> next; 
            nodeB = nodeB -> next; 
            continue; 
        }    
        if(nodeA -> data < nodeB -> data ){nodeA = nodeA -> next; continue;  }
    }
    return (13);
}

int main()
{
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n");
    LinkList ListA,ListB,ListC;
    int elem,elem1;
    int i;
    InitList_ll(&ListA);
    InitList_ll(&ListB);
    InitList_ll(&ListC);
    printf("����A��(Data��ֻ��һ��int��,��#��β)\n");
    for(i = 1;;)
    {
        scanf("%d",&elem);
        ListInsert_ll(ListA,i++,elem);//Ϊ�˷���
        if(getchar() == '#')
        {
            break;
        }
    }
    order(ListA);
    printf(" ok ������ʾA����Ԫ��\n");
    ListTraverse_ll(ListA);
    printf("����B��(Data��ֻ��һ��int��,��#��β)\n");
    for(i = 1;;)
    {
        scanf("%d",&elem);
        ListInsert_ll(ListB,i++,elem);//Ϊ�˷���
        if(getchar() == '#')
        {
            break;
        }
    }
    order(ListB);
    printf(" ok ������ʾB����Ԫ��\n");
    ListTraverse_ll(ListB);
    if(intersection(ListA ,ListB ,ListC))
    {
        printf(" ok ,List c is: \n");
        ListTraverse_ll(ListC);
        system("pause");
        return 0;
    }       
    else
    {
        printf("ERROR");
        system("pause");
        return 0;
    }
}