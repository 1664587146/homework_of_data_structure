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

int InitList_Sq(Sqlist *(*l))//lΪָ��
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
}//������

int ListInsert_Sq(Sqlist *l,int i ,int e)
//��i��λ��֮ǰ
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
//ɾ����i��
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
            printf("��%d����ȥ����%d��\n",(i+1), *(sq->elem+i));    
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
                printf("��%d����ȥ����%d��\n",k ++, l);
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
����������n��m��m<n��������n��������һȦ���ӵ�1���˿�ʼѭ������������m���˳��У�
Ȼ���ٴ���һ���˿�ʼ����������m�����ֳ��У�����ظ���ֱ�����е��˶�����Ϊֹ��
Ҫ������ʽ�ṹ��˳��ṹʵ�֣������е��Ⱥ�˳�����ÿ���˵���Ϣ��
*/


int main()
{
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n");
    Sqlist *sq;
    int elem,elem1;
    int m,n,k;
    InitList_Sq(&sq);
    printf("�����������ͺ�����");
    scanf("%d %d",&n,&m);
    while(m < 0 || n < 0)
    {
        printf("����������������");
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
