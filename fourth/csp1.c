#include<stdio.h>
#include<stdlib.h>
#define MAX 10001//��Ŀ�����9999�����ѵ�0���ã����Թ涨10001
//�ö��Ľ���O(n)
int main()
{
    int stack[MAX] = {0},n,j,i,total = 0;//stackҪ��ʼ��
    printf("How many numbers you want to scan:\n");
    scanf("%d",&n);
    printf("Scan the numbers you want:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d",&j);
        stack[j] ++; 
    }
    for(i = 1; i < MAX; i++)//����
    {
        if(stack[i - 1]  && stack[i] ) total++;
    }
    printf("һ����%d��\n",total);
    system("pause");
    return 0;
}