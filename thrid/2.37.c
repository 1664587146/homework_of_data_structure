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
        (*l) -> next  = (*l) -> prior = *l;
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
        p -> prior = r;
        p ->next =r ->next; 
        r->next = p ;
        r = p -> next;
        r -> prior = p;
        return 9;
    }
}//插入 无效表0 成功9 ，失败-9

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

int function(LinkList l )
/*
node1一开始指链头
node2一开始指链尾后一个（因为第2个要插入队尾
node3处理的节点指针
node1 -> next插到node2 -> prior前
node1 = node1 -> next ->next(和没变前比)
node2 = node2 -> prior (变后) 
p辅助指针
*/
{
    LinkNode *p,*node,*node1,*node2 ;
    for(node1 = l -> next,node2 = l ;;node1 = node1 -> next , node2 = node2 -> prior)
    {
        //循环条件（防止for太长所以单写
        if((node1 -> next == node2 -> prior)||(node1 -> next == node2 ))
        //stop situation 1：node1 is next to node2
        //stop situation 2; one node is between node1 and node2
        {
            break;
        }
        //将第偶数个抽出
        node = (node1 -> next);
        p = node1 -> next -> next;
        //将断链表重链
        node1 -> next = p;
        p -> prior = node1;
        //插入应该的位置
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
    printf("ok 结束显示所有元素\n");
    ListTraverse_ll(l);
    printf("开始处理链表\n");
    function(l);
    printf("ok 显示所有元素\n");
    ListTraverse_ll(l);
    system("pause");
    return 0;
}