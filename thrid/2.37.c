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
        (*l) -> next  = (*l) -> prior = *l;
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

int function(LinkList l )
/*
node1һ��ʼָ��ͷ
node2һ��ʼָ��β��һ������Ϊ��2��Ҫ�����β
node3����Ľڵ�ָ��
node1 -> next�嵽node2 -> priorǰ
node1 = node1 -> next ->next(��û��ǰ��)
node2 = node2 -> prior (���) 
p����ָ��
*/
{
    LinkNode *p,*node,*node1,*node2 ;
    for(node1 = l -> next,node2 = l ;;node1 = node1 -> next , node2 = node2 -> prior)
    {
        //ѭ����������ֹfor̫�����Ե�д
        if((node1 -> next == node2 -> prior)||(node1 -> next == node2 ))
        //stop situation 1��node1 is next to node2
        //stop situation 2; one node is between node1 and node2
        {
            break;
        }
        //����ż�������
        node = (node1 -> next);
        p = node1 -> next -> next;
        //������������
        node1 -> next = p;
        p -> prior = node1;
        //����Ӧ�õ�λ��
        p = node2 -> prior;//
        node -> prior = p;
        p -> next = node ;
        node2 -> prior =node;
        node -> next = node2;


    }
    return 11;
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
    printf("ok ������ʾ����Ԫ��\n");
    ListTraverse_ll(l);
    printf("��ʼ��������\n");
    function(l);
    printf("ok ��ʾ����Ԫ��\n");
    ListTraverse_ll(l);
    system("pause");
    return 0;
}