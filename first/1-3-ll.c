#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
//����ͷ

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
}//������ �ɹ�����1 ʧ�ܷ���-1

int ListInsert_ll(LinkList l,int i,int e)
//iǰ
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

}//���� ��Ч��0 �ɹ�9 ��ʧ��-9

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
                printf("��%d����ȥ����%d��\n",j, k->data);
                if(k != l)
                {
                    free(k);//�������е�l������ȥ
                }
                continue;
            }
            s = s->next;
        }
        printf("�����%d��\n", s->data);
        return (10);
    }
    else
    {
        int i,j = 1;
        LinkList s = l ,k;
        for(i = 1 ;i <= n ; i++)
        {
            printf("��%d����ȥ����%d��\n",j, k->data);
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
����������n��m��m<n��������n��������һȦ���ӵ�1���˿�ʼѭ������������m���˳��У�
Ȼ���ٴ���һ���˿�ʼ����������m�����ֳ��У�����ظ���ֱ�����е��˶�����Ϊֹ��
Ҫ������ʽ�ṹ��˳��ṹʵ�֣������е��Ⱥ�˳�����ÿ���˵���Ϣ��
*/
int main()
{
    LinkList l;
    int m,n,k;
    InitList_ll(&l);
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
    //������ѭ������
    for(k = n ;k > 0 ; k --)
    {
        ListInsert_ll(l,1,k);
    }
    function(l,n,m);
    system("pause");
    return (0);
}