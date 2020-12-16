/*
    7、公交线路提示  (必做) （图）
    [问题描述]
    上网下载真实南京公交线路图，建立南京主要公交线路图的存储结构。
    [基本要求]
    （1）输入任意两站点，给出转车次数最少的乘车路线。
    （2）输入任意两站点，给出经过站点最少的乘车路线。
*/
//数据结构：邻接表,队列，栈
//如果用邻接矩阵，一定是稀疏矩阵
//如果使用cpp的Victor能极大压缩代码量
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUMBER 30//普通字符串数组最大空间
#define MAX 1000//读文件支付串数组最大空间
#define MAXSIZE 100//栈用
#define TOTAL_STATION 6000
//最大站数
#define TOTAL_LINE 800
//最大公交线
//#define MAXSIZE 100

typedef struct Line
{
    char bus_number[MAX_NUMBER];       
    //如果是victor<string>可以记录多条
    //公交车号
    int index;            
    //对应车站在邻接表中的编号（位置）
    struct Line *next; //下一站(边 )
    
}Line;//弧就是线

typedef struct
{
    char name[MAX_NUMBER];       
    //公交车站名          
    //char Bus_number[MAX][MAX];
    //可以经过这个站的的公交线
    int   Count_Of_Bus;

    int Count_of_Next_Station;
    //数量
    Line *Next_Station;                    
    //邻接表存储相邻站
    //如果有多条公交线则只记录一条线  

    int Count_of_Through_Station;  
    //数量
    Line *Through;                  
    //邻接表存彼此之间可以直达的站点
    //如果有多条公交线则只记录一条线
}Station;
//顶点是站

typedef struct BusGraph
{
    int stations_number;             
    //纵公交车站点的数量
    Station station[TOTAL_STATION];//[0]不用
    //链表表头

    int Line_Number; 
    Line Bus_Line[TOTAL_LINE];//【0】不用
    //链表连接的一条公交路线
    //头结点是一些基础信息
    //读数据用
} BusGraph;

typedef struct 
// 顺序表队列
{
    int data[MAXSIZE]; // 用于存值的数组
    int front; // 头指针
    int rear; // 尾指针，若队列不空，指向队尾元素的下一个位置
} Queue;

//bfs输出站名用
typedef struct
{
    int before;
    int after;
}SElemType;

typedef struct SqStack
{
    SElemType sq[MAXSIZE];
    int top;
    int base;
    int StackSize;
}SqStack;

int Add_Informations(BusGraph *graph,char* Line_Number,char *Station);
int Create_Graph(BusGraph *graph);
int complete(BusGraph *graph,int station_index,char* line_number);
int find(BusGraph graph,char* station_name);
int Transfer_Less(BusGraph graph,char* name1,char* name2);
int Station_Less(BusGraph graph,char* name1,char* name2);
int BFS_Tansfor_Less(BusGraph graph,char* start,char* finish);
int BFS_Station_Less(BusGraph graph,char* start,char* finish1);
int show(BusGraph graph,SqStack *stack);


int InitQueue(Queue *Q);
int QueueEmpty(Queue Q) ;
int EnQueue(Queue *Q, int e);
int DeQueue(Queue *Q, int *e);
int ClearQueue(Queue *Q);

int InitStack(SqStack *stack);
int DestroyStack(SqStack *stack);
int StackEmpty(SqStack stack);
int Push(SqStack *stack,SElemType e);
int Pop(SqStack *stack,SElemType *elem);

int main()
{
    BusGraph *graph;
    graph = (BusGraph*)calloc(1,sizeof(BusGraph));
    if(!graph)
    {
        printf("空间不够");
    }
    Create_Graph(graph);
    Line *line;
    int i = 0;
    char name1[MAX_NUMBER],name2[MAX_NUMBER];

    printf("请输入你要的查找的站点\n");
    printf("起点:\n");
    scanf("%s",name1);
    printf("终点:\n");
    scanf("%s",name2);
    printf("最少转车\n");
    Transfer_Less(*graph,name1,name2);
    printf("最少站\n");
    Station_Less(*graph,name1,name2);
    system("pause");
    return (0);
}


int Station_Less(BusGraph graph,char* name1,char* name2)
{
    if(!name1 || !name2)
    {
        printf("名字有误");
        exit (0);
    }
    else if(strcmp(name1,name2) == 0)
    {
        printf("您走一步就到了\n");
    }
    else
    {
        BFS_Station_Less(graph,name1,name2);
    }
    return 0;
}

int Transfer_Less(BusGraph graph,char* name1,char* name2)
//bfs魔改
{
    if(!name1 || !name2)
    {
        printf("名字有误");
        exit (0);
    }
    else if(strcmp(name1,name2) == 0)
    {
        printf("您走一步就到了\n");
    }
    else
    {
        BFS_Tansfor_Less(graph,name1,name2);
    }
    return 0;
}

int show(BusGraph graph,SqStack *stack)
//打印路径
{
    SElemType e;//读栈的数字
    Pop(stack,&e);
    printf("%s", graph.station[e.before].name);
    while (StackEmpty(*stack) == -4)
    {   
        Pop(stack,&e);
        printf("------ %s",graph.station[e.before].name);
    }
    printf("------ %s\n",graph.station[e.after].name);
    return 0;
}


int BFS_Tansfor_Less(BusGraph graph,char* start,char* finish1)
//mod是找哪个表
//mod== 1：直达 mod == 2相邻
//这个是外函数，负责做是否访问的数组
{
    int ContrleArray[TOTAL_STATION]={0};
    //层次遍历要用
    Queue queue;
    char finish[20];
    //因为是手动模拟递归所以finish会变
    strcpy(finish,finish1);
    SqStack stack;
    //帮助输出乘车路径的
    InitStack(&stack);
    queue.front = queue . rear = 0;
    int start_index,value;//顶点在顶点数组的位置
    for ( start_index = 1 ; start_index < TOTAL_STATION; start_index ++)
    {
        if(strcmp(graph.station[start_index].name,start) == 0)
            break;
    }
    ContrleArray[start_index] = 1;
    EnQueue(&queue,start_index);
    Line *edge1,*edge2;
    int vertex;
    int i = 0;
    int state;//是否一次找到得flag
    //因为只有一个连通分支
    while(!QueueEmpty(queue))
    {
        state = 1;
        DeQueue(&queue ,&vertex);
        for(edge1 = graph.station[vertex].Through ; edge1 &&state ; edge1 = edge1 -> next)
        {
            if(!ContrleArray[edge1 -> index])
            {
                ContrleArray[edge1 -> index] = 1;
                //对起点遍历就发现
                if(strcmp(finish,graph.station[ edge1 ->index ].name) == 0)
                {
                    SElemType elem;
                    elem .after = edge1 -> index;
                    elem .before = vertex ;
                    Push(&stack,elem);
                    //下面开始手动递归
                    //改终点为vertex 如果和起点一样就结束
                    strcpy(finish,graph.station[vertex].name);
                    
                    //二者一样结束
                    if(strcmp(finish,start) == 0)
                    {
                        state = 0;
                        break;
                    }
                    //,否则开始手动递归，数组置零
                    for (int  i = 0; i < TOTAL_STATION; i++)
                    {
                        ContrleArray[i] = 0;
                    }
                    ClearQueue(&queue);
                    EnQueue(&queue,start_index);
                    break;
                    //然后从头开始
                }
                EnQueue(&queue , edge1 -> index);
            }
        }
        if(state == 0)
        {
            break;
        }    
    }   
    /*for(vertex =1 ;vertex <=TOTAL_STATION && state; vertex++)
    //如果不是在一个连通分支就找到
    {   
        if(!ContrleArray[vertex])
        {
            ContrleArray[vertex] = 1;
            printf("%s,%d",graph.station[vertex].name,i++);
            EnQueue(&queue,vertex);
            int u,w;
            while(!QueueEmpty(queue))
            {
                DeQueue(&queue ,&u);
                for(edge1 = graph.station[u].Through ; edge1 ; edge1 = edge1 -> next)
                {
                    if(!ContrleArray[edge1 -> index])
                    {
                        ContrleArray[edge1 -> index] = 1;
                        /*if(strcmp(finish,graph.station[edge1 ->index ].Through) == 0)
                        //如果已经找到了
                        {
                            SElemType elem;
                            elem .after = edge1 -> index;
                            elem .before = start_index;
                            Push(stack,elem);
                            state = 0; 
                        }
                        EnQueue(&queue , edge1 -> index);
                    }
                }    
            }   
        }
    }*/
    show(graph,&stack);
    return (11);
}

int BFS_Station_Less(BusGraph graph,char* start,char* finish1)
//mod是找哪个表
//mod== 1：直达 mod == 2相邻
//这个是外函数，负责做是否访问的数组
{
    int ContrleArray[TOTAL_STATION]={0};
    //层次遍历要用
    Queue queue;
    char finish[20];
    //因为是手动模拟递归所以finish会变
    strcpy(finish,finish1);
    SqStack stack;
    //帮助输出乘车路径的
    InitStack(&stack);
    queue.front = queue . rear = 0;
    int start_index,value;//顶点在顶点数组的位置
    for ( start_index = 1 ; start_index < TOTAL_STATION; start_index ++)
    {
        if(strcmp(graph.station[start_index].name,start) == 0)
            break;
    }
    ContrleArray[start_index] = 1;
    EnQueue(&queue,start_index);
    Line *edge1,*edge2;
    int vertex;
    int i = 0;
    int state;//是否一次找到得flag
    //因为只有一个连通分支
    while(!QueueEmpty(queue))
    {
        state = 1;
        DeQueue(&queue ,&vertex);
        for(edge1 = graph.station[vertex].Next_Station ; edge1 && state ; edge1 = edge1 -> next)
        {
            if(!ContrleArray[edge1 -> index])
            {
                ContrleArray[edge1 -> index] = 1;
                //对起点遍历就发现
                if(strcmp(finish,graph.station[ edge1 ->index ].name) == 0)
                {
                    SElemType elem;
                    elem .after = edge1 -> index;
                    elem .before = vertex ;
                    Push(&stack,elem);
                    //下面开始手动递归
                    //改终点为vertex 如果和起点一样就结束
                    strcpy(finish,graph.station[vertex].name);
                    //二者一样结束
                    if(strcmp(finish,start) == 0)
                    {
                        state = 0;
                        break;
                    }
                    //,否则开始手动递归，数组置零
                    for (int  i = 0; i < TOTAL_STATION; i++)
                    {
                        ContrleArray[i] = 0;
                    }
                    ClearQueue(&queue);
                    EnQueue(&queue,start_index);
                    break;
                    //然后从头开始
                }
                EnQueue(&queue , edge1 -> index);
            }
        }
        if(state == 0)
        {
            break;
        }    
    }   
    /*for(vertex =1 ;vertex <=TOTAL_STATION && state; vertex++)
    //如果不是在一个连通分支就找到
    {   
        if(!ContrleArray[vertex])
        {
            ContrleArray[vertex] = 1;
            printf("%s,%d",graph.station[vertex].name,i++);
            EnQueue(&queue,vertex);
            int u,w;
            while(!QueueEmpty(queue))
            {
                DeQueue(&queue ,&u);
                for(edge1 = graph.station[u].Through ; edge1 ; edge1 = edge1 -> next)
                {
                    if(!ContrleArray[edge1 -> index])
                    {
                        ContrleArray[edge1 -> index] = 1;
                        /*if(strcmp(finish,graph.station[edge1 ->index ].Through) == 0)
                        //如果已经找到了
                        {
                            SElemType elem;
                            elem .after = edge1 -> index;
                            elem .before = start_index;
                            Push(stack,elem);
                            state = 0; 
                        }
                        EnQueue(&queue , edge1 -> index);
                    }
                }    
            }   
        }
    }*/
    if (state == 1)
    {
        ClearQueue(&queue);
        InitStack(&stack);
        EnQueue(&queue,start_index);
        while(!QueueEmpty(queue))
        {
            state = 1;
            DeQueue(&queue ,&vertex);
            for(edge1 = graph.station[vertex].Through ; edge1 && state ; edge1 = edge1 -> next)
            {
                if(!ContrleArray[edge1 -> index])
                {
                    ContrleArray[edge1 -> index] = 1;
                    //对起点遍历就发现
                    if(strcmp(finish,graph.station[ edge1 ->index ].name) == 0)
                    {
                        SElemType elem;
                        elem .after = edge1 -> index;
                        elem .before = vertex ;
                        Push(&stack,elem);
                        //下面开始手动递归
                        //改终点为vertex 如果和起点一样就结束
                        strcpy(finish,graph.station[vertex].name);
                        printf("%s\n",graph.station[vertex].name);
                        //二者一样结束
                        if(strcmp(finish,start) == 0)
                        {
                            printf("和最少转车一样\n");
                            state = 0;
                            break;
                        }
                        //,否则开始手动递归，数组置零
                        for (int  i = 0; i < TOTAL_STATION; i++)
                        {
                            ContrleArray[i] = 0;
                        }
                        ClearQueue(&queue);
                        EnQueue(&queue,start_index);
                        break;
                        //然后从头开始
                    }
                    EnQueue(&queue , edge1 -> index);
                }
            }
            if(state == 0)
            {
                break;
            }    
        }   
    }
    show(graph,&stack);
    return (11);
}



int InitQueue(Queue *Q)
//初始化一个空队列 
{
    Q->front = Q->rear=  0; // 队头和队尾指针都指向0
    return 1;
}

int QueueEmpty(Queue Q) 
//判断队列是否为空
{
    if (Q.front == Q.rear) 
    { // 队头等于队尾指针，队列为空
        return 1;
    } 
    else 
    {
        return 0;
    }
}


int EnQueue(Queue *Q, int e)
//将元素e插入队列Q的队尾 
{
    // 队列已满，插入失败
    if ((Q->rear + 1) % MAXSIZE == Q->front) 
    {
        return 0;
    }

    // 将元素e插入队尾
    Q->data[Q->rear] = e;

    // 设置队尾指针指向下一个位置，若到最后则转向头部
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return 1;
}

int ClearQueue(Queue *Q)
//清空队列Q 
{
    // 队列已满，插入失败
    Q -> rear = Q -> front ;
}


int DeQueue(Queue *Q, int *e) 
// 队头元素出队，用e返回其值
{
    // 对头指针等于对尾指针，此时队列为空，出队失败
    if (Q->front == Q->rear) 
    {
        return 0;
    }

    // 将队头元素的值赋给元素e
    *e = Q->data[Q->front];

    // 设置队头指针指向下一个位置，若到最后则转向头部
    Q->front = (Q->front + 1) % MAXSIZE;
    return 1;
}


int Create_Graph(BusGraph *graph)
//因为graph里面的int要改所以用指针
//int Create_Graph()
//建图
{
    graph -> stations_number = graph -> Line_Number  = 0;
    char information[MAX];              
    //记录某一行的公交车信息
    Line *station1, *station2;                    
    //申请空间
    char bus_number[MAX_NUMBER];    
    //记录对应的公交车号
    int flag = 0; 
    //记录是否未是第一次出现的公交站
    FILE *file_r;
    file_r = fopen("南京公交线路.txt", "r");
    if (!file_r)
    {
        printf("公交信息文件打开失败");
        exit(0);
    }
    //读取成功开始干活
    while (1)
    {   
        fscanf(file_r,"%s",bus_number);
        //读入是第几路车
        graph -> Line_Number ++;
        fscanf(file_r,"%s",information); 
        Add_Informations(graph,bus_number,information);
        if( feof(file_r))
        {
            break;//读完结束
        }
    }
    fclose(file_r);
    return (4);
}

int find(BusGraph graph,char* station_name)
/*
    查询station是否已经在加入头结点
    return i;//旧的 对头结点进行维护
    return 0;//新的返回0；
*/
{
    if (!station_name)
    {
        exit(0);
    }

    for (int  i = 1; i <= graph . stations_number; i++)
    {
        if(strcmp(graph . station[i] .name , station_name) == 0)
        {
            return (i);
            //旧的 对头结点进行维护
        }
    }
    return 0;//新的返回0；
}

int Add_Informations(BusGraph *graph ,char*  Line_Number,char *station_info )
{

    if(!graph || !Line_Number || !station_info)
    {
        printf("add_informations出错\n");
        exit (0);
    }
    int flag;
    // 公交车站是否第一次出现
    char station_name[MAX_NUMBER];     
    //当前站台
    char station_name_pre[MAX_NUMBER]; 
    //当前公交的前一个站台
    Line *line1,*line2,*line3,*line4;
    //辅助变量
    
    //处理第一个边
    line1 = (Line *)calloc(1,sizeof(Line));
    if(!line1)
    {
        exit(0);
    }
    strcpy((graph -> Bus_Line )[graph -> Line_Number] . bus_number,Line_Number );
    (graph -> Bus_Line )[graph -> Line_Number] . next = line1;
    strcpy(line1 ->bus_number, Line_Number );
    
    int k = 0 , j , l,staton_had_deal = 0,station_index;
    for (int i = 0; i < strlen(station_info); i++)
    {

        if(station_info[i] != ',')
        {
            station_name[k ++] = station_info[i];
        }
        else
        {
            station_name[k ++] = '\0';//完成名字数组

            //一下操作要graph申请时为全清空才可正常运行
            if (!(station_index = find(*graph , station_name)))
            {

                //新的站点
                //首先加入顶点集合
                graph -> stations_number ++ ;
                //总站数++
                strcpy((graph -> station)[graph -> stations_number] . name , station_name);
                //给新结点命名
                (graph -> station)[graph -> stations_number] . Count_Of_Bus ++;
                //同样的会进过的新站的bus线 ++
                k = (graph -> station)[graph -> stations_number] . Count_Of_Bus;
                //省的下一个太长
                
                //同样的会进过的新站的bus线的名字写入
                station_index = graph -> stations_number;
                //这时station_index是这个新站在头指针数组的位置
                if(!staton_had_deal)
                //如果是开始的第一个结点
                {
                    line1 -> index = graph -> stations_number;
                    line2 = line1 ;
                    staton_had_deal ++ ;
                }
                else
                {
                    line1 -> index = station_index;
                    complete(graph,station_index,Line_Number);
                }
                k = 0;    
                //name数组置零
                line1 ->next = (Line *)calloc(1,sizeof(Line));
                if(!line1)
                {
                    exit(0);
                }
                line1 = line1 -> next;
                strcpy(line1 ->bus_number, Line_Number );
            }
            else
            //不是新的
            {
                line1 -> index = station_index;
                //这时station_index就是这个已经加入的站在表头的位置
                complete(graph,station_index,Line_Number);
                k = 0;    
                //name数组置零
                line1 ->next = (Line *)calloc(1,sizeof(Line));
                if(!line1)
                {
                    exit(0);
                }
                line1 = line1 -> next;
                strcpy(line1 ->bus_number, Line_Number );
                //
            }              
        }    
    }
}

int complete(BusGraph *graph,int station_index,char* line_number)
//维护表
//station_index是要维护点在的位置
//维护表的时候当前公交车线路的总数一定不变
//
{
    Line * line1 ,*line2,*line3;

    int line_index = (graph -> Line_Number);
    //   下面对 *Next_Station *Through 进行维护
    for (line3 = (graph -> Bus_Line)[line_index] . next ; line3 ; line3 = line3 -> next)
    {
        if(line3 -> index != station_index)
        //二者不是同一个站
        {
            int state = 0;
            if (!(graph ->station)[station_index].Through)
            /*
                如果是邻接表的第一个链节点
                因为是第一个结点所以肯定没有表有这个节点
                而且前面的可能直达顶点已经建立
                注意双向连接
            */
            {
                line1 = (Line *)calloc(1,sizeof(Line));
                line2 = (Line *)calloc(1,sizeof(Line));
                if(line1 && line2)
                {
                    strcpy(line1 ->bus_number,line_number );
                    strcpy(line2 ->bus_number,line_number );
                    line1 -> index = line3 ->index;
                    line2 -> index = station_index;

                }
                else
                {
                    exit(0);
                }
                if ( !(graph ->station)[ (line3 -> index) ].Through)
                {
                    (graph ->station)[ (line3 -> index) ].Through = line2;
                }
                else
                {
                    line2 -> next = (graph ->station)[ (line3 -> index) ].Through -> next;
                    (graph ->station)[ (line3 -> index) ].Through -> next  = line2;                        
                }            
                (graph ->station)[station_index].Through = line1;
                (graph ->station)[station_index].Count_of_Through_Station ++ ;      
                (graph ->station)[ (line3 -> index) ].Count_of_Through_Station ++;
            }
            else
            {
                for (line1 = (graph ->station)[station_index].Through; line1 -> next;line1 = line1 -> next)
                //下面判读是否已经加入
                {
                    if (line1 ->index == line3 -> index)
                    //已经加入过了
                    {
                        state = 1;
                        break;
                    }
                    
                }
                //如果没有break,这时line1已经到链尾了。Through的最后面
                if(state)
                //如果已经加入过，则继续
                {
                    continue;
                }
                else
                //如果没有继续
                {            
                    (graph -> station)[station_index].Count_of_Through_Station ++;
                    //直达的站++
                    //建立新的边即line
                    line1 -> next = (Line *)calloc(1,sizeof(Line));
                    line2 = (Line *)calloc(1,sizeof(Line));
                    if(line1 -> next )
                    {
                        strcpy(line1 -> next ->bus_number,line_number );
                        strcpy(line2 ->bus_number,line_number );
                        if ( !(graph ->station)[ (line3 -> index) ].Through)
                        {
                            (graph ->station)[ (line3 -> index) ].Through = line2;
                        }
                        else
                        {
                            line2 -> next = (graph ->station)[ (line3 -> index) ].Through -> next;
                            (graph ->station)[ (line3 -> index) ].Through -> next  = line2 ;                        
                        }           
                        (line1 -> next )-> index = line3 ->index;
                        line2 -> index = station_index;
                        (graph ->station)[station_index].Count_of_Through_Station ++ ;      
                        (graph ->station)[ (line3 -> index) ].Count_of_Through_Station ++;
                    }
                    else
                    {
                        exit(0);
                    }
                }
            }
            if ( line3 -> next -> index == station_index)
            /*
                //加入station_next
                //过程和上面差不多
                //将line3加入 station_next
                // station_index也要加入line3——》index
            */
            {
                if (!(graph ->station)[station_index].Next_Station)
                {
                    line1 = (Line *)calloc(1,sizeof(Line));
                    line2 = (Line *)calloc(1,sizeof(Line));
                    if(line1 && line2)
                    {
                        strcpy(line1 -> bus_number,line_number );
                        strcpy(line2 -> bus_number,line_number );
                        line1 -> index = line3 ->index;
                        //加入station
                        line2 -> index = station_index;
                        //加入line3 -> index
                    }
                    else
                    {
                        exit(0);
                    }    
                    if ( !(graph ->station)[ line1 -> index ].Next_Station)
                    {
                        (graph ->station)[ line1 -> index ].Next_Station = line2;
                    }
                    else
                    {
                        line2 -> next = (graph ->station)[ line1 -> index].Next_Station -> next;
                        (graph ->station)[ line1 -> index ].Next_Station -> next  = line2;                        
                    }           
                    (graph ->station)[station_index].Next_Station = line1;
                    (graph ->station)[station_index].Count_of_Next_Station++;
                    (graph ->station)[line1 -> index].Count_of_Next_Station++;
                    continue;
                }
                else
                {              
                    state = 0;
                    for (line1 = (graph ->station)[station_index].Next_Station; line1 -> next;line1 = line1 -> next)
                    {
                        if (line1 ->index == line3 -> index)
                        //已经加入过了
                        {
                            state = 1;
                            break;
                        }
                        
                    }
                    //如果没有break,这时line1已经到了。Next_Station的最后面
                    //如果没发现
                    if(state == 0)
                    {            
                        (graph -> station)[station_index].Count_of_Through_Station ++;
                        //直达的站++
                        //建立新的边即line
                        line1 -> next = (Line *)calloc(1,sizeof(Line));
                        line2 = (Line *)calloc(1,sizeof(Line));
                        if(line1 -> next )
                        {
                            strcpy(line1 -> next ->bus_number,line_number );
                            strcpy(line2 ->bus_number,line_number );
                            line1 -> next ->index = line3 ->index;
                            line2 -> index = station_index;
                            (graph ->station)[station_index].Next_Station = line1;
                            if ( !(graph ->station)[ line1 -> index ].Next_Station)
                            {
                                (graph ->station)[ line1 -> index ].Next_Station = line2;
                            }
                            else
                            {
                                line2 -> next = (graph ->station)[ line1 -> index].Next_Station -> next;
                                (graph ->station)[ line1 -> index ].Next_Station -> next  = line2 -> next;                        
                            } 
                            (graph ->station)[station_index].Count_of_Next_Station++;
                            (graph ->station)[line1 -> index].Count_of_Next_Station++;
                        }
                        else
                        {
                            exit(0);
                        }    
                    }
                }
            }
        }
    }
    return (3);
}



int InitStack(SqStack *stack)
{
    stack -> base = stack -> top = 0;
}//创建栈 成功一
//空栈 ：top = base

int StackEmpty(SqStack stack)
{    
    if(&stack == 0) return(0);
    if(stack.base  == stack.top) return 4;
    else
    {
        return -4;    
    }
}//判断栈空 4空 -4不空


int Push(SqStack *stack,SElemType e)
//top用于在栈顶上元素的上面
{
    if(&stack == 0) return(0);
    stack ->sq[stack -> top] . after = e.after;
    stack ->sq[stack -> top] . before = e.before;
    stack -> top ++;
}//入栈 成功6 失败-6

int Pop(SqStack *stack,SElemType *elem)
{
    if(&stack == 0) return(0);
    else
    {   
        stack -> top --; 
        elem ->after = stack ->sq[stack -> top] . after;
        elem ->before = stack ->sq[stack -> top] . before;
        return (7); 
    }

}//删除栈头 成功7 失败-7
