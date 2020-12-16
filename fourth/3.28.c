#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int d;
}QElemType;

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;
//带头空节点
int IntiQueue(LinkQueue *queue)
{
    QueuePtr newbase;
    newbase = (QNode *)malloc(sizeof(QNode));
    if(newbase)
    {
        newbase -> next = newbase;
        (queue) -> front = (queue) -> rear = newbase;
        return (1);
    }
    else exit(0);
}//创建队列 成功1


int EnQueue(LinkQueue *queue,QElemType elem)
{
    if(queue == 0) return (0);
    QNode *node;
    node = ( QNode*) malloc(sizeof(QNode));
    if(node)
    {
        (queue -> rear) -> next = node;
        node -> data = elem;
        queue -> rear = node ;
        node -> next =queue -> front;
        return (6);
    }
    return (-6);
}//入队 成功6 失败-6

int DeQueue(LinkQueue *queue,QElemType* elem)
{
    if(queue == 0 || elem == 0) return (0);
    *elem = ((queue -> front) -> next) -> data ;
    (queue -> front) -> next = ((queue -> front) -> next) ->next;
    return (7);
}//出队 成功7 

int visit(QElemType elem)
{
    if(printf("这个元素是：%d\n",elem.d)) return (1);
    else{return (0);}
}

int QueueTraverse(LinkQueue queue,int (* visit)(QElemType ))
{
    int state = 0;
    QNode *node;
    for ( node = (queue.front) -> next;  ; node = node ->next )
    {
        if(visit(node -> data)) {state = 1;}
        else {state = 0;}
        if(node -> next== queue.front)
        {
            break;
        }
    }
    if(state == 1) return(8);
    else{return(-8);}
}

int main()
{
    printf("中文使用的是GBK。Simplified Chinese using GBK.\n");
    LinkQueue queue;
    IntiQueue(&queue);
    QElemType elem;
    int i ;
    printf("我们先写几个,然后入队：(为了方便elemtype里只有一个int型,以#结尾)\n");
    for(;;)
    {
        scanf("%d",&elem.d);
        EnQueue(&queue,elem);//为了方便
        if(getchar() == '#')
        {
            break;
        }
    }
    printf("ok 结束显示全队\n");
    QueueTraverse(queue,visit);
    DeQueue(&queue,&elem);
    printf("Dequeue:%d\n",elem);
    QueueTraverse(queue,visit);
    system("pause");
    return 0;
}