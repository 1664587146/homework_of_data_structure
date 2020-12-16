/*
    [问题描述]
    一副扑克牌的每张牌表示一个数（J、Q、K分别表示11、12、13，两个司令都表示6）。任取4张牌，即得到1-13的数，请添加运算符（规定为加、减、乘、除四种）使之成为运算式。每个数只能参与一次运算，4个数顺序可以任意组合，4个运算符任意取3个且可以重复取。运算遵从一定有限级别，可加括号控制，最终使运算结果为24.请输出一种解决方案的表达式，用括号表示运算优先。如果没有解决方案，则输出-1表示无解。 
    [基本要求]
    （1）输入说明：在一行中给出4个整数，每个整数取值范围是[1, 13].
    （2）输出说明：输出一种解决方案的表达式，用括号表示运算优先，如果没有解决方案，则输出-1。
    （3）测试用例： 输入  2 3 12 12  输出 （（3-2）*12）+12 
    （4）可选要求：输入采用随机生成4个整数， 输出要求输出该4个整数所有可能的解决方案。
*/
#include<stdio.h>
#include<stdlib.h>
static char oper[4] = { '+', '-' , '*' , '/' };
static int  factor_of_24[6] = {2,3,4,6,8,12};

#define NUMBER_OF_OPERATOR 4

float Circulate(float a,char theta,float b)
//二运算的函数
//下面check要
{   
	if(theta=='+')
        return(a+b);
	if(theta=='-')
        return(a-b);
	if(theta=='*')
        return(a*b);
	if(theta=='/')
    {
        if(b == 0)
        {
            return(INT_MIN);
        }
        else
            return(a/b); 
    }
}

float check(int* number)
//主要算法：穷举
//根据排列组合原理，可能有5种不同的，有效的加括号方式
//下面开始处理
{
    int i,j,k;
    float l,a;
    //((A opi B) opj C) opk D
    for ( i = 0; i < NUMBER_OF_OPERATOR ; i++)
    {
        for ( j = 0; j < NUMBER_OF_OPERATOR; j++)
        {
            for ( k = 0; k < NUMBER_OF_OPERATOR; k++)
            {
                l = Circulate(number[0],oper[i],number[1]);
                l = Circulate(l,oper[j],number[2]);
                l = Circulate(l,oper[k],number[3]);
                if(l == 24)
                {
                    printf("((%d %c %d) %c %d) %c %d = 24\n",number[0],oper[i],number[1],oper[j],number[2] ,oper[k],number[3]); 
                    return(1);
                }
            }
        }
    }
    //(A opi (B opj C)) opk D
    for ( i = 0; i < NUMBER_OF_OPERATOR ; i++)
    {
        for ( j = 0; j < NUMBER_OF_OPERATOR; j++)
        {
            for ( k = 0; k < NUMBER_OF_OPERATOR; k++)
            {
                l = Circulate(number[1],oper[j],number[2]);
                l = Circulate(l,oper[i],number[0]);
                l = Circulate(l,oper[k],number[3]);
                if(l == 24)
                {
                    printf("(%d %c (%d %c %d)) %c %d = 24\n",number[0],oper[i],number[1],oper[j],number[2] ,oper[k],number[3]);
                    return(2);
                }
            }
        }
    }
    //A opi (B opj (C opk D))
    for ( i = 0; i < NUMBER_OF_OPERATOR ; i++)
    {
        for ( j = 0; j < NUMBER_OF_OPERATOR; j++)
        {
            for ( k = 0; k < NUMBER_OF_OPERATOR; k++)
            {
                l = Circulate(number[3],oper[k],number[2]);
                l = Circulate(l,oper[j],number[1]);
                l = Circulate(l,oper[i],number[0]);
                if(l == 24)
                {
                    printf("%d %c (%d %c (%d %c %d)) = 24\n",number[0],oper[i],number[1],oper[j],number[2] ,oper[k],number[3]);
                    return(3);
                }
            }
        }
    }    
    //A opi ((B opj C) opk D)
    for ( i = 0; i < NUMBER_OF_OPERATOR ; i++)
    {
        for ( j = 0; j < NUMBER_OF_OPERATOR; j++)
        {
            for ( k = 0; k < NUMBER_OF_OPERATOR; k++)
            {
                l = Circulate(number[1],oper[j],number[2]);
                l = Circulate(l,oper[k],number[3]);
                l = Circulate(l,oper[i],number[0]);
                if(l == 24)
                {
                    printf("%d %c ((%d %c %d) %c %d) = 24\n",number[0],oper[i],number[1],oper[j],number[2] ,oper[k],number[3]);
                    return(4);
                }
            }
        }
    }    
    //(A opi B) opj (C opk D)
    for ( i = 0; i < NUMBER_OF_OPERATOR ; i++)
    {
        for ( j = 0; j < NUMBER_OF_OPERATOR; j++)
        {
            for ( k = 0; k < NUMBER_OF_OPERATOR; k++)
            {
                l = Circulate(number[1],oper[i],number[0]);
                a = Circulate(number[2],oper[k],number[3]);
                l = Circulate(l,oper[j],number[0]);
                if(l == 24)
                {
                    printf("(%d %c %d) %c (%d %c %d) = 24\n",number[0],oper[i],number[1],oper[j],number[2] ,oper[k],number[3]);  
                    return(5);
                }
            }
        }
    }    
}

int main()
{
    int choice;//选择模式
    printf("牌按黑桃（Spade）、红桃（Heart）、方块（Diamond）、梅花（Club）排列\n");
    printf("1：手动输入\n2:穷举\n请选择\n");
    scanf("%d",&choice);
    if(choice == 1)
    {
        int number[4];//给手动输入的数字的准备的
        scanf("%d%d%d%d",&(number[0]),&(number[1]),&(number[2]),&(number[3]));
        check(number);
    }
    if(choice == 2)
    {
        //牌一共13个花
        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                for (int k = 0; k < 13; k++)
                {
                    for (int l = 0; l < 13; l++)
                    {
                        int number[4];
                        number[0] = i;
                        number[1] = j;
                        number[2] = k;
                        number[3] = l;
                        check(number);
                    }   
                }   
            }   
        }
    }
    system("pause");
    return (0);
}