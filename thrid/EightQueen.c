#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//按行为主序放皇后，所以行不可能一样，在一列斜率为0，在一斜线斜率为+-1，用fabs来限制只有1（简化判断）
void EightQueen();
int main()
{
    EightQueen();
    system("pause");
    return 0;
}

void printSolution(int *x);
int place(int *x,int j)//第j行 是否是正确的位置
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
}//0能 1不能

void EightQueen()
{
    int i,sum = 0,top,x[9]={0};//栈用于存8个的位置，x【0】省去
    top = 1;//top为当前找位置的行
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
    printf("一共有:%d\n",sum);
}

void printSolution(int *x)
{
    int i, j;
    for (i = 1; i <9; i++)    /*输出第i行*/
    {
        for (j=1; j<9; j++)
        {  
            if (j == x[i])    /*第x[i]列输出Q，其他列输出*号 */
                printf("Q");
            else
                printf("*");
        }
        printf("\n");
    }
    printf("\n");
}