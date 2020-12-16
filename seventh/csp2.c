#include <stdio.h>
#include<stdlib.h>
//算法：加边法（避圈法

#define  SELECTED 1
#define INABLE -1
#define ABLE 0

int check(int *help[5],int i,int j,int count_of_ver,int count_of_arc)
{
    //开始判断是在同连通
    int a[80] = {0};
    int state1,state2;
    for ( int k = 1; k <= count_of_arc; k++)
    {
        state1 = state2 = 0;
        if(help[1][k] == 1)
        {
            if (a[help[2][k]] == 0)
            {
                state1 = 1;
            }
            if (a[help[3][k]] == 0)
            {
                state2 = 1;
            }

            if(state1)
            {
                a[help[2][k]] = k;
            }
            else
            {   
                int change = a[help[2][k]];
                for ( int q = 1; q <= count_of_ver; q++)
                {
                    if(a[q] == change)
                        a[q] =k;
                }
            }           

            if(state2)
            {
                a[help[3][k]] = k;
            }
            else
            {
                int change = a[help[3][k]];
                for ( int q = 1; q <= count_of_ver; q++)
                {
                    if(a[q] == change)
                        a[q] = k;
                }
            }

        }
    }
    if (a[i] != a[j])
    {
        return (0);
    }
    else
    {
        return (1);
    }
    
}

void kruskal(int **map)
{
    int i ,j,*tree,a,statue,statue1 ,k,*help[5];//帮忙辅助的数组
    /*
        help为边集合
        help【1】【x】表示是否在tree内且能否被选取,详细看define
        help【2】【x】和help【3】【x】表两个顶点
        help【4】【x】表示权值
    */
    tree =  (int * ) calloc( map[0][0] + 1 , sizeof(int *)); 
    for ( i = 0; i <= map[0][0]; i++)//边集合
    {
        help[i] =  (int * ) calloc( map[0][1] + 1 , sizeof(int ));
    }
    k = map[0][1] ;
    //下面开始初始化help数组
    for ( i = 1; i <= map[0][0]; i++)
    {
        for ( j = i + 1;j <= map[0][0]; j++)//因为无环的连通无向图
        {
            if(map[i][j])
            {
                help[2][k ] = i;
                help[3][k ] = j;
                help[4][k --] = map[i][j];
                if(k == 0)
                {
                    break;
                }
            }
        }
        if(k == 0)
        {
            break;
        }
    }
    //开始给help排序（以权值为主）冒泡
    //这样如果使用快排可以减少O()，因为这里代码量小所以冒泡
    for ( i = 1; i <= map[0][1]; i ++)
    {
        for( j = i + 1; j <= map[0][1]; j ++)
        {
            if(help[4][i] > help[4][j])
            {
                k = help[1][i];
                help[1][i] = help[1][j];
                help[1][j] = k;

                k = help[2][i];
                help[2][i] = help[2][j];
                help[2][j] = k;
                
                k = help[3][i];
                help[3][i] = help[3][j];
                help[3][j] = k;
                
                k = help[4][i];
                help[4][i] = help[4][j];
                help[4][j] = k;
            }
        }
    }

    k = 1;
    for (i = 1; i <= map[0][1] ; i++)
    {
        if(help[1][i] == 0)
        {
            help[1][i] = 1;
            //下面开始加点入tree
            if(tree[0] == 0)
            {
                tree[k ++ ] = help[2][i];
                tree[k ++ ] = help[3][i];
                tree[0] = 2;
            }
            else
            {
                statue = 1;
                for(j = 1; j <= tree[0] ; j++)
                {
                    if(help[2][i] == tree[j]) statue = 0;
                }
                if(statue)
                {
                    tree[k ++] = help[2][i];
                    tree[0] ++ ;
                }
                statue = 1;
                for(j = 1; j <= tree[0] ; j++)
                {
                    if(help[3][i] == tree[j]) statue = 0;
                }
                if(statue)
                {
                    tree[k ++] = help[3][i];
                    tree[0] ++ ;
                }
            }
            //下面开始维护数组help
            //如果arc的两边都在tree内 map【1】【x】 == 1

            for (j = 1; j <= map[0][1] ; j++)
            {
                statue = statue1 = 1;

                for (a = 1; a <= map[0][1]; a++)
                {
                    if(tree[a] == help[2][j] )
                        statue = 0;
                }
                for (a = 1; a <= map[0][1]; a++)
                {
                    if(tree[a] == help[3][j] )
                        statue1 = 0;
                }
                if(!statue1 && !statue && help[1][j] != 1 && check(help,help[2][j],help[3][j],map[0][0],map[0][1]))
                {
                    help[1][j] = -1;
                }
            }
        }
    }
    int total_weights = 0;
    for (i = 1; i <= map[0][1]; i++)
    {
        if(help[1][i] == 1)
            total_weights += help[4][i];
    }
    printf("总权值是%d\n",total_weights);
    for (i = 1; i <= map[0][1]; i++)
    {
        if(help[1][i] == 1)
        {
            printf("麦田%d到%d\n",help[2][i],help[3][i]);
        }        
    }
    for ( i = 0; i < 5 ; i++)
    {
        free(help[i]);
    }
    free(tree);
}

int main()
{
    int **map,ver_num,arc_num,i,j,weight,ver1,ver2;
    printf("请输入顶点数和边数\n");
    scanf("%d%d",&ver_num,&arc_num);
    map = (int ** ) calloc(ver_num + 1 , sizeof(int *));//map[0]不用
    for(int i = 0; i <= ver_num; i++)
    {
       map[i] =  (int * ) calloc( ver_num + 1 , sizeof(int ));
    }
    map[0][0] = ver_num;
    map[0][1] = arc_num;
    /*
        [0][0]顶点数 【0】【1】边数
    */
    while(arc_num --)
    {
        printf("请输入边的两个顶点和权\n");
        scanf("%d%d%d",&ver1,&ver2,&weight);
        map[ver1][ver2] = map[ver2][ver1] = weight;
    }
    kruskal(map);
    free(map);
    system("pause");
    return (0);
}