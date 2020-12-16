#include<stdio.h>
#include<stdlib.h>
typedef struct ElementType//�򻯲���������int
{
    int q;
}Data;

typedef struct LinkNode
{  
    Data data; 
    int freq;//���ʵĴ���
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
        (*l) -> next = (*l) -> prior = *l;
        (*l) -> freq = 0;
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
        p -> freq = 0;
        p -> prior = r;
        p ->next =r ->next; 
        r->next = p ;
        r = p -> next;
        r -> prior = p;
        return 9;
    }
}//���� ��Ч��0 �ɹ�9 ��ʧ��-9

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


int compare(Data d1,Data d2)
{
    if(d1.q == d2.q )return (1);
    else return (0);
}
int LOCATE(LinkList l, Data e,int(*compare)(Data , Data))
/*
first find the node.Its freq plus 1.
Its freq compare with its prior`s that find the first one bigger than itself. 
Insert after the bigger one.
node1 node2 node3is assist point.
*/
{
    if(l == 0)
    {
        return 0;
    }
    int j = 1,state = 0;
    LinkNode *node1 = l -> next,*node2,*node3;
    for(; node1 != l; node1 = node1 -> next,j++)
    {
        if(compare(node1->data,e))
        {
            node1 -> freq ++;
            state = 1;
            break;
        }
    }
    if(state)
    {
        for (node2 = node1 -> prior; (node2 -> freq) <= (node1-> freq)&&node2 != l; node2 = node2 ->prior);
        // cut the node
        (node1 -> prior) -> next = node1 -> next;
        (node1 -> next) -> prior = node1 -> prior;
        //link the node into the list
        node3 = node2 ->next;
        node2 -> next = node1;
        node1 -> next = node3;
        node3 -> prior = node1;
        node1 -> prior = node2;
        return (j);
    }
    else
    {
        return(-6);
    }
}//��λ ��Ч��0 �з���λ�� ����-6

int main()
{
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n");
    LinkList l;
    Data elem;
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
    printf("ok ������ʾ����Ԫ��\n");
    ListTraverse_ll(l);
    while (1)
    {
        printf("Ҫ��λ��Ԫ��,�˳�#\n");
        scanf("%d",&elem.q);
        if(getchar() == '#')
        {
            break;
        }
        printf("��ʼ��������\n");
        printf("�ڵ�%d��\n", LOCATE(l,elem,compare));
        printf("ok ��ʾ����Ԫ��\n");
        ListTraverse_ll(l);
    }
    system("pause");
    return 0;
}