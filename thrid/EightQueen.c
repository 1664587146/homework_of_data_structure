#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//����Ϊ����Żʺ������в�����һ������һ��б��Ϊ0����һб��б��Ϊ+-1����fabs������ֻ��1�����жϣ�
void EightQueen();
int main()
{
    EightQueen();
    system("pause");
    return 0;
}

void printSolution(int *x);
int place(int *x,int j)//��j�� �Ƿ�����ȷ��λ��
{
    int i;
    for(i = 1 ;i < j;i ++)
    {
        if((x[i] == x[j]) || (fabs((i - j)) == fabs(x[i] - x[j])))
        {
            return (1);
        }
    }
    return(0);
}//0�� 1����

void EightQueen()
{
    int i,sum = 0,top,x[9]={0};//ջ���ڴ�8����λ�ã�x��0��ʡȥ
    top = 1;//topΪ��ǰ��λ�õ���
    while (top >0)
    {   
        x[top]++;
        while(x[top]<=8 && place(x,top)) x[top]++;
        if(x[top] <= 8)
        {
            if(top == 8)
            {
                printSolution(x);
                x[top]++;
                sum ++;
            }
            else
            {
                top++;
            }
        }
        if(x[top] > 8)
        {
            x[top--] = 0;
        }
    }
    printf("һ����:%d\n",sum);
}

void printSolution(int *x)
{
    int i, j;
    for (i = 1; i <9; i++)    /*�����i��*/
    {
        for (j=1; j<9; j++)
        {  
            if (j == x[i])    /*��x[i]�����Q�����������*�� */
                printf("Q");
            else
                printf("*");
        }
        printf("\n");
    }
    printf("\n");
}