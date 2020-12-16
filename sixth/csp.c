#include<stdio.h>
#include<stdlib.h>
/*
    球用ball【x】【4】存信息
    ball [x][3]编号
    ball【x】【0】 速度
    ball【x】【1】 位置
    ball【x】【2】 运动方向 //右+（1）表示 左负（-1）表示
    ball[0][1] 下界；
    ball【x + 1】【1】 上界
    主要是为了第1个和最后一个普通化
*/

int Calculate(int **ball,int time, int Number_of_ball);
int main()
{
    int i ,j,min,k,time,Length,ball_position,ball_velocity,Number_of_ball;
    int **ball;
    int *position[2];
    printf("请输入有多少小球，线段长度和时间\n");
    scanf("%d%d%d",&Number_of_ball,&Length,&time);
    //下面开始初始化
    ball = (int ** )calloc(Number_of_ball + 2,sizeof(int *));
    position[0] = (int * )calloc(  Number_of_ball + 2,sizeof(int));
    position[1] = (int * )calloc(  Number_of_ball + 2,sizeof(int));
    //下界
    ball[0] = (int * )calloc( 4 ,sizeof(int));
    //处理上界
    ball[Number_of_ball + 1] = (int * )calloc( 4 ,sizeof(int));
    ball[Number_of_ball + 1][1] = Length;
    
    for(i = 1 ; i <= Number_of_ball ; i++)
    {
        ball[i] = (int * )calloc( 4 ,sizeof(int));
        ball[i][2] = 1;
        ball[i][0] = 1;
        //因为是calloc，下界是0，所以不用处理
    }

    //因为每个球的相对位置不会变
    //所以将位置进行排序，直接冒泡排
    for(i = 1 ; i <= Number_of_ball ; i++)
    {
        printf("请输入位置\n");
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
    //初始化完成
    Calculate(ball,time,Number_of_ball);
    for(i = 1 ; i <= Number_of_ball ; i++)
    {  
        for(j = 1 ; j <= Number_of_ball ; j++)
        {
            if(ball[j][3] == i)  
                printf("小球%d现在在%d\n",(i),ball[j][1]);
        }
    }
    system("pause");
    return (0);
}
int Calculate(int **ball,int time,int Number_of_ball)
//一个for循环，只不过每次要对n个球都进行判断
//因为要和左右的球比过去 所以时间复杂度O(n * time)
//借助judge数组判断是否经过了处理
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
        //算第i秒初始时刻的状态
        for(j = 1; j <= Number_of_ball ; j++ )
        {
            ball[j][1] +=  ball[j][2];
        }
        //开始判断
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