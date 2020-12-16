#include<stdio.h>
#include<stdlib.h>
#define MAX 10001//题目中最多9999个但堆第0不用，所以规定10001
//用堆拍降到O(n)
int main()
{
    int stack[MAX] = {0},n,j,i,total = 0;//stack要初始化
    printf("How many numbers you want to scan:\n");
    scanf("%d",&n);
    printf("Scan the numbers you want:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d",&j);
        stack[j] ++; 
    }
    for(i = 1; i < MAX; i++)//查找
    {
        if(stack[i - 1]  && stack[i] ) total++;
    }
    printf("一共有%d个\n",total);
    system("pause");
    return 0;
}