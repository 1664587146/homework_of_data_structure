#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
//����ͷ

typedef struct ElementType//�򻯲���������int
{
    int q;
}Data;

typedef struct LinkNode
{  
    Data data; 
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

int GetElem_ll(LinkList l, int i, Data *d)
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

int compare(Data d1,Data d2)
{
    if(d1.q == d2.q )return (1);
    else return (0);
}
int LocateElem_ll(LinkList l, Data e,int(*compare)(Data , Data))
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

int PriorElem_ll(LinkList l, Data cur_e,Data *pre_e,int(*compare)(Data , Data))
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

int NextElem_ll(LinkList l, Data cur_e,Data *next_e,int(*compare)(Data , Data))
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

int ListInsert_ll(LinkList l,int i,Data e)
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
        p -> next = r ->next; 
        r-> next = p ;
        return 9;
    }
    if((l) -> next == 0)
    {
        (l) ->next = p;
        p ->next =0;
        return 9;
    }
}//���� ��Ч��0 �ɹ�9 ��ʧ��-9

int ListDelete_ll(LinkList l,int i,Data* e)
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

int ListTraverse_ll(LinkList l )//l��ַû�䵫��ʾ*node������node����
{
    LinkNode *p ;
    for(p = l -> next; p != 0 ; p = p -> next)
    {
            if(!printf("���Ԫ���� : %d\n", (p ->data).q))
        {
            exit (-11);
        }
    }
    return 11;
}

int main()
{
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n");
    LinkList l = 0;
    Data elem,elem1;
    int i;
    InitList_ll(&l);
    printf("ll�Ƿ�Ϊ�գ�%d��3Ϊ�գ�0��-3Ϊ�ǿգ�\n",ListEmpty_ll(l));
    printf("������д�����ڵ㣺(Ϊ�˷���Data��ֻ��һ��int��,��#��β)\n");
    i = 1;
    for(;;)
    {
        scanf("%d",&elem.q);
        ListInsert_ll(l,i++,elem);//Ϊ�˷���
        if(getchar() == '#')
        {
            break;
        }
    }
    printf(" ok ������ʾ����Ԫ��\n");
    ListTraverse_ll(l);
    printf("����Ϊ%d\n",ListLength_ll(l));
    printf("����������λ�ú;������ݣ�λ����ǰ��:");
    scanf("%d%d",&i,&elem.q);
    if(ListInsert_ll(l,i,elem))
    {
        printf(" ok ������ʾ����Ԫ��\n");
        ListTraverse_ll(l);
    }
    else
    {
        printf("����");
    }
    printf("������Ҫɾ���ľ������ݵ�λ��\n");
    scanf("%d",&i);//
    if(ListDelete_ll(l,i,&elem))
    {
        printf("ɾ����Ԫ���� : %d\n",elem.q);
        printf(" ok ������ʾ����Ԫ��\n");
        ListTraverse_ll(l);
    }
    else
    {
        printf("����");
    }
    printf("������Ҫ��ѯ�ģ�");
    scanf("%d",&elem.q);
    if(i = LocateElem_ll(l,elem,compare))
    {
        printf("�ڵ�%d��\n",i);
    }
    else
    {
        printf("��");   
    }
    printf("������Ҫ��ѯǰ��̵�����ֵ��");
    scanf("%d",&elem.q);
    {
        if(PriorElem_ll(l,elem,&elem1,compare))
        {
            printf("ǰ����%d\n",elem1.q);
        }
        else
        {
            printf("ûǰ��\n");
        }
        if(NextElem_ll(l,elem,&elem1,compare))
        {
            printf("�����%d\n",elem1.q);
        }
        else
        {
            printf("û���\n");
        }        
    }
    printf("clear list\n");
    ClearList_ll(l);
    printf("ll�Ƿ�Ϊ�գ�%d(3Ϊ�գ�0��-3Ϊ�ǿ�)\n",ListEmpty_ll(l));
    DestroyList_ll(&l);
    system("pause");
    return 0;
}