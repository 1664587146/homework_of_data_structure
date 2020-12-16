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
        (queue) -> front = (queue) -> rear = newbase;
        return (1);
    }
    else exit(0);
}//创建队列 成功1

int DestroyQueue(LinkQueue *queue)
{
    if(queue == 0) return (0);
    QNode *node,*node1;
    if(((queue) -> front) -> next)
    {
        for(node = node1 = ((queue) -> front) -> next;node != NULL  ;  )
        {
            node1 = node;
            node = node -> next;
            free(node1);
        }
    }
    (queue) -> rear = (queue) -> front = 0;
    //因为是主函数申请的front 所以MinG无法删除 
    return (2);
}//销毁队列 成功2

int ClearQueue(LinkQueue *queue)
{
    if(queue == 0) return (0);
    QNode *node,*node1;
    for(node = node1 = queue -> front;  ;  )
    {
        node1 = node;
        node = node -> next;
        free(node1);
        if(node == queue -> rear )
        {
            free(node);
            break;
        }
    }
    queue -> rear = queue -> front;
    (queue -> front) -> next = 0;
    return (3);
}//清空队列 成功3

int QueueEmpty(LinkQueue queue)
{
    if(queue.front == queue.rear ) return 4;
    else { return -4;}
}//空4 非空-4

int QueueLength(LinkQueue queue)
{
    int i = 0;
    QNode *node;
    for(node = queue.front;node != queue.rear;node = node ->next,i++);
    return (i);
} //返回长度i

int GetHead(LinkQueue queue,QElemType *elem)
{
    if(!elem) return(0); 
    *elem = ((queue.front) -> next) -> data;
    return (5);
}//得表头 成功5

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
        if(node == queue.rear)
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
    printf("Queue是否为空：%d（4为空，-4为非空）\n",QueueEmpty(queue));
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
    printf("length:%d\n",QueueLength(queue));
    GetHead(queue,&elem);
    printf("get:%d\n",elem.d);
    printf(" ok 结束显示全队\n");
    QueueTraverse(queue,visit);
    DeQueue(&queue,&elem);
    printf("Dequeue:%d\n",elem);
    printf(" ok 结束显示全队\n");
    QueueTraverse(queue,visit);
    printf("clear list\n");
    ClearQueue(&queue);
    printf("sq是否为空：%d（4为空，-4为非空）\n",QueueEmpty(queue));
    DestroyQueue(&queue);
    system("pause");
    return 0;
}