#include<stdio.h>
#include<stdlib.h>
#define PLATOON 20//platoon排
#define SEAT 5//每排的座位
static int CRH[PLATOON + 1][SEAT + 1] ;
//CRH【x】【0】表示排总空位置，CRH【0】【0】表示总空位， = 0表示空
int BuyTicket(int CRH[PLATOON + 1][SEAT + 1],int tickets);

int main()
{
    printf("中文使用的是GBK。Simplified Chinese using GBK.\n");
    int times,tickets,i,j;
    //初始化crh
    for( i  = 0;i < PLATOON + 1 ; i++)
    {
        if( i == 0)
        {
            CRH[0][0] = 100;
            continue ;
        }
        for (j = 0; j < SEAT + 1; j++)
        {
            if( j == 0)
            {
                CRH[i][0] = 5;
                continue ;
            }
            else
            {
                CRH[i][j] = 0;//表示空 
            }
            
        }
        
    }
    printf("请输入操作次数:\n");
    scanf("%d",&times);
    for( i  = 0;i < times ; i++)
    {   
        printf("请输入要买几张票:\n");
        scanf("%d",&tickets);
        while(tickets > 5)
        {
            printf("超过5张！请重新输入要买几张票:\n");
            scanf("%d",&tickets);
        }
        BuyTicket(CRH,tickets);
    }
    system("pause");
    return(0);
}


int BuyTicket(int CRH[PLATOON + 1][SEAT + 1],int tickets)
{
    int i,j,k,state = 0;
    if(CRH[0][0] < tickets)
    {
        printf("无票");
        return (0);
    }
    CRH[0][0] -= tickets;
    for(i = 1; i < PLATOON + 1 ; i++)//能同一排就同一排
    {
        if(CRH[i][0] >= tickets)
        {
            CRH[i][0] -= tickets;
            for(k = tickets,j = 1; k > 0 ;j++)
            {
                if(CRH[i][j] == 0)
                {
                    printf("%d ", (i - 1) * SEAT + j);//输出座位编号
                    CRH[i][j] = 1;
                    k --;
                    tickets --;
                }
                if(k == 0)
                {
                    break;
                }
            }
            state = 1;
        }
        if(!tickets)
        {
            break ;
        }
    }
    if(!state)//处理不能放在一排
    {
        for(i = 1; i < PLATOON + 1 ; i++)
        {
            if(CRH[i][0] )
            {
                tickets -= CRH[i][0];
                for(j = 1; j < SEAT + 1 ;j ++)
                {
                    if(CRH[i][j] == 0)
                    {
                        printf("%d ", (i - 1) * SEAT  + j);//输出座位编号
                        CRH[i][j] = 1;
                    }
                }
            }
            if(!tickets)
            {
                break ;
            }
        }
    }
    printf("\n");
    return (1);
}