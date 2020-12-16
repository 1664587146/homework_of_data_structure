#include<stdio.h>
#include<stdlib.h>
//因为大量移动所以用链表

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
}//得到元素 成功5 失败-5

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
}//定位 无效表0 有返回位置 ，无-6

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
    
}//找前继 无效表0 有返回7 ，无-7

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
}//找前继 无效表0 有返回8 ，无-8

int ListInsert_ll(LinkList l,int i,int e)
//i前
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
}//插入 无效表0 成功9 ，失败-9

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
}//删除 无效表0 成功10 ，失败-10

int ListTraverse_ll(LinkList l )
{
    LinkNode *p ;
    for(p = l -> next; p != 0 ; p = p -> next)
    {
            if(!printf("这个元素是 : %d\n", (p ->number)))
        {
            exit (-11);
        }
    }
    return 11;
}

//以上为链表的基本操作
int main()
{
    LinkList l;
    int m,n,k,i,j,a,node;
    InitList_ll(&l);
    printf("请输入人数");
    scanf("%d",&n);
    while(n < 0 )
    {
        printf("请输入请重新输入");
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
    printf("请输入操作次数");
    scanf("%d",&m);
    while(m < 0 )
    {
        printf("请输入请重新输入");
        scanf("%d",&m);
        if( m < 0)
        {
            break;
        }
    }
    ListTraverse_ll(l);
    for(k = 0 ; k < m ; k++)
    {
        printf("请输入学号和位数");
        scanf("%d %d",&i, &j);
        a = LocateElem_ll(l,i,compare);
        if( a )
        {
            while(a+j<1 || a + j >n)
            {
                printf("请输入请重新输入位置");
                scanf("%d",&j);  
            }
            ListDelete_ll(l,a,&node);
            ListInsert_ll(l,a+j,node);
            //ListTraverse_ll(l);
        }
        else{
            printf("无此学号");
        }
    }
    ListTraverse_ll(l);
    system("pause");
    return 0;
}
