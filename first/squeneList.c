#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct//简化操作所以int
{
    int a;
}Elemtype;

typedef struct
{
    Elemtype *elem;
    int length;
    int listsize;
}Sqlist;

int InitList_Sq(Sqlist *(*l))//l为指针
{   
    if(sizeof(*l) != sizeof(Sqlist))
    {
        if(!(*l = (Sqlist *)malloc(sizeof(Sqlist))))
        {
            exit (1);//0=OVERFLOW
        }
    }    
    (*l)->elem = (Elemtype *)calloc(LIST_INIT_SIZE,sizeof(Elemtype));
    if((*l)->elem == 0)
    {
        exit (1);//0=OVERFLOW
    }
    else
    {
        (*l)->length = 0;
        (*l)->listsize = LIST_INIT_SIZE;
        return 0;
    }
}//创建表

int DestoryList_Sq(Sqlist* (*l))
{
    if(l == 0) exit(0);
    else
    {
        free( (*l) -> elem );
        (*l)->length = -1;
        (*l)->listsize = -1;
        free(*l);
        return 0;
    }
    /*free(l);*/
}//销毁 

int ClearList_Sq(Sqlist* l)
{
    if(l == 0) exit(0);
    else
    {
        l->length = 0;
        return 0;
    }
}//清空表

int ListEmpty_Sq(Sqlist* l)
{
    if( l == 0)
    {
        printf("kong");
    }
    printf("%h",l);
    if(l == 0) exit(0);
    else
    {
        if( l -> length == 0)
        return (0);
    }
    return (1);
}//判断是否为空

int GetElem_Sq(Sqlist* l , int i,Elemtype *e)
{
    if(l == 0) exit(0);
    else
    {
        *e = *(l->elem + i - 1);
    }
    return (1);
}//得到第i个元素值

int compare( Elemtype *e1, Elemtype *e2 )
{
    if(e1 -> a == e2 -> a)
    {
        return 0;
    }
    return 1;//一表示不相等
}//下面一起用

int LocateElem_Sq(Sqlist *l, Elemtype e ,int (*compare)(Elemtype* , Elemtype*))
{
    if( l == NULL) exit(0);
    int i = 0;
    for(;i< l -> length ;i ++ )
    {
        if(!compare(l->elem + i,&e))
        {
            return (i+1);
        }
    }
    return (-1);//找不到用-1表示
}

int PriorElem_Sq(Sqlist *l,Elemtype cur_e ,Elemtype *pre_e,int (*compare)(Elemtype* , Elemtype*))
{
    int i,state;
    if( l == NULL) exit(0);
    for(i = state = 0;i< l -> length;i ++ )
    {
        if(!compare(l->elem + i,&cur_e))
        {
            break;
        }
    }
    if(i != 0)
    {
        *pre_e = *(l -> elem + i - 1);
        state = 1;
    }
    if(state)
    {
        return (1);
    }
    return (0);
}

int NextElem_Sq(Sqlist *l,Elemtype cur_e ,Elemtype *next_e,int (*compare)(Elemtype* , Elemtype*))
{
    int state,i;
    if( l == NULL) exit(0);
    for(i = state = 0;i< l -> length;i ++ )
    {
        if(!compare(l->elem + i,&cur_e))
        {
            break;
        }
    }
    *next_e = *(l -> elem + i + 1);
    state = 1;
    if(state)
    {
        return (1);
    }
    return (0);
}

int ListInsert_Sq(Sqlist *l,int i ,Elemtype e)
//第i个位置之前
{
    if(i < 0 || (i > l->length+1)&&(l -> length != 0))
    {
        exit(0); 
    }
    if(l->length >= l->listsize)
    {
        Elemtype* new_base;
        new_base = (Elemtype *)realloc(l->elem,(l->length+LISTINCREMENT)*sizeof(Elemtype));
        if(new_base == 0)
        {
            exit(1);
        }
        l->elem = new_base;
        l->listsize += LISTINCREMENT;
    }
    Elemtype *q,*p;
    q = l->elem + i - 1 ;
    for(p = (l->elem) + (l->length) ;p > q; p -- )
    {
        *p = *(p - 1);
    }
    *q = e;
    l->length ++ ;
    return (0);
}

int ListDelete_Sq(Sqlist *l,int i,Elemtype *e)
//删除第i个
{
    if(l == 0 || i > l->length)
    {
        exit (0);
    }
    Elemtype *p;
    p = l->elem + i - 1;
    *e = *p;
    for(;i < l->length; i++)
    {
        *p = *(p + 1);
        p++;
    }
    l->length -=1;
    return 0;
} 

int ListTraverse_sq(Sqlist *l )
{
    int i;
    for( i = 0; i < l->length ;i++)
    {
            if(!printf("这个元素是 : %d\n", (l ->elem + i) -> a))
        {
            exit (0);
        }
    }
    return 0;
}
//因为没必要多文件所有就没多文件

int main()
{
    printf("中文使用的是GBK。Simplified Chinese using GBK.\n");
    Sqlist *sq;
    Elemtype elem,elem1;
    InitList_Sq(&sq);
    int i ;
    printf("sq是否为空：%d（0为空，1为非空）\n",ListEmpty_Sq(sq));
    printf("我们先写几个节点：(为了方便elemtype里只有一个int型,以#结尾)\n");
    for(i = 1;;)
    {
        scanf("%d",&elem.a);
        ListInsert_Sq(sq,i++,elem);//为了方便
        if(getchar() == '#')
        {
            break;
        }
    }
    printf(" ok 结束显示所有元素\n");
    ListTraverse_sq(sq);
    printf("请输入插入的位置和具体数据（位置在前）:");
    scanf("%d%d",&i,&elem.a);
    if(!ListInsert_Sq(sq,i,elem))
    {
        printf(" ok 结束显示所有元素\n");
        ListTraverse_sq(sq);
    }
    else
    {
        printf("错误");
    }
    printf("请输入要删除的具体数据的位置\n");
    scanf("%d",&i);
    if(!ListDelete_Sq(sq,i,&elem))
    {
        printf("删除的元素是 : %d\n",elem.a);
        printf(" ok 结束显示所有元素\n");
        ListTraverse_sq(sq);
    }
    else
    {
        printf("错误");
    }
    printf("请输入要查询的：");
    scanf("%d",&elem.a);
    if(i = LocateElem_Sq(sq,elem,compare))
    {
        printf("在第%d个\n",i);
    }
    else
    {
        printf("无");   
    }
    printf("请输入要查询前后继的数据值：");
    scanf("%d",&elem.a);
    {
        if(PriorElem_Sq(sq,elem,&elem1,compare))
        {
            printf("前继是%d\n",elem1.a);
        }
        else
        {
            printf("没前继\n");
        }
        if(NextElem_Sq(sq,elem,&elem1,compare))
        {
            printf("后继是%d\n",elem1.a);
        }
        else
        {
            printf("没后继\n");
        }        
    }
    printf("clear list\n");
    ClearList_Sq(sq);
    printf("sq是否为空：%d（0为空，1为非空）\n",ListEmpty_Sq(sq));
    DestoryList_Sq(&sq);
    system("pause");
    return 0;
}

