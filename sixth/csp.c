#include<stdio.h>
#include<stdlib.h>
/*
    ����ball��x����4������Ϣ
    ball [x][3]���
    ball��x����0�� �ٶ�
    ball��x����1�� λ��
    ball��x����2�� �˶����� //��+��1����ʾ �󸺣�-1����ʾ
    ball[0][1] �½磻
    ball��x + 1����1�� �Ͻ�
    ��Ҫ��Ϊ�˵�1�������һ����ͨ��
*/

int Calculate(int **ball,int time, int Number_of_ball);
int main()
{
    int i ,j,min,k,time,Length,ball_position,ball_velocity,Number_of_ball;
    int **ball;
    int *position[2];
    printf("�������ж���С���߶γ��Ⱥ�ʱ��\n");
    scanf("%d%d%d",&Number_of_ball,&Length,&time);
    //���濪ʼ��ʼ��
    ball = (int ** )calloc(Number_of_ball + 2,sizeof(int *));
    position[0] = (int * )calloc(  Number_of_ball + 2,sizeof(int));
    position[1] = (int * )calloc(  Number_of_ball + 2,sizeof(int));
    //�½�
    ball[0] = (int * )calloc( 4 ,sizeof(int));
    //�����Ͻ�
    ball[Number_of_ball + 1] = (int * )calloc( 4 ,sizeof(int));
    ball[Number_of_ball + 1][1] = Length;
    
    for(i = 1 ; i <= Number_of_ball ; i++)
    {
        ball[i] = (int * )calloc( 4 ,sizeof(int));
        ball[i][2] = 1;
        ball[i][0] = 1;
        //��Ϊ��calloc���½���0�����Բ��ô���
    }

    //��Ϊÿ��������λ�ò����
    //���Խ�λ�ý�������ֱ��ð����
    for(i = 1 ; i <= Number_of_ball ; i++)
    {
        printf("������λ��\n");
        scanf("%d",&position[0][i]);
        position[1][i] = i ;
    }
    for ( i = 1 ; i <= Number_of_ball ; i++)
    {
        for ( j  = i + 1; j  <= Number_of_ball; j++)
        {
            if(position[ 0 ][ j ] < position[ 0 ][ i ])
            {
                k = position[ 0 ][ j ] ;
                position[ 0 ][ j ] = position[ 0 ][ i ]; 
                position[ 0 ][ i ] = k ;
                k = position[ 1 ][ j ] ;
                position[ 1 ][ j ] = position[ 1 ][ i ]; 
                position[ 1 ][ i ] = k ;
                
            }
        }
    }   
    for(i = 1 ; i <= Number_of_ball ; i++)
    {
        ball[i][1] = position[ 0 ][i];
        ball[i][3] = position [1][i];
    }
    //��ʼ�����
    Calculate(ball,time,Number_of_ball);
    for(i = 1 ; i <= Number_of_ball ; i++)
    {  
        for(j = 1 ; j <= Number_of_ball ; j++)
        {
            if(ball[j][3] == i)  
                printf("С��%d������%d\n",(i),ball[j][1]);
        }
    }
    system("pause");
    return (0);
}
int Calculate(int **ball,int time,int Number_of_ball)
//һ��forѭ����ֻ����ÿ��Ҫ��n���򶼽����ж�
//��ΪҪ�����ҵ���ȹ�ȥ ����ʱ�临�Ӷ�O(n * time)
//����judge�����ж��Ƿ񾭹��˴���
{
    int i,j,k;
    int *judge;
    judge = (int * )calloc(  Number_of_ball + 2,sizeof(int));
    for(i = 1 ; i <= time ; i ++)
    {
        for(j = 1 ; j <= Number_of_ball ; j ++)
        {
            judge[j] = 0;
        }
        //���i���ʼʱ�̵�״̬
        for(j = 1; j <= Number_of_ball ; j++ )
        {
            ball[j][1] +=  ball[j][2];
        }
        //��ʼ�ж�
        for(j = 1; j <= Number_of_ball ; j++ )
        {
            if(ball[j - 1 ][1] == ball[j][1])
            {
                if(!judge[j - 1])
                {
                    ball[ j -1 ][2] *= ( -1 );
                    judge[ j - 1] = 1;
                }
                if(!judge[ j ])
                {
                    ball[ j ][2] *= ( -1 );
                    judge[ j ] = 1;
                }
            }
            if(ball[ j ][1] == ball[ j + 1 ][1])
            {
                if(!judge[ j ])
                {
                    ball[ j ][2] *= ( -1 );
                    judge[ j ] = 1;
                }
                if(!judge[ j + 1])
                {
                    ball[ j + 1 ][2] *= ( -1 );
                    judge[ j + 1 ] = 1;
                }
            }
        }
    }
    return 0;
}