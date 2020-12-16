#include<stdio.h>
#include<stdlib.h>
typedef struct ElementType//�򻯲���������int
{
    int q;
}Data;

typedef struct LinkNode
{  
    Data data; 
    struct LinkNode *next,*prior;
}LinkNode,*LinkList;


int InitList_ll(LinkList *l)
{
    {
        *l = (LinkList )malloc(sizeof(LinkList));
        if(l == 0)
        {
            return (-1);
        }
        (*l) -> next  = *l;
    } 
    return (1);
}//������ �ɹ�����1 ʧ�ܷ���-1



int ListLength_ll(LinkList l)
{
    if(l == 0) return 0;
    int i = 0;
    LinkNode *p;
    for(p = (l) -> next;p != l;p = p -> next,i++);
    return i;

}//����������i                  ��Ч�� 0

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
        p ->next =r ->next; 
        r->next = p ;
        return 9;
    }
}//���� ��Ч��0 �ɹ�9 ��ʧ��-9



void circulate(LinkList l)
{
    LinkNode *node;
    for(node = l -> next; ;node = node ->next)
    {
        (node ->next) -> prior = node;
        if(node == l)
        break;
    }
}

int ListTraverse_ll(LinkList l )
{
    LinkNode *p ;
    for(p = l -> next; p != l ; p = p -> next)
    {
            if(!printf("���Ԫ���� : %d\n", (p ->data).q))
        {
            exit (-11);
        }
    }
    return 11;
}

int ListTraversePrior_ll(LinkList l )
{
    LinkNode *p ;
    for(p = l ->prior;p != l; p = p -> prior)
    {
            if(!printf("���Ԫ���� : %d\n", (p ->data).q))
        {
            exit (-12);
        }
    }
    return 12;
}

int main()
{
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n");
    LinkList l;
    Data elem,elem1;
    int i;
    InitList_ll(&l);
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
    printf("��ʼѭ������\n");
    circulate(l);
    printf(" ok ��ǰ��ʾ����Ԫ��\n");
    ListTraversePrior_ll(l);
    system("pause");
    return 0;
}