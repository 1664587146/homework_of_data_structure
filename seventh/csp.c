#include <stdio.h>
#include<stdlib.h>
int a[4][4];//表示棋盘
//主要算法：对抗搜索
int judge(int user)
{
    for(int i = 1 ; i <= 3;i ++)
    {
        if(a[i][1] == user && a[i][1] == a[i][2] && a[i][1] == a[i][3])
            return 1;
        if(a[1][i] == user && a[1][i] == a[2][i] && a[1][i] == a[3][i])
            return 1;
    }
    if(a[1][1] == user&&  a[1][1] == a[2][2] && a[1][1] == a[3][3])
        return 1;
    if(a[1][3] == user && a[1][3] == a[2][2] && a[1][3] == a[3][1])
        return 1;
    return 0;
}
int blanknum()
{
    int count = 0;
    for(int i = 1;i <= 3;i ++)
        for(int j = 1;j <= 3;j ++)
            if(a[i][j] == 0)
                count ++;
    return count;
}
int cal(int user)
{
    int count = blanknum();
    int sum;
        if(user == 1)
            sum = count + 1;
        else
            sum =- (count + 1);
    return sum;
}
int dfs(int user)
{   //有输赢
    if(user == 1 && judge(2))
        return cal(2);
    if(user == 2 && judge(1))
        return cal(1);
    if( ! blanknum() )//平局
        return 0;
    //模拟每一步
    int max = -1000,min =1000;
    for(int i = 1;i <= 3; i++)
        for(int j = 1;j <= 3;j ++)
        {
            if(a[i][j] == 0)
            {
                a[i][j]=user;
                if(user == 1)
                    {
                        if(max < dfs(2))
                        {
                            max = dfs(2);
                        }
                    }
                if(user==2)
                {
                    if(min > dfs(1))
                        min = dfs(1);
                }
                a[i][j]=0;
            }
        }
    if(user==1)
        return max;
    else
        return min;
}
int main()
{
    int t;
    int i,j;
    printf("请输入次数\n");
    scanf("%d",&t);
    printf("请输入棋盘\n");
    while(t--)
    {
        for(i=1;i<=3;i++)
            {
                for(j=1;j<=3;j++)
                    scanf("%d",&a[i][j]);
            }
        printf("%d\n",dfs(1));//Alice
    }
    system("pause");
    return 0;
}
