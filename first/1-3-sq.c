#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct
{
    int *elem;
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
    (*l)->elem = (int *)calloc(LIST_INIT_SIZE,sizeof(int));
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

int ListInsert_Sq(Sqlist *l,int i ,int e)
//第i个位置之前
{
    if(i < 0 || (i > l->length+1)&&(l -> length != 0))
    {
        exit(0); 
    }
    if(l->length >= l->listsize)
    {
        int* new_base;
        new_base = (int *)realloc(l->elem,(l->length+LISTINCREMENT)*sizeof(int));
        if(new_base == 0)
        {
            exit(1);
        }
        l->elem = new_base;
        l->listsize += LISTINCREMENT;
    }
    int *q,*p;
    q = l->elem + i - 1 ;
    for(p = (l->elem) + (l->length) ;p > q; p -- )
    {
        *p = *(p - 1);
    }
    *q = e;
    l->length ++ ;
    return (0);
}

int ListDelete_Sq(Sqlist *l,int i,int *e)
//删除第i个
{
    if(l == 0 || i > l->length)
    {
        exit (0);
    }
    int *p;
    p = l->elem + i - 1;
    *e = *p;
    for(;i < l->length; i++)
    {
        *p = *(p + 1);
        p++;
    }
    l->length --;
    return 0;
} 

int function(Sqlist* sq,int n, int m)
{
    if(sq == 0 )
    {
        return 0;
    }
    int i,j,k,l;
    i = j = 0;
    if(m == 1)
    {
        for(i = 0 ;i < sq->length ; i++)
        {
            printf("第%d个出去的是%d号\n",(i+1), *(sq->elem+i));    
        }
    }
    else
    {
        k = 1;
       for(i = 0, j =1 ; sq->length ;j++ )
        {
            if(j == m)
            {
                j %= m;
                ListDelete_Sq(sq,i +1 ,&l);
                printf("第%d个出去的是%d号\n",k ++, l);
                i -= 1;
                if(sq->length == 0)
                {
                    break;
                }
                if( i > sq->length )
                {
                    i = 0;
                } 
            }
            {
                 i = (++i) % (sq->length);
            }
        }
    }
    
}
/*
输入正整数n、m（m<n），设有n个人坐成一圈，从第1个人开始循环报数，报到m的人出列，
然后再从下一个人开始报数，报到m的人又出列，如此重复，直到所有的人都出列为止。
要求用链式结构和顺序结构实现，按出列的先后顺序输出每个人的信息。
*/


int main()
{
    printf("中文使用的是GBK。Simplified Chinese using GBK.\n");
    Sqlist *sq;
    int elem,elem1;
    int m,n,k;
    InitList_Sq(&sq);
    printf("请输入人数和和数字");
    scanf("%d %d",&n,&m);
    while(m < 0 || n < 0)
    {
        printf("请输入请重新输入");
        scanf("%d %d",&n,&m);
        if(m < 0 && n < 0)
        {
            break;
        }
    }    
    for(k = n ;k > 0 ; k --)
    {
        ListInsert_Sq(sq,1,k);
    }
    function(sq,n,m);
    system("pause");
    return 0;
}
