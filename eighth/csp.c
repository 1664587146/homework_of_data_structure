#include<stdio.h>
#include<stdlib.h>
#define HASH_NUMBER  1009
int hash(int number,int *Hash_Array)
{
        Hash_Array[number % HASH_NUMBER] ++;        
}

int main()
{
    int Hash_Array[HASH_NUMBER] = {0},i,number,times;
    int output[2][1009] = {0};
    printf("请输入要输入几次:\n");
    scanf("%d",&times);
    while (i < times)
    {
        printf("请输入数字\n");
        scanf("%d",&number);
        hash(number,Hash_Array);
        i++;
    }
    for ( i = 0; i < HASH_NUMBER; i++)
    {
        if (i == 0 &&  Hash_Array[i] != 0)
        {            
            output[0][0]++;
            output[0][output[0][0]] = HASH_NUMBER;
            output[1][output[0][0]] = Hash_Array[i] ;
        }
        
        if( Hash_Array[i] != 0)
        {
            output[0][0]++;
            output[0][output[0][0]] = i;
            output[1][output[0][0]] = Hash_Array[i] ;
        }
    }
    //排序采用冒泡
    for ( i = 1; i <= output[0][0]; i++)
    {
        for ( int j = 1; j <= output[0][0]; j++)
        {
            
            if( output[1][j]  < output[1][j + 1])
            {
                times = output[0][j];
                output[0][j] = output[0][j + 1];
                output[0][j+1] = times ;

                times = output[1][j];
                output[1][j] = output[1][j + 1];
                output[1][j + 1] = times ;
            }
        }
        
    }
    for ( i = 1; i <= output[0][0]; i++)
    {
        printf("%d %d\n",output[0][i],output[1][i]);
    }
    system("pause");
    return 0;
}