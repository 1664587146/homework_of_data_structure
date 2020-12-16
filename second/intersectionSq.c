#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct//�򻯲�������int
{
    int a;
}Elemtype;

typedef struct
{
    Elemtype *elem;
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
}//������

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
}//���� 

int ClearList_Sq(Sqlist* l)
{
    if(l == 0) exit(0);
    else
    {
        l->length = 0;
        return 0;
    }
}//��ձ�

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
}//�ж��Ƿ�Ϊ��

int GetElem_Sq(Sqlist* l , int i,Elemtype *e)
{
    if(l == 0) exit(0);
    else
    {
        *e = *(l->elem + i - 1);
    }
    return (1);
}//�õ���i��Ԫ��ֵ

int compare( Elemtype *e1, Elemtype *e2 )
{
    if(e1 -> a == e2 -> a)
    {
        return 0;
    }
    return 1;//һ��ʾ�����
}//����һ����

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
    return (-1);//�Ҳ�����-1��ʾ
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

int 
ListInsert_Sq(Sqlist *l,int i ,Elemtype e)
//��i��λ��֮ǰ
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
//ɾ����i��
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
            if(!printf("���Ԫ���� : %d\n", (l ->elem + i) -> a))
        {
            exit (0);
        }
    }
    return 0;
}
//��Ϊû��Ҫ���ļ����о�û���ļ�
int intersection(Sqlist a,Sqlist b ,Sqlist *c)
{
    if(c == 0) return 0;
    int positionA,positionB,positionC;
    Elemtype data;
    for( positionA = positionB = positionC = 0; positionA <a.length || positionB < b.length; )
    {
        if((a.elem + positionA) -> a > (b.elem + positionB) -> a ){ positionB ++;  continue;      }
        if((a.elem + positionA) -> a == (b.elem + positionB) -> a )
        {
            data.a =(a.elem+positionA)->a;
            ListInsert_Sq(c,++positionC,data);
            positionA ++; 
            positionB ++ ;
            continue; 
        }    
        if((a.elem + positionA) -> a < (b.elem + positionB) -> a ){ positionA ++ ; continue; }
    }
    return (13);
}

int order(Sqlist *sq)
{
    if(sq == 0) exit(0);
    int i,cur,cir,position;
    Elemtype *minNowData;
    for(i = 0; i < sq -> length;i ++)
    {
        for(cir = i, minNowData -> a = (sq ->elem +cir) ->a ;cir <sq ->length; cir ++)
        {
            if(minNowData -> a >(sq ->elem +cir) ->a ) minNowData -> a = (sq ->elem +cir) ->a; 
        }
        position = LocateElem_Sq(sq,*minNowData,compare);
        ListDelete_Sq(sq,position,minNowData);
        ListInsert_Sq(sq, i+1 ,*minNowData );
    }
    return (12);
}//��������

int main()
{
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n");
    Sqlist *sqA,*sqB,*sq;
    Elemtype elem,elem1;
    InitList_Sq(&sqA);
    InitList_Sq(&sqB);
    InitList_Sq(&sq);
    int i ;
    printf("����A(elemtype��ֻ��һ��int��,��#��β)\n");
    for(i = 1;;)
    {
        scanf("%d",&elem.a);
        ListInsert_Sq(sqA,i++,elem);
        if(getchar() == '#')
        {
            break;
        }
    }
    order(sqA);
    printf(" ok ������ʾA����Ԫ��\n");
    ListTraverse_sq(sqA);
    printf("����B(��elemtype��ֻ��һ��int��,��#��β)\n");
    for(i = 1;;)
    {
        scanf("%d",&elem.a);
        ListInsert_Sq(sqB,i++,elem);
        if(getchar() == '#')
        {
            break;
        }
    }
    order(sqB);
    printf(" ok ������ʾB����Ԫ��\n");
    ListTraverse_sq(sqB);
    printf("��c�����ӽ���");
    if(intersection(*sqA,*sqB,sq))
    {
        printf(" ok ������ʾC����Ԫ��\n");
        ListTraverse_sq(sq);
    }
    system("pause");
    return 0;
}
