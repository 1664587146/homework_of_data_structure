#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INFINITY 999//最大值，在有向图中表示没有边
#define MAX_VERTEX_NUM 20
typedef enum{DG = 1,DN,UDG,UDN} GraphKind;
//有向图，有向网，无向图，无向网
typedef int VRType;
//顶点类型 无权是1/0表示是否相邻
//网是有权值，不相邻是999,默认总权值为100%,省略%
typedef char InfoType ;

typedef struct ArcCell
{
    VRType adj;
    InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM + 1][MAX_VERTEX_NUM + 1];
//AdjMatrix[0][X] AdjMatrix[X][0]不用 还可以放其他的信息
//AdjMatrix[0][0]表示边个数 
//AdjMatrix[x][0]表示顶点邻接节点的个数(x >= 1) 
typedef int VertexType;

typedef struct 
{
    //顶点
    VertexType Vertexes[MAX_VERTEX_NUM + 1];//用数字编号 [0]不用
    //邻接矩阵
    AdjMatrix arcs;
    //点边的数量
    int VexNum,ArcNum;
    GraphKind kind;
}MGraph;

int CreateDG(MGraph *graph)
//创建有向图
{
    if(!graph) return 0;
    printf("请输入点的数量,点不超过20\n");
    scanf("%d",&(graph -> VexNum));
    printf("请输入各个顶点的信息：\n");
    int i,j,k,ver1,ver2;
    for( i = 1 ; i <= graph -> VexNum ; i++)
    {
        scanf("%d",&j);
        ( graph -> Vertexes )[i] = j;
    }
    printf("现在输入边信息，以#结尾\n");
    for( i = 1 ; getchar() != '#' ; i++)
    {
        printf("请输入始点和终点:\n");
        scanf("%d %d",&ver1,&ver2);
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
        graph ->arcs[ver1][ver2].adj = 1;
        graph ->arcs[0][0].adj += 1;
        graph ->arcs[ver1][0].adj += 1;
        //graph ->arcs[ver2][ver1].adj = 1;
        //因为这个这我这里没有什么用，所以这里注解掉，要用激活即可
        /*
            char *info;
            printf("请输入边的信息");
            scanf("%s",info);
            strcpy( graph ->arcs[ver1][ver2].info,info);
        */
    }
    graph ->ArcNum = graph -> arcs[0][0] . adj;
    return (1);
}

int CreateDN(MGraph *graph)
//创建有向网
{
    if(!graph) return 0;
    int i,j,ver1,ver2;
    //网不相邻的为max——int所以将矩阵初始化
    for ( i = 1; i <= MAX_VERTEX_NUM; i++)
    {
        for ( j = 1; j <= MAX_VERTEX_NUM ; j++)
        {
            graph -> arcs[i][j].adj = INFINITY;
        }   
    }
    printf("请输入顶点的数量,顶点不超过20\n");
    scanf("%d00",&(graph -> VexNum));
    printf("请输入各个顶点的信息：\n");
    for( i = 1 ; i <= graph -> VexNum ; i++)
    {
        scanf("%d",&j);
        ( graph -> Vertexes )[i] = j;
    }
    printf("现在输入边信息,以#结尾\n");
    for( i = 1 ; getchar() != '#' ; i++)
    {
        int weight;
        printf("请输入始点、终点和权:\n");
        scanf("%d %d %d",&ver1,&ver2,& weight);
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
        //因为是有向无权图
        graph ->arcs[ver1][ver2].adj = weight;
        graph ->arcs[0][0].adj += 1;
        graph ->arcs[ver1][0].adj += 1;
        //因为这个这我这里没有什么用，所以这里注解掉，要用激活即可
        /*
            char *info;
            printf("请输入边的信息");
            scanf("%s",info);
            strcpy( graph ->arcs[ver1][ver2].info,info);
        */
    }
    graph ->ArcNum = graph -> arcs[0][0] . adj;
    return (1);
}

int CreateUDG(MGraph *graph)
//无向图
{

    if(!graph) return 0;
    printf("请输入点边的数量,点不超过20\n");
    scanf("%d",&(graph -> VexNum));
    printf("请输入各个顶点的信息：\n");
    int i,j,ver1,ver2;
    for( i = 1 ; i <= graph -> VexNum ; i++)
    {
        scanf("%d",&j);
        ( graph -> Vertexes )[i] = j;
    }
    printf("现在输入边信息,以#结尾\n");
    for( i = 1 ; getchar() != '#'; i++)
    {
        printf("请输入始点和终点:\n");
        scanf("%d %d",&ver1,&ver2);
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
        //因为是有向无权图
        graph ->arcs[ver1][ver2].adj  = graph ->arcs[ver2][ver1].adj = 1;
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
    graph -> ArcNum = graph ->arcs [0][0] . adj;
    return (1);
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
        int weight;
        printf("请输入始点、终点和权:\n");
        scanf("%d %d %d",&ver1,&ver2,& weight);
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
    printf("请输入图的类型:\n");
    scanf("%d",&kind);
    (*graph) -> kind = kind ;
    switch ((*graph) ->kind)
    {
        //DG,DN,UDG,UDN
        case DG:CreateDG(*graph);break;
        case DN:CreateDN(*graph);break;
        case UDG:CreateUDG(*graph);break;
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

int FirstAdjVex(MGraph graph , int ver_value)
/*
    这里的ver是value
    第一个就是邻接阵里面第一个值
    返回ver在数组位置 -5表示单独的连通分量
*/
{
    int i,j;
    for (i = 1; i <=  MAX_VERTEX_NUM ; i++)
    {
        if(graph.Vertexes[i] == ver_value)
            break;
    }
    if(graph.arcs[i][0].adj == 0) 
    {
        //printf("无邻接点\n");
        return (-5);
    }
    else
    {
        for ( j = 1; j <= MAX_VERTEX_NUM; j++)
        {
            if(graph.arcs[i][j].adj && graph.arcs[i][j].adj != INFINITY && i !=  j) break;
        }
    }
    //printf("邻接点在数组中是%d个，value是%d\n",j,graph.Vertexes[j]);
    //返回值
    //定位使用locate 或者printf有
    return (j);
} 

int NextAdjVex(MGraph graph,int ver1_value,int ver2_value)
/*
    这里的ver1是value
    返回数组位置 -6表示ver2是最后一个
    以矩阵位置标示邻接点的位置
*/
{
    int ver1,ver2,i,state = 0;
    //定位ver1
    for(ver1 = 1; ver1 <=  MAX_VERTEX_NUM ; ver1++)
    {
        if(graph.Vertexes[ver1] == ver1_value)
            break;
    }
    //定位ver2
    for (ver2 = 1; ver2 <=  MAX_VERTEX_NUM ; ver2++)
    {
        if(graph.Vertexes[ver2] == ver2_value)
            break;
    }
    //下面开始查找
    for ( i = ver2 + 1; i <= MAX_VERTEX_NUM; i++)
    {
        if(graph.arcs[ver1][i].adj && graph.arcs[ver1][i].adj != INFINITY)
        {
            state = 1;    
            break;
        }
    }
    if( state)
    {
        //printf("邻接点在数组中是%d个，value是%d\n",i,graph.Vertexes[i]);
        //返回值
        //定位使用locate 或者printf有
        return (i);        
    }
    else
    { 
        //printf("无邻接点\n");
        return (-6);
    }
}

int InsertArc(MGraph *graph,int ver1_value , int ver2_value)
/*
    先写加边的函数，后面要用
    成功7 失败-7
*/
{
    if(!graph)  return (-7);
    int ver1,ver2,state1 = 0,state2 = 0;
    //定位ver1
    for(ver1 = 1; ver1 <=  MAX_VERTEX_NUM ; ver1++)
    {
        if(graph -> Vertexes[ver1] == ver1_value)
        {
            state1 = 1;
            break;
        }    
    }
    //定位ver2
    for (ver2 = 1; ver2 <=  MAX_VERTEX_NUM ; ver2++)
    {
        if(graph -> Vertexes[ver2] == ver2_value)
        {
            state2 = 1;
            break;
        }    
    }
    if( !state1 || !state2) return (-7);
    switch (graph->kind)
    {
        //下面没有给边信息，如果需要将前面create中的按图类型复制即可
        case(DG)://有向图
        {
            graph ->arcs[ver1][ver2].adj = 1;
            graph ->arcs[0][0].adj ++;
            graph ->arcs[ver1][0].adj += 1;
            break;           
        }
        case(DN)://有向网
        {
            int weight;
            printf("请输入权值");
            scanf("%d",&weight);
            graph ->arcs[ver1][ver2].adj = weight;
            graph ->arcs[0][0].adj ++;
            graph ->arcs[ver1][0].adj += 1;
            break;
        }
        case(UDG):
        {
            graph ->arcs[ver1][ver2].adj = graph ->arcs[ver2][ver1].adj = 1;
            graph ->arcs[0][0].adj ++;
            graph ->arcs[ver1][0].adj += 1;
            graph ->arcs[ver2][0].adj += 1;
            break;           
        }
        case(UDN):
        {
            int weight;
            printf("请输入权值");
            scanf("%d",&weight);
            graph ->arcs[ver1][ver2].adj = graph ->arcs[ver2][ver1].adj = weight;
            graph ->arcs[0][0].adj ++;
            graph ->arcs[ver1][0].adj += 1;
            graph ->arcs[ver2][0].adj += 1;
            break;           
        }
    }
    graph -> ArcNum++ ;
    return (7);
}


int InsertVex(MGraph *graph,int ver_value)
/*
    插入顶点
    没有位置则是返回-9
    有是返回9
*/
{
    int i ,j;
    //开始找是否有空位
    if(graph ->VexNum == MAX_VERTEX_NUM)
    {//无位置
        printf("无可插入位置\n");
        return (-9);
    }
    else
    {
        for(i = 1 ; i <= MAX_VERTEX_NUM ; i++)
        {
            if(graph ->Vertexes[i] == 0)
            {
                graph ->Vertexes[i]=ver_value;
                graph -> VexNum ++;
                break;
            }
        }
        //加边这里考虑单独函数加，因为后面有，而且如果这里加显得过于大。
        int state = 1;
        int ver2_value;
        if(graph-> kind == DN ||graph -> kind == DG)
        {
            while (getchar() != '#')
            {
                printf("请输入以它为始点的边(顶点用它的值表示)(#结束)\n");
                scanf("%d",&ver2_value);
                InsertArc(graph,ver_value,ver2_value);
            }
            while (getchar() != '#')
            {
                printf("请输入以它为终点的边(顶点用它的值表示)(#结束)\n");
                scanf("%d",&ver2_value);
                InsertArc(graph,ver2_value,ver_value);//权值这里输入
            }
        }
        else
        {
            while (getchar() != '#')
            {
                printf("请输入另一个顶点(顶点用它的值表示)(#结束)\n");
                scanf("%d",&ver2_value);
                InsertArc(graph,ver_value,ver2_value);
                graph -> VexNum ++;
            }
        }
        return(9);
    }
}

int DeleteArc(MGraph *graph,int ver1_value , int ver2_value)
/*
    先写减边的函数，后面要用
    成功8 失败-8
*/
{
    if(!graph)  return (-8);
    int ver1,ver2,state1,state2;
    //定位ver1
    for(ver1 = 1; ver1 <=  MAX_VERTEX_NUM ; ver1++)
    {
        if(graph -> Vertexes[ver1] == ver1_value)
        {
            state1 = 1;
            break;
        }    
    }
    //定位ver2
    for (ver2 = 1; ver2 <=  MAX_VERTEX_NUM ; ver2++)
    {
        if(graph -> Vertexes[ver2] == ver2_value)
        {
            state2 = 1;
            break;
        }    
    }
    if( !state1 || !state2) return (-7);
    switch (graph->kind)
    {
        //下面没有给边信息，如果需要将前面create中的按图类型复制即可
        case(DG)://有向图
        {
            if(graph ->arcs[ver1][0].adj)//看是否有边
            {
                graph ->arcs[ver1][ver2].adj = 0;
                graph ->arcs[0][0].adj --;
                graph ->arcs[ver1][0].adj -= 1;
                break;
            }
            else
            {            
                break;        
            }
   
        }
        case(DN)://有向网
        {
            if(graph ->arcs[ver1][0].adj)
            {
                graph ->arcs[ver1][ver2].adj = INFINITY;
                graph ->arcs[0][0].adj --;
                graph ->arcs[ver1][0].adj -= 1;
                break;
            }
            else
            {            
                break;        
            }

        }
        case(UDG):
        {
            if(graph ->arcs[ver1][0].adj)
            {
                graph ->arcs[ver1][ver2].adj = graph ->arcs[ver2][ver1].adj = 0;
                graph ->arcs[0][0].adj --;
                graph ->arcs[ver1][0].adj -= 1;
                graph ->arcs[ver2][0].adj -= 1;
                break;           
            }
            else
            {            
                break;        
            }
        }
        case(UDN):
        {
            if(graph ->arcs[ver1][0].adj)
            {
                graph ->arcs[ver1][ver2].adj = graph ->arcs[ver2][ver1].adj = INFINITY;
                graph ->arcs[0][0].adj --;
                graph ->arcs[ver1][0].adj -= 1;
                graph ->arcs[ver2][0].adj -= 1;
                break;           
            }
            else
            {            
                break;        
            }
        }
    }
    graph -> ArcNum --;
    return (9);
}


int DeleteVex(MGraph *graph,int ver_value)
/*
    删除顶点
    没有顶点则是返回-10
    有是返回10
*/
{
    //开始找是否有空位
    if(!graph)    return (-10);
    //定位
    int ver1,state1;
    //定位ver1
    for(ver1 = 1; ver1 <=  MAX_VERTEX_NUM ; ver1++)
    {
        if(graph -> Vertexes[ver1] == ver_value)
        {
            graph -> Vertexes[ver1] = 0;
            state1 = 1;
            break;
        }    
    }
    if(state1)
    {
        //下面开始删边
        int state = 1;
        int ver2;
        if(graph-> kind == DN ||graph -> kind == DG)
        {
            for ( ver2 = 1; ver2 < MAX_VERTEX_NUM; ver2 ++)
            {
                if(graph ->arcs[ver1][ver2].adj && graph ->arcs[ver1][ver2].adj  != 999)//j为始点的
                {
                    DeleteArc(graph,ver_value,graph -> Vertexes[ver2]);
                }
                if(graph ->arcs[ver1][ver2].adj && graph ->arcs[ver1][ver2].adj  != 999)//j为终点的
                {
                    DeleteArc(graph,graph -> Vertexes[ver2],ver_value);
                }
            }
        }
        else
        {
            for ( ver2 = 1; ver2< MAX_VERTEX_NUM; ver2++)
            {
                if(graph ->arcs[ver1 ][ver2].adj)
                {
                    DeleteArc(graph,ver_value,graph -> Vertexes[ver1]);
                }
            }
        }
        graph ->VexNum --;
    }
    else
    {
        return(-10);
    }
}

int visit(MGraph graph,int i  )
{
    printf("这个顶点的值是:%d\n",graph.Vertexes[i]);
    return (1);
}

int DFS(MGraph graph,int *contrleArray,int i,int (*visit)(MGraph graph ,int i  ))
{
    contrleArray[i] = 1;
    visit( graph ,i);
    VertexType w;
    for(w = FirstAdjVex(graph,graph.Vertexes[i] ) ; w >= 0;w = NextAdjVex(graph,graph.Vertexes[i],graph.Vertexes[w]))
    {
        if(!contrleArray[w] && graph . Vertexes [w] != 0) DFS(graph,contrleArray,w,visit);
    }
    return (1);
}

int DFSTraverse(MGraph graph,int (*visit)(MGraph graph ,int i  ))
//这个是外函数，负责做是否访问的数组
{
    int ContrleArray[MAX_VERTEX_NUM + 1]={0};
    int value;
    printf("请输入点的值\n");
    scanf("%d",&value);
    value = LocateVex(graph,value);
    DFS(graph,ContrleArray,value,visit);
    return (11);
}


typedef struct
{
    int position[MAX_VERTEX_NUM];
    int front;
    int rear;
}SqQueue;

int Empty(SqQueue queue)
{
    if(queue .front == queue .rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}
int EnQueue(SqQueue * queue,int i)
{
    queue -> position[queue -> rear ] = i;
    queue -> rear += 1;
    queue -> rear %= MAX_VERTEX_NUM;
    return 1;
}

int DeQueue(SqQueue * queue,int *i)
{
    *i = queue -> position[queue -> front ];
    queue -> position[queue -> front ] = 0;
    queue -> front += 1;
    queue -> front %= MAX_VERTEX_NUM;
}

int BFSTraverse(MGraph graph,int (*visit)(MGraph graph ,int i  ))
//这个是外函数，负责做是否访问的数组
{
    int ContrleArray[MAX_VERTEX_NUM + 1]={0};
    SqQueue queue;
    queue.front = queue . rear = 0;
    int v,value;//顶点在顶点数组的位置
    printf("请输入开始点的值\n");
    scanf("%d",&value);
    v = LocateVex(graph,value);//先以用户为主
    ContrleArray[v] = 1;
    visit( graph ,v);
    EnQueue(&queue,v);
    int u,w;
    while(!Empty(queue))
    {
        DeQueue(&queue ,&u);
        for(w = FirstAdjVex(graph ,graph.Vertexes[u]);w >= 0; w = NextAdjVex(graph,graph.Vertexes[v],graph.Vertexes[w]))
        {
            if(!ContrleArray[w])
            {
                ContrleArray[w] = 1;
                visit( graph ,w);
                EnQueue(&queue , w);
            }
        }    
    }   
    for(v =1 ;v <MAX_VERTEX_NUM + 1; v++)
    {   
        if(!ContrleArray[v] && graph . Vertexes [v] != 0)
        {
            ContrleArray[v] = 1;
            visit( graph ,v);
            EnQueue(&queue,v);
            int u,w;
            while(!Empty(queue))
            {
                DeQueue(&queue ,&u);
                for(w = FirstAdjVex(graph ,graph.Vertexes[u]);w >= 0; w = NextAdjVex(graph,graph.Vertexes[v],graph.Vertexes[w]))
                {
                    if(!ContrleArray[w])
                    {
                        ContrleArray[w] = 1;
                        visit( graph ,w);
                        EnQueue(&queue , w);
                    }
                }    
            }   
        }
    }
    
    return (11);
}


int main()
{
    MGraph *graph = 0;
    CreateGraph(&graph);
    int value,position;
    printf("DFS\n");
    DFSTraverse(*graph,visit);
    printf("BFS\n");  
    BFSTraverse(*graph,visit); 
    printf("请输入要定位的顶点的值\n");
    scanf("%d",&value);
    position = LocateVex(*graph,value);
    printf("位置是%d\n",position);
    //这里默认返回第一个
    printf("第一个顶点的值是%d\n",GetVex(*graph,1));
    printf("修改第一个顶点的赋值:\n");
    PutVex(graph,1);
    printf("DFS\n");
    DFSTraverse(*graph,visit);
    //FirstAdjVex和NextAdjVex在dfs和bfs验证过
    printf("新加顶点的值:\n");
    scanf("%d",&value);
    InsertVex(graph,value);
    printf("DFS\n");
    DFSTraverse(*graph,visit);
    printf("删除顶点的值:\n");
    scanf("%d",&value);
    DeleteVex(graph,value);//有问题
    printf("DFS\n");
    DFSTraverse(*graph,visit);
    system("pause");
    DestoryGraph(graph);
    return 0;
}

