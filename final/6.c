/*
    [��������]
    ��������ķ�㷨�Ϳ�³˹�����㷨ʵ����С���������⡣
    [����Ҫ��]
    ��1�����н���ͼ�������ļ�����һ���Ƕ��������Ȼ�������Ƕ��������������Ǳߣ���float��ʾ�ߵ�Ȩֵ��
    ��2�����ڽӱ�����ڽӾ����ʾͼ�Կɣ�
    ��3���ֱ�����prim��Kruskal�㷨ʵ����С��������
    ��4�������С��������Ȩֵ֮�ͣ������õıߡ�
    ���ݽṹ���ڽӾ���
*/
#include <stdio.h>
#include<stdlib.h>

#define  SELECTED 1
#define INABLE -1
#define ABLE 0

#define INFINITY 999//���ֵ��������ͼ�б�ʾû�б�
#define MAX_VERTEX_NUM 20
typedef enum{DG = 1,DN,UDG,UDN} GraphKind;
//����ͼ��������������ͼ��������
typedef double VRType;
//�������� ��Ȩ��1/0��ʾ�Ƿ�����
//������Ȩֵ����������999,Ĭ����ȨֵΪ100%,ʡ��0�͸���
typedef char InfoType ;

typedef struct ArcCell
{
    VRType adj;
    InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM + 1][MAX_VERTEX_NUM + 1];
/*
    AdjMatrix[0][X] AdjMatrix[X][0]���� �����Է���������Ϣ
    AdjMatrix[0][0]��ʾ�߸��� 
    AdjMatrix[x][0]��ʾ�����ڽӽڵ�ĸ���(x >= 1) 
*/
typedef int VertexType;

typedef struct 
{
    //����
    VertexType Vertexes[MAX_VERTEX_NUM + 1];//�����ֱ�� vertexes[0]����
    //�ڽӾ���
    AdjMatrix arcs;
    //��ߵ�����
    int VexNum,ArcNum;
    GraphKind kind;
}MGraph;

//������ͼ���йز���
int CreateUDN(MGraph *graph);
int CreateGraph(MGraph **graph);
int DestoryGraph(MGraph *graph);
int LocateVex(MGraph graph,int value);
/*
    ��Ϊ������ڽӾ�����ǰ��д����
    ��������͵��ֱ�Ӹ����ˣ����Բ�֧���ļ�����
*/
//��������Ҫ�㷨
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
    ��Ҫ˼�룺
    1��ѡ��һ������Ϊ��ʼ�㣬���뼯��
    2�����ͼ����ڵ����ڵ���СȨֵ�����·���������¸����㵽���ϵ���Ȩֵ
    3���ظ�2
*/
{
    //graph . ArcNum <= 1 ���ô���
    if (graph . ArcNum == 1 || graph . ArcNum  == 0)
    {
        printf("�������");
        return (1109);
    }
    float *weight;
    //ʼ�㵽�������Ȩֵ
    //û�о���infinity
    int i,j,l,ver_value,ver,*vers[2];
    weight = (float * )calloc(graph . ArcNum + 1,sizeof(float));
    //��0������
    for ( i = 0; i < 2; i++)
    {
        vers[i] = (int * )calloc(graph . ArcNum + 1,sizeof(int));
    }
    /*
        vers[1][0]����û���뼯��
        vers��ʾ�������Ϣ 
        ��ʾ�������Ϣ 
        vers[1][x] == 0 ��ʾ���ڼ�����
        ��Ϊ��ֱ�ӽ�ͼ�ģ�����ֱ�Ӷ�ǰ graph . VexNum��
    */
    for (int i = 1; i <= graph.VexNum; i++)
    {
        vers[0][i] = graph .Vertexes[i];
    }
    for (size_t i = 0; i <= graph . VexNum; i++)//��weight���г�ʼ������ʼΪinfinity
    {
        weight[i] = INFINITY ;
    }
    //           vers[1][0]����û���뼯��
    vers[1][0] = graph . VexNum ;
    //���㼯�϶�Ӧ�����ֵ
    printf("������ʼ���ֵ\n");
    scanf("%d",&ver_value);
    //��λver
    ver = LocateVex(graph , ver_value);
    vers[1][ver] = 1;
    vers[1][0] -- ;
    weight[ver] = 0;//��ʼ����Ϊ0
    int last_into_set;
    last_into_set = ver;
    while ( vers[1][0])
    {
        //��ʼά������
        //ֻҪ���¼���ĵ���оͿ���
        for ( i = 1; i <= graph . VexNum ; i++)
        {
            if(vers [1][i] == 0 && graph . arcs[last_into_set][i] . adj  + weight[last_into_set] < weight[i])
            //��������
            //1�����ڼ�����
            //2���µ���Ȩֵ��С
            {
                weight[i] = graph . arcs[last_into_set][i] . adj + weight[last_into_set];
            }
        }
        //���濪ʼ�ҵ���С��
        int min_of_weight = INFINITY,min = -1;
        for ( i = 1; i <= graph . VexNum ; i++)
        {
            if (vers [1][i] == 0 && weight[i] < min_of_weight)
            {
                min = i ;
                min_of_weight = weight[i];
            }
        }
        //�ҵ���
        last_into_set = min;
        vers[1][last_into_set] = 1;
        vers[1][0] -- ;
    }
    for ( i = 1; i <= graph . VexNum ; i++)
    {
        //
        printf("����%d��Ȩֵ��:%f\n",vers[0][i],weight[i]);
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
    //��ʼ�ж�����ͬ��ͨ
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
    //graph . ArcNum <= 1 ���ô���
    if (graph . ArcNum == 1 || graph . ArcNum  == 0)
    {
        printf("�������");
        return (1109);
    }
    int i ,j,*tree,a,statue,statue1 ,k,*help[4];//��æ����������
    float *weight,q;
    /*
        helpΪ�߼���
        help��1����x����ʾ�Ƿ���tree�����ܷ�ѡȡ,��ϸ��define
        help��2����x����help��3����x������������
        weight[]��ʾȨֵ
        help[0][x]����
        help[x][0]����
         weight[0]����
    */
    tree =  (int * ) calloc( graph .VexNum +  1 , sizeof(int *));
    //tree[0]����
    //tree����С������ 
    weight =  (float * ) calloc( graph . ArcNum + 1 , sizeof(float ));
    for ( i = 0; i < 4 ; i++)//�߼���
    {
        help[i] =  (int * ) calloc( graph . ArcNum + 1 , sizeof(int ));
    }
    k =  graph .ArcNum;//k��ֵΪ�ߵ�����
    //���濪ʼ��ʼ��help����
    //��Ϊ��0�����ã�����i = 1��
    for ( i = 1; i <= graph .VexNum; i++)
    {
        for ( j = i + 1;j <= graph .VexNum ; j++)//��Ϊ�޻�����ͨ������
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
    //��ʼ��help������ȨֵΪ����ð��
    //�������ʹ�ÿ��ſ��Լ���O()����Ϊ���������С����ð��
    //��Ϊk��Ȧ������ѡ��С�ı�
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
            //���濪ʼ�ӵ���tree
            //tree�Ƕ��㼯
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
            //���濪ʼά������help
            //���arc�����߶���tree�� map��1����x�� == 1
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
    printf("��Ȩֵ��%0.3f\n",total_weights);
    printf("·����:\n");
    for (i = 1; i <= graph . ArcNum; i++) 
    {
        if(help[1][i] == 1)
        {
            printf("����%d������%d\n",help[2][i],help[3][i]);
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
        float weight;
        printf("������ʼ�㡢�յ��Ȩ:\n");
        scanf("%d %d %f",&ver1,&ver2,& weight);
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
