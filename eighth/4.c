#include <stdio.h>
#include<stdlib.h>
#define MAX_LENGTH 80
void HeapAdjust(int a[],int s,int m)//һ��ɸѡ�Ĺ���
{
    int rc,j;
    rc = a[s];
    for(j = 2 * s;j <= m;j = j * 2)//ͨ��ѭ���ؽϴ�ĺ��ӽ������ɸѡ
    {
        if(j<m&&a[j]<a[j + 1]) j ++;//jΪ�ϴ�ļ�¼���±�
        if(rc > a[j]) break;
        a[s] = a[j];s = j;
    }
    a[s] = rc;//����
}
void HeapSort(int a[],int n)
{
    int temp,i,j;
    for(i = n / 2;i > 0;i -- )//ͨ��ѭ����ʼ������
    {
        HeapAdjust(a,i,n);
    }
    for(i = n;i > 0;i -- )
    {
        temp = a[1];
        a[1] = a[i];
        a[i] = temp;//���Ѷ���¼��δ��������һ����¼����
        HeapAdjust(a,1,i - 1);//���µ���Ϊ����
    }
}
int main()
{
    int n = 0,i;
    printf("��С����\n");
    printf("������������#��β:\n");
    int a[MAX_LENGTH + 1];
    for(i = 1;;i ++)
    {
        scanf("%d",&a[i]);
        n ++;
        if(getchar() == '#')
        {
            break;
        }
    }
    HeapSort(a,n);
    for ( i = 1; i <= n; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");    
    system("pause");
    return 0;
}

