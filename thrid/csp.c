#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100 //��ʼ��ַ��С
#define STACKINCREMENT 10//����

int main()
{
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n");
    int i,n,j,elem,*x;
    printf("������������:\n");
    scanf("%d",&n);
    x = (int *)malloc(sizeof(int) * n);
    for(i = 0; i < n ; i++)
    {
        scanf("%d",(x+i));
    }
    for (i = 0; i < n; i++ )
    {
        for (j = 0; j < n; j++ )
        {
            if(*( x + i )> *(x + j))
            {
                elem = *( x + i );
                *( x + i ) = *(x + j);
                *(x + j) = elem;
            }
        }
    }
    if(n%2)
    {
        if(*(x + n / 2) == *(x + n / 2 - 1) ||*(x + n / 2) == *(x + n / 2 + 1) )
        {
            elem = -1;
        }
        else
        {
            elem = *(x + n / 2);
        }
    }
    else
    {
        if(*(x + n / 2) == *(x + n / 2 - 1))
        elem = *(x + n / 2);
        else
        {
            elem = -1;
        }
    }
    printf("%d",elem);
    system("pause");
    return (0);
}