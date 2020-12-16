#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100 //初始地址大小
#define STACKINCREMENT 10//增量
//定义 如果栈空错误 ，就返回0
//自定义用户数据类 （先内含int栈示

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
    if(!newbase) exit(0);//系统错误，直接退出
    else
    {
        stack -> base = newbase;
        stack -> top = newbase ;
        stack -> StackSize = STACK_INIT_SIZE;
        return 1;
    }
}//创建栈 成功一
//空栈 ：top = base + 1

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
}//销毁栈 成功2 未知失败 -2

int ClearStack(SqStack *stack)
{    
    if(stack == 0) return(0);
    else
    {
        stack -> top = stack -> base ;
        return 3;
    }
    return -3;
}//清空栈 成功3 未知失败 -3

int StackEmpty(SqStack stack)
{    
    if(&stack == 0) return(0);
    if(stack.base  == stack.top) return 4;
    else{return -4;    }
}//判断栈空 4空 -4不空

int StackLength(SqStack stack)
{
    if(&stack == 0) return(0);
    return (stack.top  - stack.base);
}//栈长 返回长度

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
}//得栈头 成功5 失败-5

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
}//入栈 成功6 失败-6

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
}//删除栈头 成功7 失败-7

int visit(SElemType *elem)
{
    if(elem == 0) return(0);
    else
    {
        if(printf("这个元素是：%d\n",elem -> data)) return (1);
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
    printf("中文使用的是GBK。Simplified Chinese using GBK.\n");
    SqStack s;
    InitStack(&s);
    SElemType elem;
    int i ;
    printf("stack是否为空：%d（4为空，-4为非空）\n",StackEmpty(s));
    printf("我们先写几个,然后入栈：(为了方便elemtype里只有一个int型,以#结尾)\n");
    for(;;)
    {
        scanf("%d",&elem.data);
        Push(&s,elem);//为了方便
        if(getchar() == '#')
        {
            break;
        }
    }
    printf("ok 结束显示全栈\n");
    StackTraverse(&s,visit);
    printf("length:%d\n",StackLength(s));
    GetTop(s,&elem);
    printf("get:%d\n",elem);
    printf(" ok 结束显示全栈\n");
    StackTraverse(&s,visit);
    Pop(&s,&elem);
    printf("pop:%d\n",elem);
    printf(" ok 结束显示全栈\n");
    StackTraverse(&s,visit);
    printf("clear list\n");
    ClearStack(&s);
    printf("sq是否为空：%d（4为空，-4为非空）\n",StackEmpty(s));
    DestroyStack(&s);
    system("pause");
    return 0;
}