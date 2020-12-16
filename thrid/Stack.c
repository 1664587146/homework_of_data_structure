#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100 //��ʼ��ַ��С
#define STACKINCREMENT 10//����
//���� ���ջ�մ��� ���ͷ���0
//�Զ����û������� �����ں�intջʾ

typedef struct
{
    int data;
}SElemType;

typedef struct SqStack
{
    SElemType *top;
    SElemType *base;
    int StackSize;
}SqStack;

int InitStack(SqStack *stack)
{
    //if(stack != 0) free(stack);
    SElemType *newbase;
    newbase = (SElemType *)(malloc(STACK_INIT_SIZE * sizeof(SElemType)));
    if(!newbase) exit(0);//ϵͳ����ֱ���˳�
    else
    {
        stack -> base = newbase;
        stack -> top = newbase ;
        stack -> StackSize = STACK_INIT_SIZE;
        return 1;
    }
}//����ջ �ɹ�һ
//��ջ ��top = base + 1

int DestroyStack(SqStack *stack)
{
    if(stack == 0) return(0);
    else
    {
        free(stack ->base);
        stack -> base = stack -> top = 0;
        stack -> StackSize = 0;
        return 2;
    }
    return -2;
}//����ջ �ɹ�2 δ֪ʧ�� -2

int ClearStack(SqStack *stack)
{    
    if(stack == 0) return(0);
    else
    {
        stack -> top = stack -> base ;
        return 3;
    }
    return -3;
}//���ջ �ɹ�3 δ֪ʧ�� -3

int StackEmpty(SqStack stack)
{    
    if(&stack == 0) return(0);
    if(stack.base  == stack.top) return 4;
    else{return -4;    }
}//�ж�ջ�� 4�� -4����

int StackLength(SqStack stack)
{
    if(&stack == 0) return(0);
    return (stack.top  - stack.base);
}//ջ�� ���س���

int GetTop(SqStack stack,SElemType *elem)
{
    if(&stack == 0) return(0);
    if(elem -> data = (stack.top - 1) -> data)
    {
        return (5); 
    }
    else
    {
        return (-5);
    }
}//��ջͷ �ɹ�5 ʧ��-5

int Push(SqStack *stack,SElemType e)
{
    if(&stack == 0) return(0);
    if(stack -> base  == stack -> top)
    {
        if( (stack -> base) -> data =e.data)
        {
            stack -> top ++;
            return 6;
        }
    }
    if( (stack -> top ) -> data =e.data)
    {
        stack -> top ++;
        return 6;
    }
    else
    {
        return -6;
    }
}//��ջ �ɹ�6 ʧ��-6

int Pop(SqStack *stack,SElemType *elem)
{
    if(&stack == 0) return(0);
    if(elem -> data =( ((stack ->top)--) - 1) -> data)
    {
        return (7); 
    }
    else
    {
        return (-7);
    }
}//ɾ��ջͷ �ɹ�7 ʧ��-7

int visit(SElemType *elem)
{
    if(elem == 0) return(0);
    else
    {
        if(printf("���Ԫ���ǣ�%d\n",elem -> data)) return (1);
        else{return (0);}
    }
}
int StackTraverse(SqStack *stack,int (*visit)(SElemType* ))
{
    if(stack == 0) return(0);
    SElemType *node;
    int state;
    for(state =0,node = stack -> base;node < stack -> top;node++)
    {
        if(visit(node)) {state = 1;}
        else {state = 0;}
    }
    if(state == 1) return(8);
    else{return(-8);}
}

int main()
{
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n");
    SqStack s;
    InitStack(&s);
    SElemType elem;
    int i ;
    printf("stack�Ƿ�Ϊ�գ�%d��4Ϊ�գ�-4Ϊ�ǿգ�\n",StackEmpty(s));
    printf("������д����,Ȼ����ջ��(Ϊ�˷���elemtype��ֻ��һ��int��,��#��β)\n");
    for(;;)
    {
        scanf("%d",&elem.data);
        Push(&s,elem);//Ϊ�˷���
        if(getchar() == '#')
        {
            break;
        }
    }
    printf("ok ������ʾȫջ\n");
    StackTraverse(&s,visit);
    printf("length:%d\n",StackLength(s));
    GetTop(s,&elem);
    printf("get:%d\n",elem);
    printf(" ok ������ʾȫջ\n");
    StackTraverse(&s,visit);
    Pop(&s,&elem);
    printf("pop:%d\n",elem);
    printf(" ok ������ʾȫջ\n");
    StackTraverse(&s,visit);
    printf("clear list\n");
    ClearStack(&s);
    printf("sq�Ƿ�Ϊ�գ�%d��4Ϊ�գ�-4Ϊ�ǿգ�\n",StackEmpty(s));
    DestroyStack(&s);
    system("pause");
    return 0;
}