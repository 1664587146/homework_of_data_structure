#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INFINITY INT_MAX//���ֵ��������ͼ�б�ʾû�б�
#define MAX_VERTEX_NUM 20
typedef enum{DG = 1,DN,UDG,UDN} GraphKind;
//����ͼ��������������ͼ��������
typedef int VRType;
//�������� ��Ȩ��1/0��ʾ�Ƿ�����
//������Ȩֵ����������INT_MAX,Ĭ����ȨֵΪ100%,ʡ��%
typedef char InfoType ;

typedef struct ArcCell
{
    VRType adj;
    InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM + 1][MAX_VERTEX_NUM + 1];
//AdjMatrix[0][X] AdjMatrix[X][0]���� �����Է���������Ϣ
//AdjMatrix[0][0]��ʾ�߸��� 
//AdjMatrix[x][0]��ʾ�����ڽӽڵ�ĸ���(x >= 1) 
typedef int VertexType;

typedef struct 
{
    //����
    VertexType Vertexes[MAX_VERTEX_NUM + 1];//�����ֱ�� [0]����
    //�ڽӾ���
    AdjMatrix arcs;
    //��ߵ�����
    int VexNum,ArcNum;
    GraphKind kind;
}MGraph;

int CreateDG(MGraph *graph)
//��������ͼ
{
    if(!graph) return 0;
    printf("������������,�㲻����20\n");
    scanf("%d",&(graph -> VexNum));
    printf("����������������Ϣ��\n");
    int i,j,k,ver1,ver2;
    for( i = 1 ; i <= graph -> VexNum ; i++)
    {
        scanf("%d",&j);
        ( graph -> Vertexes )[i] = j;
    }
    printf("�����������Ϣ����#��β\n");
    for( i = 1 ; getchar() != '#' ; i++)
    {
        printf("������ʼ����յ�:\n");
        scanf("%d %d",&ver1,&ver2);
        //��Ϊ��������Ȩͼ
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
        //��Ϊ�����������û��ʲô�ã���������ע�����Ҫ�ü����
        /*
            char *info;
            printf("������ߵ���Ϣ");
            scanf("%s",info);
            strcpy( graph ->arcs[ver1][ver2].info,info);
        */
    }
    graph ->ArcNum = graph -> arcs[0][0] . adj;
    return (1);
}

int CreateDN(MGraph *graph)
//����������
{
    if(!graph) return 0;
    int i,j,ver1,ver2;
    //�������ڵ�Ϊmax����int���Խ������ʼ��
    for ( i = 1; i <= MAX_VERTEX_NUM; i++)
    {
        for ( j = 1; j <= MAX_VERTEX_NUM ; j++)
        {
            graph -> arcs[i][j].adj = INFINITY;
        }   
    }
    printf("�����붥�������,���㲻����20\n");
    scanf("%d00",&(graph -> VexNum));
    printf("����������������Ϣ��\n");
    for( i = 1 ; i <= graph -> VexNum ; i++)
    {
        scanf("%d",&j);
        ( graph -> Vertexes )[i] = j;
    }
    printf("�����������Ϣ,��#��β\n");
    for( i = 1 ; getchar() != '#' ; i++)
    {
        int weight;
        printf("������ʼ�㡢�յ��Ȩ:\n");
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
        //��Ϊ��������Ȩͼ
        graph ->arcs[ver1][ver2].adj = weight;
        graph ->arcs[0][0].adj += 1;
        graph ->arcs[ver1][0].adj += 1;
        //��Ϊ�����������û��ʲô�ã���������ע�����Ҫ�ü����
        /*
            char *info;
            printf("������ߵ���Ϣ");
            scanf("%s",info);
            strcpy( graph ->arcs[ver1][ver2].info,info);
        */
    }
    graph ->ArcNum = graph -> arcs[0][0] . adj;
    return (1);
}

int CreateUDG(MGraph *graph)
//����ͼ
{

    if(!graph) return 0;
    printf("�������ߵ�����,�㲻����20\n");
    scanf("%d",&(graph -> VexNum));
    printf("����������������Ϣ��\n");
    int i,j,ver1,ver2;
    for( i = 1 ; i <= graph -> VexNum ; i++)
    {
        scanf("%d",&j);
        ( graph -> Vertexes )[i] = j;
    }
    printf("�����������Ϣ,��#��β\n");
    for( i = 1 ; getchar() != '#'; i++)
    {
        printf("������ʼ����յ�:\n");
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
        //��Ϊ��������Ȩͼ
        graph ->arcs[ver1][ver2].adj  = graph ->arcs[ver2][ver1].adj = 1;
        graph ->arcs[0][0].adj += 1;
        graph ->arcs[ver1][0].adj += 1;
        graph ->arcs[ver2][0].adj += 1;
        //��Ϊ�����������û��ʲô�ã���������ע�����Ҫ�ü����
        /*
            char *info;
            printf("������ߵ���Ϣ");
            scanf("%s",info);
            strcpy( graph ->arcs[ver1][ver2].info,info);
            strcpy( graph ->arcs[ver2][ver1].info,info);
        */
    }
    graph -> ArcNum = graph ->arcs [0][0] . adj;
    return (1);
}

int CreateUDN(MGraph *graph)
//������
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
    printf("�������ߵ�����,�㲻����20\n");
    scanf("%d",&(graph -> VexNum));
    printf("����������������Ϣ��\n");
    for( i = 1 ; i <= graph -> VexNum ; i++)
    {
        scanf("%d",&j);
        ( graph -> Vertexes )[i] = j;
    }
    printf("�����������Ϣ����#��β\n");
    for( i = 1 ; getchar() != '#'; i++)
    {
        int weight;
        printf("������ʼ�㡢�յ��Ȩ:\n");
        scanf("%d %d %d",&ver1,&ver2,& weight);
        //��Ϊ��������Ȩͼ
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
        //��Ϊ�����������û��ʲô�ã���������ע�����Ҫ�ü����
        /*
            char *info;
            printf("������ߵ���Ϣ");
            scanf("%s",info);
            strcpy( graph ->arcs[ver1][ver2].info,info);
            strcpy( graph ->arcs[ver2][ver1].info,info);
        */
    }
    graph -> ArcNum = graph ->arcs[0][0].adj;
    return (1);
}

int CreateGraph(MGraph **graph)//Ĭ��graph = 0
{
    MGraph *newbase;
    newbase = (MGraph *)calloc(1,sizeof(MGraph));
    if(!newbase) return (0);
    *graph =newbase;
    GraphKind kind;
    printf("������ͼ������:\n");
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
//�������������е�λ��
{
    for (int i = 1; i <= MAX_VERTEX_NUM ; i++)
    {
        if(graph.Vertexes[i] == value)
        return (i);
    }
}

int GetVex(MGraph graph,int ver)
//verΪ���������е�λ��
{
    return (graph.Vertexes[ver]);
}

int PutVex(MGraph *graph,int ver)
//verΪ���������е�λ��
{  
    printf("������ֵ��\n");
    scanf("%d",&(graph ->Vertexes[ver]));
    return 4;
}

int FirstAdjVex(MGraph graph , int ver_value)
/*
    �����ver��value
    ��һ�������ڽ��������һ��ֵ
    ����ver������λ�� -5��ʾ��������ͨ����
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
        //printf("���ڽӵ�\n");
        return (-5);
    }
    else
    {
        for ( j = 1; j <= MAX_VERTEX_NUM; j++)
        {
            if(graph.arcs[i][j].adj && graph.arcs[i][j].adj != INFINITY && i !=  j) break;
        }
    }
    //printf("�ڽӵ�����������%d����value��%d\n",j,graph.Vertexes[j]);
    //����ֵ
    //��λʹ��locate ����printf��
    return (j);
} 

int NextAdjVex(MGraph graph,int ver1_value,int ver2_value)
/*
    �����ver1��value
    ��������λ�� -6��ʾver2�����һ��
    �Ծ���λ�ñ�ʾ�ڽӵ��λ��
*/
{
    int ver1,ver2,i,state = 0;
    //��λver1
    for(ver1 = 1; ver1 <=  MAX_VERTEX_NUM ; ver1++)
    {
        if(graph.Vertexes[ver1] == ver1_value)
            break;
    }
    //��λver2
    for (ver2 = 1; ver2 <=  MAX_VERTEX_NUM ; ver2++)
    {
        if(graph.Vertexes[ver2] == ver2_value)
            break;
    }
    //���濪ʼ����
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
        //printf("�ڽӵ�����������%d����value��%d\n",i,graph.Vertexes[i]);
        //����ֵ
        //��λʹ��locate ����printf��
        return (i);        
    }
    else
    { 
        //printf("���ڽӵ�\n");
        return (-6);
    }
}

int InsertArc(MGraph *graph,int ver1_value , int ver2_value)
/*
    ��д�ӱߵĺ���������Ҫ��
    �ɹ�7 ʧ��-7
*/
{
    if(!graph)  return (-7);
    int ver1,ver2,state1 = 0,state2 = 0;
    //��λver1
    for(ver1 = 1; ver1 <=  MAX_VERTEX_NUM ; ver1++)
    {
        if(graph -> Vertexes[ver1] == ver1_value)
        {
            state1 = 1;
            break;
        }    
    }
    //��λver2
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
        //����û�и�����Ϣ�������Ҫ��ǰ��create�еİ�ͼ���͸��Ƽ���
        case(DG)://����ͼ
        {
            graph ->arcs[ver1][ver2].adj = 1;
            graph ->arcs[0][0].adj ++;
            graph ->arcs[ver1][0].adj += 1;
            break;           
        }
        case(DN)://������
        {
            int weight;
            printf("������Ȩֵ");
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
            printf("������Ȩֵ");
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
    ���붥��
    û��λ�����Ƿ���-9
    ���Ƿ���9
*/
{
    int i ,j;
    //��ʼ���Ƿ��п�λ
    if(graph ->VexNum == MAX_VERTEX_NUM)
    {//��λ��
        printf("�޿ɲ���λ��\n");
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
        //�ӱ����￼�ǵ��������ӣ���Ϊ�����У��������������Եù��ڴ�
        int state = 1;
        int ver2_value;
        if(graph-> kind == DN ||graph -> kind == DG)
        {
            while (getchar() != '#')
            {
                printf("����������Ϊʼ��ı�(����������ֵ��ʾ)(#����)\n");
                scanf("%d",&ver2_value);
                InsertArc(graph,ver_value,ver2_value);
            }
            while (getchar() != '#')
            {
                printf("����������Ϊ�յ�ı�(����������ֵ��ʾ)(#����)\n");
                scanf("%d",&ver2_value);
                InsertArc(graph,ver2_value,ver_value);//Ȩֵ��������
            }
        }
        else
        {
            while (getchar() != '#')
            {
                printf("��������һ������(����������ֵ��ʾ)(#����)\n");
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
    ��д���ߵĺ���������Ҫ��
    �ɹ�8 ʧ��-8
*/
{
    if(!graph)  return (-8);
    int ver1,ver2,state1,state2;
    //��λver1
    for(ver1 = 1; ver1 <=  MAX_VERTEX_NUM ; ver1++)
    {
        if(graph -> Vertexes[ver1] == ver1_value)
        {
            state1 = 1;
            break;
        }    
    }
    //��λver2
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
        //����û�и�����Ϣ�������Ҫ��ǰ��create�еİ�ͼ���͸��Ƽ���
        case(DG)://����ͼ
        {
            if(graph ->arcs[ver1][0].adj)//���Ƿ��б�
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
        case(DN)://������
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
    ɾ������
    û�ж������Ƿ���-10
    ���Ƿ���10
*/
{
    //��ʼ���Ƿ��п�λ
    if(!graph)    return (-10);
    //��λ
    int ver1,state1;
    //��λver1
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
        //���濪ʼɾ��
        int state = 1;
        int ver2;
        if(graph-> kind == DN ||graph -> kind == DG)
        {
            for ( ver2 = 1; ver2 < MAX_VERTEX_NUM; ver2 ++)
            {
                if(graph ->arcs[ver1][ver2].adj && graph ->arcs[ver1][ver2].adj  != INT_MAX)//jΪʼ���
                {
                    DeleteArc(graph,ver_value,graph -> Vertexes[ver2]);
                }
                if(graph ->arcs[ver1][ver2].adj && graph ->arcs[ver1][ver2].adj  != INT_MAX)//jΪ�յ��
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
    printf("��������ֵ��:%d\n",graph.Vertexes[i]);
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
//������⺯�����������Ƿ���ʵ�����
{
    int ContrleArray[MAX_VERTEX_NUM + 1]={0};
    int value;
    printf("��������ֵ\n");
    scanf("%d",&value);
    value = LocateVex(graph,value);
    DFS(graph,ContrleArray,value,visit);
    return (11);
}

int visit_djs(MGraph graph,int *table,int i  )
{
    printf("%d��Ȩֵ��:%d\n",graph.Vertexes[i],table[i]);
    return (1);
}



int Traverse_djs(MGraph graph,int v0,int *table,int (*visit)(MGraph graph ,int i  ))
//������⺯�����������Ƿ���ʵ�����
{
    VertexType w;
    int i ,j,k,l;
    int route[MAX_VERTEX_NUM + 1] = {0};
    for( i = 1 ; i <= graph .VexNum ; i++)
    {
        route [ 0] = 0;
        route [ 1] = v0;
        for (j  = 2; j <= MAX_VERTEX_NUM; j++)
        {
            route[j] = 0;
        }
        l = 1;
        if(table[i] == INFINITY ) continue;
        else
        {
            
            printf("��v0��v%d����:v0",graph.Vertexes[i]);
            for(j = 1; j <= graph . VexNum; j++)
            {
                if(graph.arcs[i][j].adj )
                {
                    route[l ++] =  j;
                    route [ 0 ] ++;
                }
            }  
            //route[l ++] =  i;
            //route [ 0 ] ++;      
            for ( j = 2; j <=  route [ 0]  && j <= graph .VexNum ; j++)
            {
                for ( k =  j + 1; k <= route [ 0] &&  k <= graph .VexNum; k++)
                {
                    if(table[route[j]]  > table[route[k]]   )
                    {
                        l = route[j];
                        route[j] = route [k];
                        route [k] = l ;
                    }
                }
                
            }
             for ( j = 2; j <=  graph .VexNum ; j++)
            {
                if(route [j])
                {
                    printf(" -> v%d",graph.Vertexes[route [j]]);
                }
            }
            printf("\tȨֵΪ%d\n",table[i]);
        }
    }
    return (14);
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
//������⺯�����������Ƿ���ʵ�����
{
    int ContrleArray[MAX_VERTEX_NUM + 1]={0};
    SqQueue queue;
    queue.front = queue . rear = 0;
    int v,value;//�����ڶ��������λ��
    printf("�����뿪ʼ���ֵ\n");
    scanf("%d",&value);
    v = LocateVex(graph,value);//�����û�Ϊ��
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
 
int    ShortestPath_djs(MGraph graph,int ver_value,int **PathMatrix,int *ShortPathTable)
{
    int *final;
    final = (int * )calloc(graph.VexNum +1,sizeof( int ) );
    int v,v0,w;
    v0 = LocateVex(graph,ver_value);
    //���濪ʼ��ʼ��
    for ( v = 1; v <= graph.VexNum; v++)
    {
        final[v] = 0;
        ShortPathTable[v] = graph.arcs[v0][v].adj;
        for(w = 1; w <= graph . VexNum ; w ++ )
            PathMatrix[v][w] = 0;
        if(ShortPathTable[v] < INFINITY)
        {
            PathMatrix[v][v0] = 1;
            PathMatrix[v][v] = 1;
        }
    }
    ShortPathTable[v0] = 0;
    final[v0] = 1;
    //�ؼ�·��
    int min;
    v = v0;
    for (int i = 1 ; i <= graph . VexNum ; i++)
    {
        if( graph.Vertexes[i] != graph.Vertexes[v0])
        {
            min = INFINITY ;
            for(w = 1;w <= graph . VexNum; w ++ )
            {
                if(!final[w])
                {
                    if(ShortPathTable[w] < min && ShortPathTable[w] >= 0)
                    {
                        v = w ;
                        min = ShortPathTable[w];
                    }
                }
            }
            final[v] = 1;//�ҵ���v���뼯��
            //ά��Ȩֵ����
            for(w = 1 ;w <= graph . VexNum ; w ++ )
            {
                if(!final[w]&& (min + graph.arcs[v][w] . adj) > 0 &&(min + graph.arcs[v][w] . adj < ShortPathTable[w]))
                {
                    ShortPathTable[w] = min + graph .arcs[v][w].adj;
                    for (int  i = 0; i <= graph . VexNum  ; i++)
                    {
                        PathMatrix[w][i] = PathMatrix[v][i];
                    }
                    PathMatrix[w][w] = 1;
                }
            }
        }
    }
    //��Ŀ����ʼ���·��
    MGraph djs = graph;
    PathMatrix[0][0] = graph .VexNum;
    for ( v = 0; v <= graph.VexNum; v++)
    {
        for(w = 0; w <= graph . VexNum ; w ++ )
        {
            djs . arcs[v][w] . adj = PathMatrix[v][w];
        }
    }
    Traverse_djs(djs,v0,ShortPathTable,visit);

}

int main()
{
    MGraph *graph = 0;
    CreateGraph(&graph);
    int **PathMatrix,*ShortPathTable,ver_value;
    PathMatrix = (int **) calloc(graph -> VexNum + 1,sizeof(int*));// 0�Ų��ú�graph->arcsһ��
    for (int i = 0; i < graph -> VexNum + 1 ; i++)
    {
         PathMatrix[i] = (int *) calloc(graph -> VexNum + 1,sizeof(int));
    }
    ShortPathTable= (int *) calloc(graph -> VexNum + 1,sizeof(int));
    printf("������Ҫ���ֵ\n");
    scanf("%d",&ver_value);
    ShortestPath_djs(*graph,ver_value,PathMatrix,ShortPathTable);
    DestoryGraph(graph);
    system("pause");
    return 0;
}

