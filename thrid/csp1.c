#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int head[2],head2[2],number;
}ElemType;

typedef struct LinkNode
{  
    ElemType data; 
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

int ListInsert_ll(LinkList l,int i,ElemType e)
//iǰ
{
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

int ListDelete_ll(LinkList l,int i,ElemType* e)
{
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

int ToTop(LinkList l,int *a);

int main()
{
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n");
    LinkList l;
    InitList_ll(&l);
    ElemType elem;
    int i,num1,num2,point[2];
    printf("�����봰�������͵����:\n");
    scanf("%d%d",&num1,&num2);
    printf("�����봰�ڶ���\n");
    for(i = 0;i < num1; i++)
    {
        scanf("%d %d %d %d",elem.head,elem.head + 1,elem.head2 ,elem.head2 + 1);
        elem.number =  i + 1;
        ListInsert_ll(l,1,elem);
    }
    printf("����������\n");
    for(i = 0;i < num2; i++)
    {
        scanf("%d %d",point ,point + 1 );
        ToTop(l,point);
    }
    system("pause");
    return 0;
}

int ToTop(LinkList l,int *a)
{ 
    LinkNode *node;
    int i;
    ElemType elem;
    for(node = l -> next,i = 1 ; ;node = node -> next,i++  )
    {
        if((a[0] >= (node->data).head[0]&&a[0] <= (node->data).head2[0]))
        {
            if((a[1] >= (node->data).head[1]&&a[1] <= (node->data).head2[1])||(a[1] <= (node->data).head[1]&&a[1] >= (node->data).head2[1]))
            {
                printf("%d\n",node ->data.number);
                ListDelete_ll(l,i ,& elem );
                ListInsert_ll(l,1,elem);
                return 0;
            }
            else if(node -> next == 0)
            {
                printf("IGNORED\n");
                return 0;
            }
        }
        else if((a[0] <= (node->data).head[0]&&a[0] >= (node->data).head2[0]))
        {
            if((a[1] >= (node->data).head[1]&&a[1] <= (node->data).head2[1])||(a[1] <= (node->data).head[1]&&a[1] >= (node->data).head2[1]))
            {
                printf("%d\n",node ->data.number);
                ListDelete_ll(l,i ,& elem );
                ListInsert_ll(l,1,elem);
                return 0;
            }
            else if(node -> next == 0)
            {
                printf("IGNORED\n");
                return 0;
            }
        }
        else
        {
            if(node -> next == 0)
            {
                printf("IGNORED\n");
                return 0;
            }
        }
    }
    return 0;
}