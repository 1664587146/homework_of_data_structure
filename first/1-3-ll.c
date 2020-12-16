#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
//带表头

typedef struct LinkNode
{  
    int data; 
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
        (*l) -> next  =*l;
    } 
    return (1);
}//创建表 成功返回1 失败返回-1

int ListInsert_ll(LinkList l,int i,int e)
//i前
{
    if(e == 1)
    {
        l ->data = 1;
        return 9;
    }
    if(l == 0 ) return(0);
    LinkNode *p,*r;
    int j = 1;
    p = (LinkNode*)malloc(sizeof(LinkNode));
    if(p){  p ->data = e;}
    else{return (-9);}
    p ->next =l ->next; 
    l->next = p ;
    return 9;

}//插入 无效表0 成功9 ，失败-9

int     function(LinkList l,int n,int m)
{
    if(m != 1)
    {
        int i,j = 1;
        LinkList s = l,k;
        for(i = 2 ;(s -> next) != s ; i++)
        {
            if(i == m)
            {
                i %= m;
                k =s->next;
                s ->next = k-> next;
                printf("第%d个出去的是%d号\n",j, k->data);
                if(k != l)
                {
                    free(k);//主程序中的l不能消去
                }
                continue;
            }
            s = s->next;
        }
        printf("最后是%d号\n", s->data);
        return (10);
    }
    else
    {
        int i,j = 1;
        LinkList s = l ,k;
        for(i = 1 ;i <= n ; i++)
        {
            printf("第%d个出去的是%d号\n",j, k->data);
            s = s->next;
        }
        for(k = l,i = 1 ;i <= n ; i++)
        {
            s = k->next;
            free(k);
            k = s;
        }
        return (10);
    }
    
}
/*
输入正整数n、m（m<n），设有n个人坐成一圈，从第1个人开始循环报数，报到m的人出列，
然后再从下一个人开始报数，报到m的人又出列，如此重复，直到所有的人都出列为止。
要求用链式结构和顺序结构实现，按出列的先后顺序输出每个人的信息。
*/
int main()
{
    LinkList l;
    int m,n,k;
    InitList_ll(&l);
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
    //下面做循环链表
    for(k = n ;k > 0 ; k --)
    {
        ListInsert_ll(l,1,k);
    }
    function(l,n,m);
    system("pause");
    return (0);
}