#include<stdio.h>
#include<stdlib.h>
typedef struct ElementType//简化操作所以用int
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
}//创建表 成功返回1 失败返回-1



int ListLength_ll(LinkList l)
{
    if(l == 0) return 0;
    int i = 0;
    LinkNode *p;
    for(p = (l) -> next;p != l;p = p -> next,i++);
    return i;

}//返回链表长度i                  无效表 0

int ListInsert_ll(LinkList l,int i,Data e)
//i前
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
}//插入 无效表0 成功9 ，失败-9



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
            if(!printf("这个元素是 : %d\n", (p ->data).q))
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
            if(!printf("这个元素是 : %d\n", (p ->data).q))
        {
            exit (-12);
        }
    }
    return 12;
}

int main()
{
    printf("中文使用的是GBK。Simplified Chinese using GBK.\n");
    LinkList l;
    Data elem,elem1;
    int i;
    InitList_ll(&l);
    printf("我们先写几个节点：(为了方便Data里只有一个int型,以#结尾)\n");
    i = 1;
    for(;;)
    {
        scanf("%d",&elem.q);
        ListInsert_ll(l,i++,elem);//为了方便
        if(getchar() == '#')
        {
            break;
        }
    }
    printf(" ok 结束显示所有元素\n");
    ListTraverse_ll(l);
    printf("开始循环链表\n");
    circulate(l);
    printf(" ok 向前显示所有元素\n");
    ListTraversePrior_ll(l);
    system("pause");
    return 0;
}