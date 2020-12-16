#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
//带表头

typedef struct ElementType//简化操作所以用int
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
}//创建表 成功返回1 失败返回-1

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
}//摧毁表 无表头0 成功2 未知原因失败-2

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
}//清空表 无表头0 成功2 未知原因失败-2

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
}//判断是否为空 无表头0 空表3 错误-3

int ListLength_ll(LinkList l)
{
    if(l == 0) return 0;
    int i = 0;
    LinkNode *p;
    for(p = (l) -> next;p != NULL;p = p -> next,i++);
    return i;

}//返回链表长度i                  无效表 0

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
}//得到元素 成功5 失败-5

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
}//定位 无效表0 有返回位置 ，无-6

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
    
}//找前继 无效表0 有返回7 ，无-7

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
}//找前继 无效表0 有返回8 ，无-8

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
}//插入 无效表0 成功9 ，失败-9

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
}//删除 无效表0 成功10 ，失败-10

int ListTraverse_ll(LinkList l )//l地址没变但表示*node，所以node变了
{
    LinkNode *p ;
    for(p = l -> next; p != 0 ; p = p -> next)
    {
            if(!printf("这个元素是 : %d\n", (p ->data).q))
        {
            exit (-11);
        }
    }
    return 11;
}

int main()
{
    printf("中文使用的是GBK。Simplified Chinese using GBK.\n");
    LinkList l = 0;
    Data elem,elem1;
    int i;
    InitList_ll(&l);
    printf("ll是否为空：%d（3为空，0和-3为非空）\n",ListEmpty_ll(l));
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
    printf("长度为%d\n",ListLength_ll(l));
    printf("请输入插入的位置和具体数据（位置在前）:");
    scanf("%d%d",&i,&elem.q);
    if(ListInsert_ll(l,i,elem))
    {
        printf(" ok 结束显示所有元素\n");
        ListTraverse_ll(l);
    }
    else
    {
        printf("错误");
    }
    printf("请输入要删除的具体数据的位置\n");
    scanf("%d",&i);//
    if(ListDelete_ll(l,i,&elem))
    {
        printf("删除的元素是 : %d\n",elem.q);
        printf(" ok 结束显示所有元素\n");
        ListTraverse_ll(l);
    }
    else
    {
        printf("错误");
    }
    printf("请输入要查询的：");
    scanf("%d",&elem.q);
    if(i = LocateElem_ll(l,elem,compare))
    {
        printf("在第%d个\n",i);
    }
    else
    {
        printf("无");   
    }
    printf("请输入要查询前后继的数据值：");
    scanf("%d",&elem.q);
    {
        if(PriorElem_ll(l,elem,&elem1,compare))
        {
            printf("前继是%d\n",elem1.q);
        }
        else
        {
            printf("没前继\n");
        }
        if(NextElem_ll(l,elem,&elem1,compare))
        {
            printf("后继是%d\n",elem1.q);
        }
        else
        {
            printf("没后继\n");
        }        
    }
    printf("clear list\n");
    ClearList_ll(l);
    printf("ll是否为空：%d(3为空，0和-3为非空)\n",ListEmpty_ll(l));
    DestroyList_ll(&l);
    system("pause");
    return 0;
}