/*
    [��������]
    һ���˿��Ƶ�ÿ���Ʊ�ʾһ������J��Q��K�ֱ��ʾ11��12��13������˾���ʾ6������ȡ4���ƣ����õ�1-13�������������������涨Ϊ�ӡ������ˡ������֣�ʹ֮��Ϊ����ʽ��ÿ����ֻ�ܲ���һ�����㣬4����˳�����������ϣ�4�����������ȡ3���ҿ����ظ�ȡ���������һ�����޼��𣬿ɼ����ſ��ƣ�����ʹ������Ϊ24.�����һ�ֽ�������ı��ʽ�������ű�ʾ�������ȡ����û�н�������������-1��ʾ�޽⡣ 
    [����Ҫ��]
    ��1������˵������һ���и���4��������ÿ������ȡֵ��Χ��[1, 13].
    ��2�����˵�������һ�ֽ�������ı��ʽ�������ű�ʾ�������ȣ����û�н�������������-1��
    ��3������������ ����  2 3 12 12  ��� ����3-2��*12��+12 
    ��4����ѡҪ����������������4�������� ���Ҫ�������4���������п��ܵĽ��������
*/
#include<stdio.h>
#include<stdlib.h>
static char oper[4] = { '+', '-' , '*' , '/' };
static int  factor_of_24[6] = {2,3,4,6,8,12};

#define NUMBER_OF_OPERATOR 4

float Circulate(float a,char theta,float b)
//������ĺ���
//����checkҪ
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
//��Ҫ�㷨�����
//�����������ԭ��������5�ֲ�ͬ�ģ���Ч�ļ����ŷ�ʽ
//���濪ʼ����
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
    int choice;//ѡ��ģʽ
    printf("�ư����ң�Spade�������ң�Heart�������飨Diamond����÷����Club������\n");
    printf("1���ֶ�����\n2:���\n��ѡ��\n");
    scanf("%d",&choice);
    if(choice == 1)
    {
        int number[4];//���ֶ���������ֵ�׼����
        scanf("%d%d%d%d",&(number[0]),&(number[1]),&(number[2]),&(number[3]));
        check(number);
    }
    if(choice == 2)
    {
        //��һ��13����
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