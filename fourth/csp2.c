#include<stdio.h>
#include<stdlib.h>
#define PLATOON 20//platoon��
#define SEAT 5//ÿ�ŵ���λ
static int CRH[PLATOON + 1][SEAT + 1] ;
//CRH��x����0����ʾ���ܿ�λ�ã�CRH��0����0����ʾ�ܿ�λ�� = 0��ʾ��
int BuyTicket(int CRH[PLATOON + 1][SEAT + 1],int tickets);

int main()
{
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n");
    int times,tickets,i,j;
    //��ʼ��crh
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
                CRH[i][j] = 0;//��ʾ�� 
            }
            
        }
        
    }
    printf("�������������:\n");
    scanf("%d",&times);
    for( i  = 0;i < times ; i++)
    {   
        printf("������Ҫ����Ʊ:\n");
        scanf("%d",&tickets);
        while(tickets > 5)
        {
            printf("����5�ţ�����������Ҫ����Ʊ:\n");
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
        printf("��Ʊ");
        return (0);
    }
    CRH[0][0] -= tickets;
    for(i = 1; i < PLATOON + 1 ; i++)//��ͬһ�ž�ͬһ��
    {
        if(CRH[i][0] >= tickets)
        {
            CRH[i][0] -= tickets;
            for(k = tickets,j = 1; k > 0 ;j++)
            {
                if(CRH[i][j] == 0)
                {
                    printf("%d ", (i - 1) * SEAT + j);//�����λ���
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
    if(!state)//�����ܷ���һ��
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
                        printf("%d ", (i - 1) * SEAT  + j);//�����λ���
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