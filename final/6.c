/*
    [问题描述]
    利用普利姆算法和克鲁斯卡尔算法实现最小生成树问题。
    [基本要求]
    （1）自行建立图的数据文件，第一行是顶点个数，然后依次是顶点名，接下来是边，用float表示边的权值；
    （2）以邻接表或者邻接矩阵表示图皆可；
    （3）分别利用prim和Kruskal算法实现最小生成树；
    （4）输出最小生成树的权值之和，及所用的边。
    数据结构：邻接矩阵
*/
#include <stdio.h>
#include<stdlib.h>

#define  SELECTED 1
#define INABLE -1
#define ABLE 0

#define INFINITY 999//最大值，在有向图中表示没有边
#define MAX_VERTEX_NUM 20
typedef enum{DG = 1,DN,UDG,UDN} GraphKind;
//有向图，有向网，无向图，无向网
typedef double VRType;
//顶点类型 无权是1/0表示是否相邻
//网是有权值，不相邻是999,默认总权值为100%,省略0和负数
typedef char InfoType ;

typedef struct ArcCell
{
    VRType adj;
    InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM + 1][MAX_VERTEX_NUM + 1];
/*
    AdjMatrix[0][X] AdjMatrix[X][0]不用 还可以放其他的信息
    AdjMatrix[0][0]表示边个数 
    AdjMatrix[x][0]表示顶点邻接节点的个数(x >= 1) 
*/
typedef int VertexType;

typedef struct 
{
    //顶点
    VertexType Vertexes[MAX_VERTEX_NUM + 1];//用数字编号 vertexes[0]不用
    //邻接矩阵
    AdjMatrix arcs;
    //点边的数量
    int VexNum,ArcNum;
    GraphKind kind;
}MGraph;

//下面是图的有关操作
int CreateUDN(MGraph *graph);
int CreateGraph(MGraph **graph);
int DestoryGraph(MGraph *graph);
int LocateVex(MGraph graph,int value);
/*
    因为这里的邻接矩阵是前面写过的
    所以这里偷懒直接复制了，所以不支持文件输入
*/
//下面是主要算法
int kruskal(MGraph graph);
int prime(MGraph graph);
int main()
{
    MGraph *graph;
    CreateGraph(&graph);
    printf("kruskal\n");
    kruskal(*graph);
    printf("prime\n");
    prime(*graph);
    system("pause");
    return (0);
}

int prime(MGraph graph)
/*
    主要思想：
    1，选择一个点作为起始点，加入集合
    2，将和集合内点相邻的最小权值点加入路径，并更新各个点到集合的总权值
    3，重复2
*/
{
    //graph . ArcNum <= 1 不用处理
    if (graph . ArcNum == 1 || graph . ArcNum  == 0)
    {
        printf("顶点过少");
        return (1109);
    }
    float *weight;
    //始点到各个点的权值
    //没有就是infinity
    int i,j,l,ver_value,ver,*vers[2];
    weight = (float * )calloc(graph . ArcNum + 1,sizeof(float));
    //【0】不用
    for ( i = 0; i < 2; i++)
    {
        vers[i] = (int * )calloc(graph . ArcNum + 1,sizeof(int));
    }
    /*
        vers[1][0]放有没加入集合
        vers表示顶点的信息 
        表示顶点的信息 
        vers[1][x] == 0 表示不在集合内
        因为是直接建图的，所以直接读前 graph . VexNum个
    */
    for (int i = 1; i <= graph.VexNum; i++)
    {
        vers[0][i] = graph .Vertexes[i];
    }
    for (size_t i = 0; i <= graph . VexNum; i++)//对weight进行初始化，初始为infinity
    {
        weight[i] = INFINITY ;
    }
    //           vers[1][0]放有没加入集合
    vers[1][0] = graph . VexNum ;
    //顶点集合对应顶点的值
    printf("请输入始点的值\n");
    scanf("%d",&ver_value);
    //定位ver
    ver = LocateVex(graph , ver_value);
    vers[1][ver] = 1;
    vers[1][0] -- ;
    weight[ver] = 0;//初始顶点为0
    int last_into_set;
    last_into_set = ver;
    while ( vers[1][0])
    {
        //开始维护数组
        //只要对新加入的点进行就可以
        for ( i = 1; i <= graph . VexNum ; i++)
        {
            if(vers [1][i] == 0 && graph . arcs[last_into_set][i] . adj  + weight[last_into_set] < weight[i])
            //更新条件
            //1：不在集合内
            //2：新的总权值更小
            {
                weight[i] = graph . arcs[last_into_set][i] . adj + weight[last_into_set];
            }
        }
        //下面开始找到最小的
        int min_of_weight = INFINITY,min = -1;
        for ( i = 1; i <= graph . VexNum ; i++)
        {
            if (vers [1][i] == 0 && weight[i] < min_of_weight)
            {
                min = i ;
                min_of_weight = weight[i];
            }
        }
        //找到了
        last_into_set = min;
        vers[1][last_into_set] = 1;
        vers[1][0] -- ;
    }
    for ( i = 1; i <= graph . VexNum ; i++)
    {
        //
        printf("顶点%d的权值是:%f\n",vers[0][i],weight[i]);
    }

    for ( i = 0; i < 2 ; i++)
    {
        free(vers[i]);
    }
    free(weight);
    return (15);
}

int check(int *help[4],int i,int j,int count_of_ver,int count_of_arc)
{
    //开始判断是在同连通
    int a[80] = {0};
    int state1,state2;
    for ( int k = 1; k <= count_of_arc; k++)
    {
        state1 = state2 = 0;
        if(help[1][k] == SELECTED)
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


int kruskal(MGraph graph)
{
    //graph . ArcNum <= 1 不用处理
    if (graph . ArcNum == 1 || graph . ArcNum  == 0)
    {
        printf("顶点过少");
        return (1109);
    }
    int i ,j,*tree,a,statue,statue1 ,k,*help[4];//帮忙辅助的数组
    float *weight,q;
    /*
        help为边集合
        help【1】【x】表示是否在tree内且能否被选取,详细看define
        help【2】【x】和help【3】【x】表两个顶点
        weight[]表示权值
        help[0][x]不用
        help[x][0]不用
         weight[0]不用
    */
    tree =  (int * ) calloc( graph .VexNum +  1 , sizeof(int *));
    //tree[0]不用
    //tree是最小生存树 
    weight =  (float * ) calloc( graph . ArcNum + 1 , sizeof(float ));
    for ( i = 0; i < 4 ; i++)//边集合
    {
        help[i] =  (int * ) calloc( graph . ArcNum + 1 , sizeof(int ));
    }
    k =  graph .ArcNum;//k赋值为边的数量
    //下面开始初始化help数组
    //因为【0】不用，所以i = 1；
    for ( i = 1; i <= graph .VexNum; i++)
    {
        for ( j = i + 1;j <= graph .VexNum ; j++)//因为无环的连通无向网
        {
            if(graph . arcs[i][j] . adj  && graph . arcs[i][j] . adj != INFINITY)
            {
                help[2][k ] = i;
                help[3][k ] = j;
                weight[k --] = graph . arcs[i][j] . adj;
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
    //因为k避圈法是先选最小的边
    for ( i = 1; i <=  graph . ArcNum; i ++)
    {
        for( j = i + 1; j <= graph . ArcNum; j ++)
        {
            if( weight[i] >  weight[j])
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
                
                q =  weight[i];
                weight[i] =  weight[j];
                weight[j] = q;
            }
        }
    }
    k = 1;
    for (i = 1; i <= graph . ArcNum ; i++)
    {
        if(help[1][i] == 0)
        {
            help[1][i] = 1;
            //下面开始加点入tree
            //tree是顶点集
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
            for (j = 1; j <= graph . ArcNum ; j++)
            {
                statue = statue1 = 1;
                for (a = 1; a <= graph . ArcNum ; a++)
                {
                    if(tree[a] == help[2][j])
                        statue = 0;
                }
                for (a = 1; a <= graph . ArcNum ; a++)
                {
                    if(tree[a] == help[3][j])
                        statue1 = 0;
                }
                if(!statue1 && !statue && help[1][j] != 1 && check(help,help[2][j],help[3][j],graph.VexNum,graph.ArcNum))
                {
                    help[1][j] = -1;
                }
            }
        }
    }
    /*for (i = 1; i <= graph . ArcNum; i++) 
    {

            printf("%d %d %d %d\n",help[0][i],help[1][i],help[2][i],help[3][i]); 
    }*/
    float total_weights = 0;
    for (i = 1; i <= graph . ArcNum ; i++)
    {
        if(help[1][i] == 1)
            total_weights +=  weight[i];
    }
    printf("总权值是%0.3f\n",total_weights);
    printf("路径是:\n");
    for (i = 1; i <= graph . ArcNum; i++) 
    {
        if(help[1][i] == 1)
        {
            printf("顶点%d到顶点%d\n",help[2][i],help[3][i]);
        }        
    }
    for ( i = 0; i < 4 ; i++)
    {
        free(help[i]);
    }
    free(tree);
    return (16);
}

int CreateUDN(MGraph *graph)
//无向网
{
    if(!graph) return 0;
    int i,j,ver1,ver2;
    for ( i = 1; i <= MAX_VERTEX_NUM; i++)
    {
        for ( j = 1; j <= MAX_VERTEX_NUM ; j++)
        {
            graph -> arcs[i][j].adj = INFINITY;
        }   
    }
    printf("请输入点边的数量,点不超过20\n");
    scanf("%d",&(graph -> VexNum));
    printf("请输入各个顶点的信息：\n");
    for( i = 1 ; i <= graph -> VexNum ; i++)
    {
        scanf("%d",&j);
        ( graph -> Vertexes )[i] = j;
    }
    printf("现在输入边信息，以#结尾\n");
    for( i = 1 ; getchar() != '#'; i++)
    {
        float weight;
        printf("请输入始点、终点和权:\n");
        scanf("%d %d %f",&ver1,&ver2,& weight);
        //因为是有向无权图
        for ( i = 1; i <= graph -> VexNum ; i++)
        {
            if(graph -> Vertexes[i] == ver1) break;    
        }
        for ( j = 1; j <= graph -> VexNum ; j++)
        {
            if(graph -> Vertexes[j] == ver2) break;    
        }
        ver1 = i;
        ver2 = j;
        graph ->arcs[ver1][ver2].adj = graph ->arcs[ver2][ver1].adj = weight;

        graph ->arcs[0][0].adj += 1;
        graph ->arcs[ver1][0].adj += 1;
        graph ->arcs[ver2][0].adj += 1;
        //因为这个这我这里没有什么用，所以这里注解掉，要用激活即可
        /*
            char *info;
            printf("请输入边的信息");
            scanf("%s",info);
            strcpy( graph ->arcs[ver1][ver2].info,info);
            strcpy( graph ->arcs[ver2][ver1].info,info);
        */
    }
    graph -> ArcNum = graph ->arcs[0][0].adj;
    return (1);
}

int CreateGraph(MGraph **graph)//默认graph = 0
{
    MGraph *newbase;
    newbase = (MGraph *)calloc(1,sizeof(MGraph));
    if(!newbase) return (0);
    *graph =newbase;
    GraphKind kind;
    (*graph) -> kind = UDN ;
    switch ((*graph) ->kind)
    {
        case UDN:CreateUDN(*graph);break;
    }
    return 0;
}

int DestoryGraph(MGraph *graph)
{
    free(graph);
    return 0;
}

int LocateVex(MGraph graph,int value)
//将返回在数组中的位置
{
    for (int i = 1; i <= MAX_VERTEX_NUM ; i++)
    {
        if(graph.Vertexes[i] == value)
        return (i);
    }
}

int GetVex(MGraph graph,int ver)
//ver为点在数组中的位置
{
    return (graph.Vertexes[ver]);
}

int PutVex(MGraph *graph,int ver)
//ver为点在数组中的位置
{  
    printf("请输入值；\n");
    scanf("%d",&(graph ->Vertexes[ver]));
    return 4;
}
