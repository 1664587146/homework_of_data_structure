/*
    ���һ������ÿ��ͳ��һ�ε�ǰϵͳ�Ľ���״�����������ڴ�ʹ���Զൽ�������ӡ��������Ϣ��
    ���Ѿ������Ľ��̣��������һ���б�����ʾ�ý��̵Ľ���ʱ��ͳ���ʱ�䡣
    �������ͣ���������ջ��
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
    �������Ͷ���˫���������Ҷ�����ͷ
*/
#define MAX_LENGTH_OF_MANE 80//���������
static int time = 0;
//time�˹������ϵͳʱ��
//ִ��һ��������һ��
typedef struct LinkNode
{
    char    Name_of_process[MAX_LENGTH_OF_MANE];//����
    int     PID;//���̱��
    double  ram_the_process_using;//���˶����ڴ�
    long     start_time,end_time;//��ʼʱ�䣬����ʱ��
    LinkNode *next,*front; //��ǰ��һ�����
    /*
        ��ջ����ı�ͷ�� next��ʾջ�ף�front��ʾջ����
        �������г����������ֻ����������β��
    */
}LinkNode,*LinkList;
/*
    ���ݴ�1.txt����
*/
int create(LinkList* list);
int Read_Data(LinkList program);
int start(LinkList active_process,LinkList killed_process ,LinkList total_process,char *name);
int kill(LinkList killed_process,LinkList active_process,char *name);
//int restart(LinkList active_process,LinkList killed_process ,char *name);

int main()
{
    LinkList program = 0;//���������еĳ������ã�������txt�е����ݶ������
    //�����ݶ��뽫ʹ�ú�����
    LinkList active_process = 0;//˫������
    LinkList killed_process = 0;//����ջ ����Ϊ����Ҫ����ת�������Զ���˫������Ľ�㡣
    //��linklist* �Ƿ������free����Ϊ������������ڴ����������ǳ��������
    create(&program);//����,��ΪҪ�ı�programֵ���Դ�ָ��
    create(&active_process);
    create(&killed_process);
    Read_Data(program);//ʵ��Ϊlinklist*
    LinkList q;
    //��ʼ��ӡ����ʹ�õĽ���
    printf("����\t����id\t�ڴ�ʹ��(K)\n");
    for( q = program -> next ; q != program; q = q -> next)
    {
        printf("%s\t\t\t%d\t%f\n",q->Name_of_process,q ->PID ,q->ram_the_process_using);
    }
    int state = 1;
    printf("������ȫ������ִ��״̬\n");
    start(active_process,killed_process,program,"COD16");
    start(active_process,killed_process,program,"GTA5");
    start(active_process,killed_process,program,"VSCODE");
    start(active_process,killed_process,program,"QQ");
    printf("���ִ���н��̵�����\t����id\t����ʱ��(s)\t�ڴ�ʹ��(K)\n");
    int i = 1;
    for( q = active_process -> next ; q != active_process; q = q -> next)
    {
        printf("%s\t\t\t%d\t%d\t%f\n",q->Name_of_process,q ->PID,( - q ->start_time + time)  ,q->ram_the_process_using);
    }
    printf("���濪ʼ���벻���ڵ�:(name):(BILIBILI)\n");
    start(active_process,killed_process,program,"BILIBILI");
    printf("����kill GTA5 ��qq\n");
    kill(killed_process,active_process,"GTA5");
    kill(killed_process,active_process,"QQ");
    printf("���ִ���н��̵�����\t����id\t����ʱ��(s)\t�ڴ�ʹ��(K)\n");
    for( q = active_process -> next ; q != active_process; q = q -> next)
    {
        printf("%s\t\t\t%d\t%d\t0.2%f\n",q->Name_of_process,q ->PID,( - q ->start_time + time)  ,q->ram_the_process_using);
        //CLOCKS_PER_SECΪ�������һ���ʱ�䵥λ����time.h���Ѷ���
    }

    printf("����������̵�����\n");
    for( q = killed_process -> next ; q != killed_process; q = q -> next)
    {
        printf("%s\n",q->Name_of_process);
        //CLOCKS_PER_SECΪ�������һ���ʱ�䵥λ����time.h���Ѷ���
    }    

    printf("�������� GTA5\n");
    start(active_process,killed_process,program,"GTA5");
    time ++;
    printf("ִ���н��̵�����\t����id\t����ʱ��(s)\t�ڴ�ʹ��(K)\n");
    for( q = active_process -> next ; q != active_process; q = q -> next)
    {
        printf("%s\t\t\t%d\t%d\t%0.2f\n",q->Name_of_process,q ->PID,( - q ->start_time + time)  ,q->ram_the_process_using);
        //CLOCKS_PER_SECΪ�������һ���ʱ�䵥λ����time.h���Ѷ���
    }    
    printf("����������̵�����\n");
    for( q = killed_process -> next ; q != killed_process; q = q -> next)
    {
        printf("%s\n",q->Name_of_process);
        //CLOCKS_PER_SECΪ�������һ���ʱ�䵥λ����time.h���Ѷ���
    }    
    system("pause");
    return (0);
}


int start(LinkList active_process,LinkList killed_process,LinkList total_process,char *name)
/*
    ����total����process�ж�λname��name��Ҫ�����Ľ���ʱ�䣬
    Ȼ���������ʱ�䣬��¼
*/
{
    time ++;
    if(name == 0) 
    {
        printf("nameΪ��");
        return 0;
    }
    LinkList p = 0,q = 0,r = 0 , h = 0;
    int state = 0,state1 = 0;
    //��ʼ�ҵ�����Ϊname�Ľ���
    for(p = total_process -> next;p != total_process ;p = p -> next)
    {
        if(strcmp(p ->Name_of_process,name) == 0 )
        {
            //�ҵ�state��1������ѭ��
            state = 1;
            break;
        }
    }
    //Ȼ��ȷ���Ƿ��Ѿ�����
    for(q = active_process -> next ; q != active_process ;q = q -> next)
    {
        if(strcmp(q -> Name_of_process,name) == 0 )
        {
            //�ҵ�state��1����������
            printf("����������");
            return (-3);
        }
    }
    //Ȼ�󿴿��Ƿ���killed����
    for(h = killed_process -> next;h != killed_process ;h = h -> next)
    {
        if(strcmp(h ->Name_of_process,name) == 0 )
        {
            //�ҵ�state��1������ѭ��
            state1 = 1;
            break;
        }
    }
    if(state && !state1)
    //����killed��
    //�ҵ��ˣ����뵽active�У�
    {
        //���潫�ҵ��Ľ��̼��뵽active��
        //�����ƻ�total����process
        q = (LinkList )calloc(1, sizeof(LinkNode));
        //����p�е��е�����;
        q -> start_time = time;
        strcpy(q -> Name_of_process , p -> Name_of_process);
        q -> PID = p -> PID;
        q -> ram_the_process_using = p -> ram_the_process_using;
        //���濪ʼ��λ�ӵ�λ��
        for (p  = active_process; p -> next!= active_process ;p = p ->next)
        {
            if(q ->ram_the_process_using > p ->next ->ram_the_process_using)
            //ͨ���Ա��ڴ��ҵ�����λ��
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
    //��killed��
    {        
        //���潫�ҵ��Ľ��̼��뵽active��
        //�ƻ�killed
        //�Ƚ���Ͽ�,Ȼ��������
        h -> start_time = time ;
        r = h -> front;
        q = h -> next ;
        r -> next = q;
        q -> front = r;
        //���濪ʼ��λ�ӵ���
        //���濪ʼ��λ�ӵ�λ��
        q = h;
        for (p  = active_process; p -> next!= active_process ;p = p ->next)
        {
            if(q ->ram_the_process_using > p ->next ->ram_the_process_using)
            //ͨ���Ա��ڴ��ҵ�����λ��
            {
                break;
            }
        }
        //���뵽��
        r = p -> next;
        p -> next = q;
        q -> next = r;
        r -> front = q;
        q -> front = p;
        return (4);

    }
    else
    {
        printf("��Ч����\n");
        return (-3);
    }
}

/*
    ��start���
*/

int kill(LinkList killed_process,LinkList active_process,char *name)
{
    time ++ ;
    if(name == 0) 
    {
        printf("nameΪ��");
        return 0;
    }
    LinkList p = 0,q = 0,r = 0;
    int state = 0;
    //��ʼ�ҵ�����Ϊname�Ľ���
    for(p = active_process -> next;p != active_process ;p = p -> next)
    {
        if(strcmp(p ->Name_of_process,name) == 0 )
        {
            //�ҵ�state��1������ѭ��
            state = 1;
            break;
        }
    }
    //p�����Ѿ��ҵ��ý���
    //Ȼ��ȷ���Ƿ��Ѿ�kill
    for(q = killed_process -> next ; q != killed_process ;q = q -> next)
    {
        if(strcmp(q -> Name_of_process,name) == 0 )
        {
            //����Ѿ�kill��������
            printf("�������");
            return (-4);
        }
    }
    if(state)
    //�ҵ��ˣ����뵽kill�У�
    {
        //���潫�ҵ��Ľ��̼��뵽kill��
        //�ƻ�active
        //�Ƚ���Ͽ�
        r = p -> front;
        q = p -> next ;
        r -> next = q;
        q -> front = r;
        p -> start_time = 0;//ɱ��ʱ��Ϊ0
        //��p����kill�����ܴ�С
        q = killed_process -> next;
        p -> next = q;
        killed_process -> next = p;
        q -> front = p;
        p -> front = killed_process; 
        return (4);

    }
    else
    {
        printf("��Ч����\n");
        return (-4);
    }
}


int Read_Data(LinkList program)
/*
    ���ļ���������
    �ļ����ı��ļ���
    ����ֻ��һ���ļ�����ָ���ļ��������������ļ�������
    ���ʹ��system("tasklist  /fo  csv)���򳬹�200��̫�࣬���Լ򻯽���������Լ�д��csv
*/
{
    time ++ ;
    LinkList p = 0,q = 0;//������������
    FILE *file = 0;
    /*
        //�����ļ����ĳ���ֻ�������ﲻ��Ҫʹ�ã�����ע���
        //���Ҫʹ�ã�ֱ��ȥע��
        char mane_of_file[80];
        scan("%s",name_of_file);
    */
    file = fopen("1.txt","r+");
    if(!file)
    {
        printf("�ļ��򿪴���");
         exit(0);//������
    }
    p = program;
    while (!feof(file))
    {
        //��ȡ����
        char waste;        
        q = (LinkList ) calloc(1 , sizeof(LinkNode));
        fscanf(file,"%s %d %lf%c", q -> Name_of_process, &(q -> PID),&(q -> ram_the_process_using),&waste);
        q -> front = p;//����������������
        p -> next = q;
        p = p -> next;
        fseek(file,SEEK_CUR,4);
    }
    //���һ�����ݶ������������һ�����
    q = q -> front;//qΪ���һ��
    p = q -> next;
    q -> next = program;
    program -> front = q;
    free(p);
    fclose(file);
    return (2);
}


int create(LinkList* list)
//����,��ΪҪ�ı�listֵ���Զഫ��ָ��
{
    time ++;
    if((*list) != 0 ) free(*list);
    else
    {
        (*list)  = (LinkList ) calloc(1 , sizeof(LinkNode));
        (*list) -> next = (*list) -> front = (*list);
        //�����ͷ�ռ�
    }
    if(!list) exit(0);//��������˳�
    else
    { 
        //��Ϊͷ���ʹ���ڴ����
        (*list) -> ram_the_process_using =INT_MAX;
        return 1;//����
    }
}

