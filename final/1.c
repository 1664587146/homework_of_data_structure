/*
    设计一个程序，每秒统计一次当前系统的进程状况，并按照内存使用自多到少排序打印输出相关信息。
    对已经结束的进程，另外给出一个列表，并显示该进程的结束时间和持续时间。
    数据类型：链表，链表栈。
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
    链表类型都是双向链表，而且都含表头
*/
#define MAX_LENGTH_OF_MANE 80//名字最长长度
static int time = 0;
//time人工定义的系统时钟
//执行一个操作加一秒
typedef struct LinkNode
{
    char    Name_of_process[MAX_LENGTH_OF_MANE];//名字
    int     PID;//进程编号
    double  ram_the_process_using;//用了多少内存
    long     start_time,end_time;//开始时间，结束时间
    LinkNode *next,*front; //后（前）一个结点
    /*
        在栈链表的表头中 next表示栈底，front表示栈顶。
        在运行中程序的链表中只负责连接首尾。
    */
}LinkNode,*LinkList;
/*
    数据从1.txt读入
*/
int create(LinkList* list);
int Read_Data(LinkList program);
int start(LinkList active_process,LinkList killed_process ,LinkList total_process,char *name);
int kill(LinkList killed_process,LinkList active_process,char *name);
//int restart(LinkList active_process,LinkList killed_process ,char *name);

int main()
{
    LinkList program = 0;//用来存所有的程序，作用：帮助将txt中的内容读入程序。
    //将数据读入将使用函数。
    LinkList active_process = 0;//双向链表。
    LinkList killed_process = 0;//链表栈 ，因为二者要互相转换，所以都用双向链表的结点。
    //用linklist* 是方便后面free，因为主程序申请的内存生命周期是程序结束。
    create(&program);//建表,因为要改变program值所以传指针
    create(&active_process);
    create(&killed_process);
    Read_Data(program);//实参为linklist*
    LinkList q;
    //开始打印正在使用的进程
    printf("名字\t进程id\t内存使用(K)\n");
    for( q = program -> next ; q != program; q = q -> next)
    {
        printf("%s\t\t\t%d\t%f\n",q->Name_of_process,q ->PID ,q->ram_the_process_using);
    }
    int state = 1;
    printf("现在令全部进入执行状态\n");
    start(active_process,killed_process,program,"COD16");
    start(active_process,killed_process,program,"GTA5");
    start(active_process,killed_process,program,"VSCODE");
    start(active_process,killed_process,program,"QQ");
    printf("输出执行中进程的名字\t进程id\t运行时间(s)\t内存使用(K)\n");
    int i = 1;
    for( q = active_process -> next ; q != active_process; q = q -> next)
    {
        printf("%s\t\t\t%d\t%d\t%f\n",q->Name_of_process,q ->PID,( - q ->start_time + time)  ,q->ram_the_process_using);
    }
    printf("下面开始加入不存在的:(name):(BILIBILI)\n");
    start(active_process,killed_process,program,"BILIBILI");
    printf("现在kill GTA5 和qq\n");
    kill(killed_process,active_process,"GTA5");
    kill(killed_process,active_process,"QQ");
    printf("输出执行中进程的名字\t进程id\t运行时间(s)\t内存使用(K)\n");
    for( q = active_process -> next ; q != active_process; q = q -> next)
    {
        printf("%s\t\t\t%d\t%d\t0.2%f\n",q->Name_of_process,q ->PID,( - q ->start_time + time)  ,q->ram_the_process_using);
        //CLOCKS_PER_SEC为计算机的一秒的时间单位，在time.h中已定义
    }

    printf("输出结束进程的名字\n");
    for( q = killed_process -> next ; q != killed_process; q = q -> next)
    {
        printf("%s\n",q->Name_of_process);
        //CLOCKS_PER_SEC为计算机的一秒的时间单位，在time.h中已定义
    }    

    printf("现在重启 GTA5\n");
    start(active_process,killed_process,program,"GTA5");
    time ++;
    printf("执行中进程的名字\t进程id\t运行时间(s)\t内存使用(K)\n");
    for( q = active_process -> next ; q != active_process; q = q -> next)
    {
        printf("%s\t\t\t%d\t%d\t%0.2f\n",q->Name_of_process,q ->PID,( - q ->start_time + time)  ,q->ram_the_process_using);
        //CLOCKS_PER_SEC为计算机的一秒的时间单位，在time.h中已定义
    }    
    printf("输出结束进程的名字\n");
    for( q = killed_process -> next ; q != killed_process; q = q -> next)
    {
        printf("%s\n",q->Name_of_process);
        //CLOCKS_PER_SEC为计算机的一秒的时间单位，在time.h中已定义
    }    
    system("pause");
    return (0);
}


int start(LinkList active_process,LinkList killed_process,LinkList total_process,char *name)
/*
    先在total——process中定位name，name即要启动的进程时间，
    然后记入启动时间，记录
*/
{
    time ++;
    if(name == 0) 
    {
        printf("name为空");
        return 0;
    }
    LinkList p = 0,q = 0,r = 0 , h = 0;
    int state = 0,state1 = 0;
    //开始找到名字为name的进程
    for(p = total_process -> next;p != total_process ;p = p -> next)
    {
        if(strcmp(p ->Name_of_process,name) == 0 )
        {
            //找到state变1，结束循环
            state = 1;
            break;
        }
    }
    //然后确定是否已经启动
    for(q = active_process -> next ; q != active_process ;q = q -> next)
    {
        if(strcmp(q -> Name_of_process,name) == 0 )
        {
            //找到state变1，结束程序
            printf("进程已启动");
            return (-3);
        }
    }
    //然后看看是否在killed里面
    for(h = killed_process -> next;h != killed_process ;h = h -> next)
    {
        if(strcmp(h ->Name_of_process,name) == 0 )
        {
            //找到state变1，结束循环
            state1 = 1;
            break;
        }
    }
    if(state && !state1)
    //不在killed中
    //找到了，加入到active中，
    {
        //下面将找到的进程加入到active中
        //不想破坏total——process
        q = (LinkList )calloc(1, sizeof(LinkNode));
        //复制p中的中的数据;
        q -> start_time = time;
        strcpy(q -> Name_of_process , p -> Name_of_process);
        q -> PID = p -> PID;
        q -> ram_the_process_using = p -> ram_the_process_using;
        //下面开始定位加的位置
        for (p  = active_process; p -> next!= active_process ;p = p ->next)
        {
            if(q ->ram_the_process_using > p ->next ->ram_the_process_using)
            //通过对比内存找到插入位置
            {
                break;
            }
        }
        r = p -> next;
        p -> next = q;
        q -> next = r;
        r -> front = q;
        q -> front = p;
        return (3);

    }
    else if(state && state1 )
    //在killed中
    {        
        //下面将找到的进程加入到active中
        //破坏killed
        //先将表断开,然后连起来
        h -> start_time = time ;
        r = h -> front;
        q = h -> next ;
        r -> next = q;
        q -> front = r;
        //下面开始定位加到哪
        //下面开始定位加的位置
        q = h;
        for (p  = active_process; p -> next!= active_process ;p = p ->next)
        {
            if(q ->ram_the_process_using > p ->next ->ram_the_process_using)
            //通过对比内存找到插入位置
            {
                break;
            }
        }
        //加入到表
        r = p -> next;
        p -> next = q;
        q -> next = r;
        r -> front = q;
        q -> front = p;
        return (4);

    }
    else
    {
        printf("无效进程\n");
        return (-3);
    }
}

/*
    和start差不多
*/

int kill(LinkList killed_process,LinkList active_process,char *name)
{
    time ++ ;
    if(name == 0) 
    {
        printf("name为空");
        return 0;
    }
    LinkList p = 0,q = 0,r = 0;
    int state = 0;
    //开始找到名字为name的进程
    for(p = active_process -> next;p != active_process ;p = p -> next)
    {
        if(strcmp(p ->Name_of_process,name) == 0 )
        {
            //找到state变1，结束循环
            state = 1;
            break;
        }
    }
    //p就是已经找到得进程
    //然后确定是否已经kill
    for(q = killed_process -> next ; q != killed_process ;q = q -> next)
    {
        if(strcmp(q -> Name_of_process,name) == 0 )
        {
            //如果已经kill结束程序
            printf("程序错误");
            return (-4);
        }
    }
    if(state)
    //找到了，加入到kill中，
    {
        //下面将找到的进程加入到kill中
        //破坏active
        //先将表断开
        r = p -> front;
        q = p -> next ;
        r -> next = q;
        q -> front = r;
        p -> start_time = 0;//杀死时间为0
        //将p加入kill表，不管大小
        q = killed_process -> next;
        p -> next = q;
        killed_process -> next = p;
        q -> front = p;
        p -> front = killed_process; 
        return (4);

    }
    else
    {
        printf("无效进程\n");
        return (-4);
    }
}


int Read_Data(LinkList program)
/*
    从文件读入数据
    文件是文本文件。
    而且只有一个文件所以指定文件名，不过输入文件名保留
    如果使用system("tasklist  /fo  csv)程序超过200，太多，所以简化进程情况，自己写。csv
*/
{
    time ++ ;
    LinkList p = 0,q = 0;//两个辅助变量
    FILE *file = 0;
    /*
        //输入文件名的程序，只不过这里不需要使用，所以注解掉
        //如果要使用，直接去注解
        char mane_of_file[80];
        scan("%s",name_of_file);
    */
    file = fopen("1.txt","r+");
    if(!file)
    {
        printf("文件打开错误");
         exit(0);//错误处理
    }
    p = program;
    while (!feof(file))
    {
        //读取数据
        char waste;        
        q = (LinkList ) calloc(1 , sizeof(LinkNode));
        fscanf(file,"%s %d %lf%c", q -> Name_of_process, &(q -> PID),&(q -> ram_the_process_using),&waste);
        q -> front = p;//帮助处理多读的数据
        p -> next = q;
        p = p -> next;
        fseek(file,SEEK_CUR,4);
    }
    //最后一个数据多读，处理掉最后一个多读
    q = q -> front;//q为最后一个
    p = q -> next;
    q -> next = program;
    program -> front = q;
    free(p);
    fclose(file);
    return (2);
}


int create(LinkList* list)
//建表,因为要改变list值所以多传个指针
{
    time ++;
    if((*list) != 0 ) free(*list);
    else
    {
        (*list)  = (LinkList ) calloc(1 , sizeof(LinkNode));
        (*list) -> next = (*list) -> front = (*list);
        //申请表头空间
    }
    if(!list) exit(0);//分配错误，退出
    else
    { 
        //认为头结点使用内存最大
        (*list) -> ram_the_process_using =INT_MAX;
        return 1;//正常
    }
}

