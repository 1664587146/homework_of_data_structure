/*
    7��������·��ʾ  (����) ��ͼ��
    [��������]
    ����������ʵ�Ͼ�������·ͼ�������Ͼ���Ҫ������·ͼ�Ĵ洢�ṹ��
    [����Ҫ��]
    ��1������������վ�㣬����ת���������ٵĳ˳�·�ߡ�
    ��2������������վ�㣬��������վ�����ٵĳ˳�·�ߡ�
*/
//���ݽṹ���ڽӱ�,���У�ջ
//������ڽӾ���һ����ϡ�����
//���ʹ��cpp��Victor�ܼ���ѹ��������
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUMBER 30//��ͨ�ַ����������ռ�
#define MAX 1000//���ļ�֧�����������ռ�
#define MAXSIZE 100//ջ��
#define TOTAL_STATION 6000
//���վ��
#define TOTAL_LINE 800
//��󹫽���
//#define MAXSIZE 100

typedef struct Line
{
    char bus_number[MAX_NUMBER];       
    //�����victor<string>���Լ�¼����
    //��������
    int index;            
    //��Ӧ��վ���ڽӱ��еı�ţ�λ�ã�
    struct Line *next; //��һվ(�� )
    
}Line;//��������

typedef struct
{
    char name[MAX_NUMBER];       
    //������վ��          
    //char Bus_number[MAX][MAX];
    //���Ծ������վ�ĵĹ�����
    int   Count_Of_Bus;

    int Count_of_Next_Station;
    //����
    Line *Next_Station;                    
    //�ڽӱ�洢����վ
    //����ж�����������ֻ��¼һ����  

    int Count_of_Through_Station;  
    //����
    Line *Through;                  
    //�ڽӱ��˴�֮�����ֱ���վ��
    //����ж�����������ֻ��¼һ����
}Station;
//������վ

typedef struct BusGraph
{
    int stations_number;             
    //�ݹ�����վ�������
    Station station[TOTAL_STATION];//[0]����
    //�����ͷ

    int Line_Number; 
    Line Bus_Line[TOTAL_LINE];//��0������
    //�������ӵ�һ������·��
    //ͷ�����һЩ������Ϣ
    //��������
} BusGraph;

typedef struct 
// ˳������
{
    int data[MAXSIZE]; // ���ڴ�ֵ������
    int front; // ͷָ��
    int rear; // βָ�룬�����в��գ�ָ���βԪ�ص���һ��λ��
} Queue;

//bfs���վ����
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
        printf("�ռ䲻��");
    }
    Create_Graph(graph);
    Line *line;
    int i = 0;
    char name1[MAX_NUMBER],name2[MAX_NUMBER];

    printf("��������Ҫ�Ĳ��ҵ�վ��\n");
    printf("���:\n");
    scanf("%s",name1);
    printf("�յ�:\n");
    scanf("%s",name2);
    printf("����ת��\n");
    Transfer_Less(*graph,name1,name2);
    printf("����վ\n");
    Station_Less(*graph,name1,name2);
    system("pause");
    return (0);
}


int Station_Less(BusGraph graph,char* name1,char* name2)
{
    if(!name1 || !name2)
    {
        printf("��������");
        exit (0);
    }
    else if(strcmp(name1,name2) == 0)
    {
        printf("����һ���͵���\n");
    }
    else
    {
        BFS_Station_Less(graph,name1,name2);
    }
    return 0;
}

int Transfer_Less(BusGraph graph,char* name1,char* name2)
//bfsħ��
{
    if(!name1 || !name2)
    {
        printf("��������");
        exit (0);
    }
    else if(strcmp(name1,name2) == 0)
    {
        printf("����һ���͵���\n");
    }
    else
    {
        BFS_Tansfor_Less(graph,name1,name2);
    }
    return 0;
}

int show(BusGraph graph,SqStack *stack)
//��ӡ·��
{
    SElemType e;//��ջ������
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
//mod�����ĸ���
//mod== 1��ֱ�� mod == 2����
//������⺯�����������Ƿ���ʵ�����
{
    int ContrleArray[TOTAL_STATION]={0};
    //��α���Ҫ��
    Queue queue;
    char finish[20];
    //��Ϊ���ֶ�ģ��ݹ�����finish���
    strcpy(finish,finish1);
    SqStack stack;
    //��������˳�·����
    InitStack(&stack);
    queue.front = queue . rear = 0;
    int start_index,value;//�����ڶ��������λ��
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
    int state;//�Ƿ�һ���ҵ���flag
    //��Ϊֻ��һ����ͨ��֧
    while(!QueueEmpty(queue))
    {
        state = 1;
        DeQueue(&queue ,&vertex);
        for(edge1 = graph.station[vertex].Through ; edge1 &&state ; edge1 = edge1 -> next)
        {
            if(!ContrleArray[edge1 -> index])
            {
                ContrleArray[edge1 -> index] = 1;
                //���������ͷ���
                if(strcmp(finish,graph.station[ edge1 ->index ].name) == 0)
                {
                    SElemType elem;
                    elem .after = edge1 -> index;
                    elem .before = vertex ;
                    Push(&stack,elem);
                    //���濪ʼ�ֶ��ݹ�
                    //���յ�Ϊvertex ��������һ���ͽ���
                    strcpy(finish,graph.station[vertex].name);
                    
                    //����һ������
                    if(strcmp(finish,start) == 0)
                    {
                        state = 0;
                        break;
                    }
                    //,����ʼ�ֶ��ݹ飬��������
                    for (int  i = 0; i < TOTAL_STATION; i++)
                    {
                        ContrleArray[i] = 0;
                    }
                    ClearQueue(&queue);
                    EnQueue(&queue,start_index);
                    break;
                    //Ȼ���ͷ��ʼ
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
    //���������һ����ͨ��֧���ҵ�
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
                        //����Ѿ��ҵ���
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
//mod�����ĸ���
//mod== 1��ֱ�� mod == 2����
//������⺯�����������Ƿ���ʵ�����
{
    int ContrleArray[TOTAL_STATION]={0};
    //��α���Ҫ��
    Queue queue;
    char finish[20];
    //��Ϊ���ֶ�ģ��ݹ�����finish���
    strcpy(finish,finish1);
    SqStack stack;
    //��������˳�·����
    InitStack(&stack);
    queue.front = queue . rear = 0;
    int start_index,value;//�����ڶ��������λ��
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
    int state;//�Ƿ�һ���ҵ���flag
    //��Ϊֻ��һ����ͨ��֧
    while(!QueueEmpty(queue))
    {
        state = 1;
        DeQueue(&queue ,&vertex);
        for(edge1 = graph.station[vertex].Next_Station ; edge1 && state ; edge1 = edge1 -> next)
        {
            if(!ContrleArray[edge1 -> index])
            {
                ContrleArray[edge1 -> index] = 1;
                //���������ͷ���
                if(strcmp(finish,graph.station[ edge1 ->index ].name) == 0)
                {
                    SElemType elem;
                    elem .after = edge1 -> index;
                    elem .before = vertex ;
                    Push(&stack,elem);
                    //���濪ʼ�ֶ��ݹ�
                    //���յ�Ϊvertex ��������һ���ͽ���
                    strcpy(finish,graph.station[vertex].name);
                    //����һ������
                    if(strcmp(finish,start) == 0)
                    {
                        state = 0;
                        break;
                    }
                    //,����ʼ�ֶ��ݹ飬��������
                    for (int  i = 0; i < TOTAL_STATION; i++)
                    {
                        ContrleArray[i] = 0;
                    }
                    ClearQueue(&queue);
                    EnQueue(&queue,start_index);
                    break;
                    //Ȼ���ͷ��ʼ
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
    //���������һ����ͨ��֧���ҵ�
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
                        //����Ѿ��ҵ���
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
                    //���������ͷ���
                    if(strcmp(finish,graph.station[ edge1 ->index ].name) == 0)
                    {
                        SElemType elem;
                        elem .after = edge1 -> index;
                        elem .before = vertex ;
                        Push(&stack,elem);
                        //���濪ʼ�ֶ��ݹ�
                        //���յ�Ϊvertex ��������һ���ͽ���
                        strcpy(finish,graph.station[vertex].name);
                        printf("%s\n",graph.station[vertex].name);
                        //����һ������
                        if(strcmp(finish,start) == 0)
                        {
                            printf("������ת��һ��\n");
                            state = 0;
                            break;
                        }
                        //,����ʼ�ֶ��ݹ飬��������
                        for (int  i = 0; i < TOTAL_STATION; i++)
                        {
                            ContrleArray[i] = 0;
                        }
                        ClearQueue(&queue);
                        EnQueue(&queue,start_index);
                        break;
                        //Ȼ���ͷ��ʼ
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
//��ʼ��һ���ն��� 
{
    Q->front = Q->rear=  0; // ��ͷ�Ͷ�βָ�붼ָ��0
    return 1;
}

int QueueEmpty(Queue Q) 
//�ж϶����Ƿ�Ϊ��
{
    if (Q.front == Q.rear) 
    { // ��ͷ���ڶ�βָ�룬����Ϊ��
        return 1;
    } 
    else 
    {
        return 0;
    }
}


int EnQueue(Queue *Q, int e)
//��Ԫ��e�������Q�Ķ�β 
{
    // ��������������ʧ��
    if ((Q->rear + 1) % MAXSIZE == Q->front) 
    {
        return 0;
    }

    // ��Ԫ��e�����β
    Q->data[Q->rear] = e;

    // ���ö�βָ��ָ����һ��λ�ã����������ת��ͷ��
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return 1;
}

int ClearQueue(Queue *Q)
//��ն���Q 
{
    // ��������������ʧ��
    Q -> rear = Q -> front ;
}


int DeQueue(Queue *Q, int *e) 
// ��ͷԪ�س��ӣ���e������ֵ
{
    // ��ͷָ����ڶ�βָ�룬��ʱ����Ϊ�գ�����ʧ��
    if (Q->front == Q->rear) 
    {
        return 0;
    }

    // ����ͷԪ�ص�ֵ����Ԫ��e
    *e = Q->data[Q->front];

    // ���ö�ͷָ��ָ����һ��λ�ã����������ת��ͷ��
    Q->front = (Q->front + 1) % MAXSIZE;
    return 1;
}


int Create_Graph(BusGraph *graph)
//��Ϊgraph�����intҪ��������ָ��
//int Create_Graph()
//��ͼ
{
    graph -> stations_number = graph -> Line_Number  = 0;
    char information[MAX];              
    //��¼ĳһ�еĹ�������Ϣ
    Line *station1, *station2;                    
    //����ռ�
    char bus_number[MAX_NUMBER];    
    //��¼��Ӧ�Ĺ�������
    int flag = 0; 
    //��¼�Ƿ�δ�ǵ�һ�γ��ֵĹ���վ
    FILE *file_r;
    file_r = fopen("�Ͼ�������·.txt", "r");
    if (!file_r)
    {
        printf("������Ϣ�ļ���ʧ��");
        exit(0);
    }
    //��ȡ�ɹ���ʼ�ɻ�
    while (1)
    {   
        fscanf(file_r,"%s",bus_number);
        //�����ǵڼ�·��
        graph -> Line_Number ++;
        fscanf(file_r,"%s",information); 
        Add_Informations(graph,bus_number,information);
        if( feof(file_r))
        {
            break;//�������
        }
    }
    fclose(file_r);
    return (4);
}

int find(BusGraph graph,char* station_name)
/*
    ��ѯstation�Ƿ��Ѿ��ڼ���ͷ���
    return i;//�ɵ� ��ͷ������ά��
    return 0;//�µķ���0��
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
            //�ɵ� ��ͷ������ά��
        }
    }
    return 0;//�µķ���0��
}

int Add_Informations(BusGraph *graph ,char*  Line_Number,char *station_info )
{

    if(!graph || !Line_Number || !station_info)
    {
        printf("add_informations����\n");
        exit (0);
    }
    int flag;
    // ������վ�Ƿ��һ�γ���
    char station_name[MAX_NUMBER];     
    //��ǰվ̨
    char station_name_pre[MAX_NUMBER]; 
    //��ǰ������ǰһ��վ̨
    Line *line1,*line2,*line3,*line4;
    //��������
    
    //�����һ����
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
            station_name[k ++] = '\0';//�����������

            //һ�²���Ҫgraph����ʱΪȫ��ղſ���������
            if (!(station_index = find(*graph , station_name)))
            {

                //�µ�վ��
                //���ȼ��붥�㼯��
                graph -> stations_number ++ ;
                //��վ��++
                strcpy((graph -> station)[graph -> stations_number] . name , station_name);
                //���½������
                (graph -> station)[graph -> stations_number] . Count_Of_Bus ++;
                //ͬ���Ļ��������վ��bus�� ++
                k = (graph -> station)[graph -> stations_number] . Count_Of_Bus;
                //ʡ����һ��̫��
                
                //ͬ���Ļ��������վ��bus�ߵ�����д��
                station_index = graph -> stations_number;
                //��ʱstation_index�������վ��ͷָ�������λ��
                if(!staton_had_deal)
                //����ǿ�ʼ�ĵ�һ�����
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
                //name��������
                line1 ->next = (Line *)calloc(1,sizeof(Line));
                if(!line1)
                {
                    exit(0);
                }
                line1 = line1 -> next;
                strcpy(line1 ->bus_number, Line_Number );
            }
            else
            //�����µ�
            {
                line1 -> index = station_index;
                //��ʱstation_index��������Ѿ������վ�ڱ�ͷ��λ��
                complete(graph,station_index,Line_Number);
                k = 0;    
                //name��������
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
//ά����
//station_index��Ҫά�����ڵ�λ��
//ά�����ʱ��ǰ��������·������һ������
//
{
    Line * line1 ,*line2,*line3;

    int line_index = (graph -> Line_Number);
    //   ����� *Next_Station *Through ����ά��
    for (line3 = (graph -> Bus_Line)[line_index] . next ; line3 ; line3 = line3 -> next)
    {
        if(line3 -> index != station_index)
        //���߲���ͬһ��վ
        {
            int state = 0;
            if (!(graph ->station)[station_index].Through)
            /*
                ������ڽӱ�ĵ�һ�����ڵ�
                ��Ϊ�ǵ�һ��������Կ϶�û�б�������ڵ�
                ����ǰ��Ŀ���ֱ�ﶥ���Ѿ�����
                ע��˫������
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
                //�����ж��Ƿ��Ѿ�����
                {
                    if (line1 ->index == line3 -> index)
                    //�Ѿ��������
                    {
                        state = 1;
                        break;
                    }
                    
                }
                //���û��break,��ʱline1�Ѿ�����β�ˡ�Through�������
                if(state)
                //����Ѿ�������������
                {
                    continue;
                }
                else
                //���û�м���
                {            
                    (graph -> station)[station_index].Count_of_Through_Station ++;
                    //ֱ���վ++
                    //�����µı߼�line
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
                //����station_next
                //���̺�������
                //��line3���� station_next
                // station_indexҲҪ����line3������index
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
                        //����station
                        line2 -> index = station_index;
                        //����line3 -> index
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
                        //�Ѿ��������
                        {
                            state = 1;
                            break;
                        }
                        
                    }
                    //���û��break,��ʱline1�Ѿ����ˡ�Next_Station�������
                    //���û����
                    if(state == 0)
                    {            
                        (graph -> station)[station_index].Count_of_Through_Station ++;
                        //ֱ���վ++
                        //�����µı߼�line
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
}//����ջ �ɹ�һ
//��ջ ��top = base

int StackEmpty(SqStack stack)
{    
    if(&stack == 0) return(0);
    if(stack.base  == stack.top) return 4;
    else
    {
        return -4;    
    }
}//�ж�ջ�� 4�� -4����


int Push(SqStack *stack,SElemType e)
//top������ջ����Ԫ�ص�����
{
    if(&stack == 0) return(0);
    stack ->sq[stack -> top] . after = e.after;
    stack ->sq[stack -> top] . before = e.before;
    stack -> top ++;
}//��ջ �ɹ�6 ʧ��-6

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

}//ɾ��ջͷ �ɹ�7 ʧ��-7
