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
//��ͷ�սڵ�
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
}//�������� �ɹ�1

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
    //��Ϊ�������������front ����MinG�޷�ɾ�� 
    return (2);
}//���ٶ��� �ɹ�2

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
}//��ն��� �ɹ�3

int QueueEmpty(LinkQueue queue)
{
    if(queue.front == queue.rear ) return 4;
    else { return -4;}
}//��4 �ǿ�-4

int QueueLength(LinkQueue queue)
{
    int i = 0;
    QNode *node;
    for(node = queue.front;node != queue.rear;node = node ->next,i++);
    return (i);
} //���س���i

int GetHead(LinkQueue queue,QElemType *elem)
{
    if(!elem) return(0); 
    *elem = ((queue.front) -> next) -> data;
    return (5);
}//�ñ�ͷ �ɹ�5

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
}//��� �ɹ�6 ʧ��-6

int DeQueue(LinkQueue *queue,QElemType* elem)
{
    if(queue == 0 || elem == 0) return (0);
    *elem = ((queue -> front) -> next) -> data ;
    (queue -> front) -> next = ((queue -> front) -> next) ->next;
    return (7);
}//���� �ɹ�7 

int visit(QElemType elem)
{
    if(printf("���Ԫ���ǣ�%d\n",elem.d)) return (1);
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
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n");
    LinkQueue queue;
    IntiQueue(&queue);
    QElemType elem;
    int i ;
    printf("Queue�Ƿ�Ϊ�գ�%d��4Ϊ�գ�-4Ϊ�ǿգ�\n",QueueEmpty(queue));
    printf("������д����,Ȼ����ӣ�(Ϊ�˷���elemtype��ֻ��һ��int��,��#��β)\n");
    for(;;)
    {
        scanf("%d",&elem.d);
        EnQueue(&queue,elem);//Ϊ�˷���
        if(getchar() == '#')
        {
            break;
        }
    }
    printf("ok ������ʾȫ��\n");
    QueueTraverse(queue,visit);
    printf("length:%d\n",QueueLength(queue));
    GetHead(queue,&elem);
    printf("get:%d\n",elem.d);
    printf(" ok ������ʾȫ��\n");
    QueueTraverse(queue,visit);
    DeQueue(&queue,&elem);
    printf("Dequeue:%d\n",elem);
    printf(" ok ������ʾȫ��\n");
    QueueTraverse(queue,visit);
    printf("clear list\n");
    ClearQueue(&queue);
    printf("sq�Ƿ�Ϊ�գ�%d��4Ϊ�գ�-4Ϊ�ǿգ�\n",QueueEmpty(queue));
    DestroyQueue(&queue);
    system("pause");
    return 0;
}