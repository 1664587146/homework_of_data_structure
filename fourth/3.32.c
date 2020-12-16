#include<stdio.h>
#include<stdlib.h>

static int No_ = 1 ;//���ڱ�ʾ�ǵڼ���쳲�������

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
        newbase -> next = newbase;
        (queue) -> front = (queue) -> rear = newbase;
        return (1);
    }
    else exit(0);
}//�������� �ɹ�1


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
    if(printf("�ڸ�%d�ǣ�%d\n",No_++,elem.d)) return (1);
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
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n");
    LinkQueue Fibonacci;
    IntiQueue(&Fibonacci);
    QElemType elem,elem1,elem2;
    int n,k,i,j,elem3;       
    printf("������쳲������ĸ����ͽ���.\n");
    scanf("%d %d",&n ,&k);
    elem1.d = elem2.d = 1;
    for(i = 1;i <n +1 ;i++)
    {
        if(i == 1)
        {
            EnQueue(& Fibonacci,elem1);
            j = 1;   
        }
        else if(i == 2)
        {
            EnQueue(& Fibonacci,elem2);   
            j ++;
        }
        else
        {
            if(j == k)
            {
                DeQueue(&Fibonacci,&elem);
                printf("��%d����%d\n",No_++,elem.d);
                //����i��쳲�������
                elem3 = elem2.d;
                elem2.d += elem1.d;
                elem1.d = elem3;
                EnQueue(&Fibonacci,elem2);
            }
            else
            {
                //����i��쳲�������
                elem3 = elem2.d;
                elem2.d += elem1.d;
                elem1.d = elem3;
                EnQueue(&Fibonacci,elem2);
                j++;
            } 
        }
    }
    printf("ok ��ʾk��쳲���������\n");
    QueueTraverse(Fibonacci,visit);
    system("pause");
    return 0;
}