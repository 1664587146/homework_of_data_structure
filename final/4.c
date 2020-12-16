/*
    [问题描述]
    实现具有下列功能的家谱管理系统。
    [基本要求]
    （1）输入文件以存放最初家谱中各成员的信息，成员的信息中均应包含以下内容：
        姓名、出生日期、婚否、地址、健在否、死亡日期（若其已死亡），
        也可附加其它信息、但不是必需的。
    （2）实现数据的文件存储和读取。
    （3）以图形方式显示家谱。
    （4）显示第n 代所有人的信息。
    （5）按照姓名查询，输出成员信息（包括其本人、父亲、孩子的信息）。
    （6）按照出生日期查询成员名单。
    （7）输入两人姓名，确定其关系。
    （8）某成员添加孩子。
    （9）删除某成员（若其还有后代，则一并删除）。
    （10）修改某成员信息。
    （11）要求建立至少20个成员的数据，以较为直观的方式显示结果，并提供文稿形式以便检查。
    （12）界面要求：有合理的提示，每个功能可以设立菜单，根据提示，可以完成相关的功能要求。
    （13）存储结构：根据系统功能要求自行设计，但是要求相关数据要存储在数据文件中。
    测试数据：要求使用1、全部合法数据；
    2、局部非法数据。进行程序测试，以保证程序的稳定。
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//文件类型：文本文件
//数据结构：孩子兄弟树
typedef struct Person
{
    char name[20];
    //名字
    int birthday[3];
    /* 
        birthday[0] 年
        birthday[1] 月
        birthday[2] 日
    */
    int marriage;
    /*
        婚否 marriage = 1；结婚
            marriage = 0未婚
    */
    char name_of_mate[20];
    //配偶的名字
    char address[20];
    int generation;
    //第几代
    int alive;
    /*
        健在否 alive = 1；健在
        alive = 0 去世
    */
    int death_date[3];
    //各个数的含义和birthday一样
    //如果健在则各个数据为零
    int flag_self;
    //表示这个节点是否有用，flag_self表示有效
    //辅助删除的
    int flag_sibling,flag_child;
    /*
        帮助判断是否有孩子和兄弟
        flag==1 有
        这里最好是bool，but c没有bool 所以用int
    */
    Person *sibling,*child,*father;
    //上面是家谱意义上的
    Person *parent;
    //parent是这个节点的父节点
}Person,*Family;

//文件的存储是以树的先序遍历存储树
//所以读取也是先序遍历
//有合法性检验，主要针对日期
//这里没有写成双向
int Read_Data(Family *family , FILE *file_r)
{
    if(feof(file_r))
    {
        //文件读完
        return (-1);
    }
    else
    {
        (*family) = (Person *)calloc(1, sizeof(Person));
        //读姓名
        fscanf(file_r,"%s",(*family) -> name);
        //读出生日期
        fscanf(file_r," %d %d %d",&((*family)-> birthday[0]) , &((*family) -> birthday[1]) , &((*family) -> birthday[2]));
        //[1][2]要大于零
        if(!((*family) ->birthday[1] > 0 && (*family) ->birthday[1] <= 12) || !((*family) ->birthday[2] > 0 && (*family) ->birthday[2] <= 31))
        {
            printf("出身日期错误 \n");
            system("pause");
            exit(0);
        }
        //读是否结婚
        fscanf(file_r,"%d",&((*family) -> marriage) );
        if((*family) -> marriage )
        {
            fscanf(file_r,"%s",(*family) -> name_of_mate);
        }
        //读地址
        fscanf(file_r,"%s",(*family) -> address);
        //读是家族第几代
        fscanf(file_r,"%d",&((*family) -> generation));
        if((*family) ->generation <= 0)
        {
            printf("辈分出现小于等于0 \n");
            exit(0);
        }        
        //读是否健在
        fscanf(file_r,"%d",&((*family) -> alive));
        if((*family) -> alive == 0)
        {
            fscanf(file_r,"%d %d %d",&((*family) -> death_date[0]) , &((*family) -> death_date[1]) , &((*family) -> death_date[2]));
        }
        if(!((*family) ->death_date[1] > 0 && (*family) ->death_date[1] <= 12) || !((*family) ->death_date[2] > 0 && (*family) -> death_date[2] <= 31))
        {
            printf("死亡日期错误 \n");
            exit(0);
        }
        //flag_self 能读自动有效
        (*family) -> flag_self = 1;
        fscanf(file_r,"%d",&((*family) -> flag_child));
        fscanf(file_r,"%d",&((*family) -> flag_sibling));
        if((*family) -> flag_child)
        {
            Read_Data(&((*family) -> child),file_r);
        }
        if((*family) -> flag_sibling)
        {
            Read_Data(&((*family) -> sibling),file_r);
        }
        return (1);
    }
}

int Make_The_Tree_Complete(Family family)
{
    if(!family)
    {
        return (-2);
    }
    if(family -> flag_child)
    {
        family -> child -> father = family;
        family -> child -> parent = family;
        Make_The_Tree_Complete(family -> child);
    }
    if(family -> flag_sibling)
    {
        family -> sibling -> father = family -> father;
        family -> sibling -> parent = family;
        Make_The_Tree_Complete(family -> sibling);

    }
    return (2);
}

int Save_Data(Family family , FILE *file_w)
//存节点
//相当于read反向
{
    if(!family)
    {
        return (-3);
    }
    if(family -> flag_self )
    {
        //存姓名
        fprintf(file_w,"%s",family -> name);
        //存出生日期
        fprintf(file_w," %d %d %d",family -> birthday[0] , family -> birthday[1] , family -> birthday[2]);
        fprintf(file_w," ");
        //存是否结婚
        fprintf(file_w,"%d",family -> marriage );
        fprintf(file_w," ");
        if(family -> marriage )
        {
            fprintf(file_w,"%s",family -> name_of_mate);
            fprintf(file_w," ");
        }
        //存地址
        fprintf(file_w,"%s",family -> address);
        fprintf(file_w," ");
        //存是家族第几代
        fprintf(file_w,"%d",family -> generation);
        fprintf(file_w," ");
        //存是否健在
        fprintf(file_w,"%d",family -> alive);
        fprintf(file_w," ");
        if(family -> alive == 0)
        {
            fprintf(file_w," %d %d %d",family -> death_date[0] , family -> death_date[1] , family -> death_date[2]);
            fprintf(file_w," ");
        }
        fprintf(file_w,"%d",family -> flag_child);
        fprintf(file_w," ");
        fprintf(file_w,"%d",family -> flag_sibling);
        fprintf(file_w,"\n");
        //flag_self 能读自动有效
        if(family -> flag_child)
        {
            Save_Data(family -> child,file_w);
        }
        if(family -> sibling)
        {
            Save_Data(family -> sibling,file_w);
        }
    }
    else
    {
        if(family -> flag_sibling)
        {
            Save_Data(family -> sibling,file_w);
        }
    }
    return (3);
}

//（3）不写图形界面，因为c图形界面不会写，qt只支持cpp
void Show_Information(Family family)
//先序魔改
{
    if(!family)
    {
        return ;
    }
    if(family -> flag_self)
    //下面开始输出信息
    {        
        printf("名字：%s\n",family -> name);
        printf("出生日期：%d年 %d月 %d日\n",family -> birthday[0] , family -> birthday[1] , family -> birthday[2]);
        if(family -> marriage )
        {
            printf("已婚 配偶名%s\n",family -> name_of_mate);
        }
        else
            printf("未婚\n");
        //存地址
        printf("第%d代\n",family -> generation);
        printf("家庭地址%s\n",family -> address);
        if(family -> alive == 0)
        {
            printf("已去世，去世时间是 %d年 %d月 %d日\n",family -> death_date[0] , family -> death_date[1] , family -> death_date[2]);
            printf("\n");
        }
        else
        {
            printf("\n");
        }
        if(family -> flag_sibling)
        {
            Show_Information(family -> sibling );
        }
        if(family -> flag_child)
        {
            Show_Information(family -> child );
        }
    }
    else
    {
        if(family -> flag_sibling)
        {
            Show_Information(family ->sibling);           
        }
    }
}//如果有返回4，如果没有返回-4

int Show_Information_By_Generation(Family family , int generation)
//先序魔改
{
    int i = -4;
    if(!family)
    {
        return (-4);
    }
    if(generation < 0)
    {
        printf("辈分不对\n");
        return(-101);
    }
    if(family -> generation == generation && family -> flag_self)
    //下面开始输出信息
    {        
        printf("名字：%s\n",family -> name);
        printf("出生日期：%d年 %d月 %d日\n",family -> birthday[0] , family -> birthday[1] , family -> birthday[2]);
        if(family -> marriage )
        {
            printf("已婚 配偶名%s\n",family -> name_of_mate);
        }
        else
            printf("未婚\n");
        //存地址
        printf("家庭地址%s\n",family -> address);
        if(family -> alive == 0)
        {
            printf("已去世，去世时间是 %d年 %d月 %d日\n",family -> death_date[0] , family -> death_date[1] , family -> death_date[2]);
            printf("\n");
        }
        else
        {
            printf("\n");
        }
        if(family -> flag_sibling)
        {
            Show_Information_By_Generation(family ->sibling ,generation);
        }//同一只孩子辈分一定比父辈数字上大
        i = 4;
    }
    else
    {
        if(!family -> flag_self)
        {
            if(family -> flag_sibling)
            {
                i = Show_Information_By_Generation(family ->sibling ,generation);
            }            
        }
        if(family -> generation <= generation)
        //辈分数字更大的没必要查
        {
            if(family ->flag_child)
            {
                i = Show_Information_By_Generation(family ->child,generation);
            }
            if(family -> flag_sibling)
            {
                i = Show_Information_By_Generation(family ->sibling ,generation);
            }
        }
    }
    return (i);
}//如果有返回4，如果没有返回-4

int Information_Inquiry_By_Name(Family family)
{
    printf("名字：%s\n",family -> name);
    printf("出生日期：%d年 %d月 %d日\n",family -> birthday[0] , family -> birthday[1] , family -> birthday[2]);
    if(family -> marriage )
    {
        printf("已婚 配偶名%s\n",family -> name_of_mate);
    }
    else
        printf("未婚\n");
    //存地址
    printf("第%d代\n",family -> generation);
    printf("家庭地址%s\n",family -> address);
    if(family -> alive == 0)
    {
        printf("已去世，去世时间是 %d年 %d月 %d日\n",family -> death_date[0] , family -> death_date[1] , family -> death_date[2]);
    }
    printf("\n");
}

int Inquiry_By_Name(Family family,char *name)
//前序的魔改
{    
    int i = -5;
    if(!family)
    {
        return (-5);
    }
    if(!name)
    {
        printf("名字为空\n");
        return (-102);
    }
    if(strcmp(family -> name, name ) == 0 && family ->flag_self)
    //下面开始输出信息
    {        
        printf("父亲:\n");
        Information_Inquiry_By_Name(family -> father);
        printf("自己:\n");
        Information_Inquiry_By_Name(family);
        Family point;
        printf("孩子\n");
        if(family -> flag_child)
        {
            point = family -> child;
            for (  ; point ;)
            {
                if(point -> flag_self)
                {
                    Information_Inquiry_By_Name(point);
                    if(point -> flag_sibling)
                    {
                        point = point -> sibling;
                    }
                    else
                    {
                        break;
                    }
                    
                }
            }
        }
        i = 5;
    }
    else
    {
        if(family ->flag_child)
        {
            i = Inquiry_By_Name(family -> child ,name);
        }
        if(family -> flag_sibling)
        {
            i = Inquiry_By_Name(family -> sibling,name);
        }
    }
    return (i);
}
//i = 5找到 i= -5没有这个人

int Inquiry_By_Birthday(Family family,int *birthday)
//和前面的姓名差不多
{
    int i = -6;
    if(!family)
    {
        return (-6);
    }
    if(!birthday)
    {
        printf("生日输入为空\n");
        return (-103);
    }
    if(family -> flag_self)
    {
        if(family ->birthday[0] == birthday[0] && family ->birthday[1] == birthday[1] && family ->birthday[1] == birthday[1] )
        {
            printf("名字：%s\n",family -> name);
            printf("出生日期：%d年 %d月 %d日\n",family -> birthday[0] , family -> birthday[1] , family -> birthday[2]);
            if(family -> marriage )
            {
                printf("已婚 配偶名%s\n",family -> name_of_mate);
            }
            else
                printf("未婚\n");
            //存地址
            printf("第%d代\n",family -> generation);
            printf("家庭地址%s\n",family -> address);
            if(family -> alive == 0)
            {
                printf("已去世，去世时间是 %d年 %d月 %d日\n",family -> death_date[0] , family -> death_date[1] , family -> death_date[2]);
            }
            printf("\n");
            i = 6;            
        }
        else
        {
            if(family ->flag_child)
            {
                i = Inquiry_By_Birthday(family -> child ,birthday);
            }
            if(family -> flag_sibling)
            {
                i = Inquiry_By_Birthday(family -> sibling,birthday);
            }
        }
    }
    else
    {
        if(family -> flag_sibling)
            i = Inquiry_By_Birthday(family ->sibling,birthday);
    }
     return(i);
}
//

int Define_Generation(Family family,char *name)
{
    int i = -7;
    if(!family)
    {
        return (-7);
    }
    if(!name)
    {
        printf("名字为空\n");
        return (-104);
    }
    if(strcmp(family -> name , name ) == 0)
    //下面开始输出信息
    {        
        i = family -> generation;
        return (i);
    }
    else
    {
        if(family ->flag_child)
        {
            i = Define_Generation(family -> child ,name);
            if(i != -7 && i != 0)
            {
                return (i);
            }
        }
        if(family -> flag_sibling)
        {
            i = Define_Generation(family -> sibling,name);
            if(i != -7  && i != 0)
            {
                return (i);
            }
        }
    }
}

int Define_Relationship(Family family,char *name1,char *name2)
/*
    函数说明，这里只是确定辈分，如果按叔伯这种太绕了，主要是我自己也不清楚、
*/
{
    if( !name1 || !name2 )
    {
        printf("名字错误\n");
        return (-105);
    }
    int generation1,generation2;
    //这里开始确定辈分
    Family point1 = family,point2 = family;
    generation1 = Define_Generation(point1,name1);
    generation2 = Define_Generation(point2,name2);
    //generation == -7表示家谱里没有这个人
    if(generation1 == - 7 )
    {
        printf("没有%s\n",name1);
        return (-107);
    }
    if(generation2 == - 7 )
    {
        printf("没有%s\n",name2);
        return(-107);
    }
    if (generation1 < generation2)
    {
        //通常情况下 辈分数值小的年纪大
        printf("%s是%s的长辈，年长%d辈\n",name1,name2,generation2 - generation1);
    }
    else if(generation1 == generation2)
    {
        printf("%s与%s是同辈\n",name1,name2);
    }
    else if(generation1 > generation2)
    {
        printf("%s是%s的长辈，年长%d辈\n",name2,name1,generation1 - generation2);
    }
    return (8);
}

Family locate(Family family,char *name)
//前序的魔改
{   
    Family point = 0;
    if( strcmp(family -> name, name ) == 0)
    //下面开始输出信息
    {    
        point = family;
        return(point);    
    }
    else
    {
        if(family -> flag_child)
        {
            point = locate(family -> child ,name);
            if (point)
            {
                return(point);    
            }
        }
        if(family -> flag_sibling)
        {
            point = locate(family -> sibling ,name);
            if (point)
            {
                return(point);    
            }
        }
    }
}

int Add_child(Family family,char *name_parent)
/*
    先要定位要加孩子的成员
*/
{
    if(!family)
    {
        return (-8);
    }
    if(!name_parent)
    {
        printf("名字为空\n");
        return (-106);
    }
    Person *add;//要加的孩子的人
    add = locate(family,name_parent);//locate用前面的inquiry改
    Person *adds_child, *point;
    adds_child =(Person *)calloc(1,sizeof(Person));
    //
    if(add -> flag_child)
    {    point = add -> child;
        //加到兄弟链的最后面
        //即add -> child的最左子树后面//8
        for ( ; point -> sibling; point = point -> sibling) ;
        point -> flag_sibling = 1;
        point -> sibling = adds_child;
        adds_child -> parent = point;
        adds_child -> father = add;
    }
    else
    {
        add -> child = adds_child ;
        add -> flag_child = 1;
        adds_child -> parent = add;
        adds_child -> father = add;
    }
    //现在已经找到,下面开始填写信息
    //读姓名
    printf("name:\n");
    scanf("%s",adds_child -> name);
    //读出生日期
    printf("birthday:\n");
    scanf("%d %d %d",&(adds_child -> birthday[0]) , & (adds_child -> birthday[1]) ,& (adds_child -> birthday[2]));
    //[1][2]要大于零
    if(!(adds_child ->birthday[1] > 0 && adds_child ->birthday[1] <= 12) || !(adds_child ->birthday[2] > 0 && adds_child ->birthday[2] <= 31))
    {
        printf("出生日期错误 \n");
        exit(0);
    }
    //读是否结婚
    printf("if marry \n");
    scanf("%d",&(adds_child -> marriage) );
    if(adds_child -> marriage )
    {
        printf("name of mate\n");
        scanf("%s",adds_child -> name_of_mate);
    }
    //读地址
    printf("address:\n");
    scanf("%s",adds_child -> address);
    //读是家族第几代
    printf("generation:\n");
    scanf("%d",&(adds_child -> generation));
    if(adds_child ->generation <= 0)
    {
        printf("辈分出现小于等于0 \n");
        exit(0);
    }        
    //读是否健在
    printf("alive:\n");
    scanf("%d",&(adds_child -> alive));
    if(adds_child -> alive == 0)
    {
        printf("death_date :\n");
        scanf("%d %d %d",&(adds_child -> death_date[0]) , &(adds_child -> death_date[1]) , &(adds_child -> death_date[2]));
        if(!(adds_child ->death_date[1] > 0 && adds_child ->death_date[1] <= 12) || !(adds_child ->death_date[2] > 0 && adds_child -> death_date[2] <= 31))
        {
            printf("死亡日期错误 \n");
            exit(0);
        }
    }
    //flag_self 能读自动有效
    adds_child -> flag_self = 1;
    //默认没有孩子;
    return (1);
}

void menu_change()
{
    printf("***********************\n");
    printf("请输入你要修改内容的序号\n");
    printf("1:姓名\n");
    printf("2:出生日期\n");
    printf("3:婚姻情况\n");
    printf("4:地址\n");
    printf("5:辈分\n");
    printf("6:是否健在\n");
    printf("7:是否删除这个节点\n");
    printf("***********************\n");
}

int Change_Infomation(Family family,char* name)
{
    Person *change;
    //定位个人
    change = locate(family , name);
    menu_change();
    int i;
    scanf("%d",&i);
    switch (i)
    {
        case 1: 
        {    
            printf("当前姓名是\n");
            printf("请输入改后的姓名\n");
            scanf("%s",change ->name);
            break;
        }

        case 2:
        {
            printf("当前出生日期：%d年 %d月 %d日\n",change -> birthday[0] , change -> birthday[1] , change -> birthday[2]);
            printf("请输入改后出生日期:\n");
            scanf("%d %d %d",&(change -> birthday[0]),&(change -> birthday[1]),&(change -> birthday [2]));
            while(!(change ->birthday[1] > 0 && change ->birthday[1] <= 12) || !( change ->birthday[2] > 0 && change ->birthday[2] <= 31))
            {
                printf("出日期错误,请重新输入\n");
                scanf("%d %d %d",&(change -> birthday[0]),&(change -> birthday[1]),&(change -> birthday [2]));    
            }
            break ;
        }

        case 3:
        {   
            if(change -> marriage )
            {
                printf("已婚 配偶名%s\n",change -> name_of_mate);
            }
            else
                printf("未婚\n");
            printf("请输入现在的婚姻状况\n");
            scanf("%d",&(change -> marriage));   
            if(change -> marriage )
            {
                printf("请输入配偶姓名\n");
                scanf("%s",change -> name_of_mate);
            }
            break;
        }

        case 4:
        {
            printf("当前地址：%d\n",change -> address);
            printf("请输入改变后的地址：\n");
            scanf("%s",change -> address);
            break;
        }
        
        case 5:
        {
            printf("现在的辈分：%d\n",change -> generation);
            printf("请输入改后的辈分\n");
            scanf("%d",&(change -> generation));
            break;
        }

        case 6:
        {   
            if(change -> alive )
            {
                printf("健在 配偶名%s\n");
            }
            else
                printf("当前去世日期：%d年 %d月 %d日\n",&(change -> death_date[0]) , &(change -> death_date[1]) , &(change -> death_date[2]));
            printf("请输入改后的是否健在:\n");
            scanf("%d",&(change -> alive));
            if(! change -> alive)
            {
                scanf("%d %d %d",&(change -> death_date[0]),&(change -> death_date[1]),&(change -> death_date [2]));
                while(!(change ->death_date[1] > 0 && change ->death_date[1] <= 12) || !( change ->death_date[2] > 0 && change ->death_date[2] <= 31))
                {
                    printf("出日期错误,请重新输入\n");
                    scanf("%d %d %d",&(change -> death_date[0]),&(change -> death_date[1]),&(change -> death_date [2]));    
                }
            }
            break;
        }

        case 7 :
        {
            change -> flag_self = 0;
            break;
        }

        default:
        {
            printf("I数值错误，重新输入\n");
            scanf("%d",&i);
            break;
        }
    }
}

//主函数的menu
void menu_main()
{
	//显示菜单栏
	printf("************************************\n");
	printf("1. 显示家谱\n");
	printf("2. 显示第n代所有人的信息\n");
	printf("3. 姓名查询，输出成员信息(本人、父亲、孩子)\n");
	printf("4. 按照出生日期查询成员名单\n");
	printf("5. 输入两人姓名确定其关系\n");
	printf("6. 某成员添加孩子\n");
	printf("7. 删除某成员（若其还有后代，则一并删除）\n");
	printf("8. 修改某成员信息\n");
	printf("9. 数据的文件存储\n");
	printf("10. 退出程序,并存储\n");
	printf("************************************\n");
}

int   Distroy(Family family)
{
    if(!family)
        return (0);
    else
    {
        Distroy(family ->child);
        Distroy(family -> sibling);
        free(family);
        return (0);
    }
    
}

int main()
{
    Family family_tree = 0;
    FILE *file = fopen("family.txt","r");
    Read_Data(&family_tree,file);
    Make_The_Tree_Complete(family_tree);
    fclose(file);
    //读完关闭
    int choice;
    while(1)
    {
        menu_main();
        printf("请输入选择\n");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1 :
                {
                    Show_Information(family_tree);
                    break;
                }

            case 2 :
                {
                    int generation;
                    printf("请输入要查询的辈数\n");
                    scanf("%d",&generation);
                    Show_Information_By_Generation(family_tree,generation);
                    break;
                }

            case 3 :
                {
                    char name[20];
                    printf("请输入要查询的名字\n");
                    scanf("%s",name);
                    if( -5 == Inquiry_By_Name(family_tree,name))
                    {
                        printf("查无此人");
                    }
                    break;
                }

            case 4 :
                {
                    int birthday[3];
                    printf("请输入要查询的生日\n");
                    scanf("%d%d%d",&(birthday[0]),&(birthday[1]),&(birthday[2]));
                    if( -6 == Inquiry_By_Birthday(family_tree,birthday))
                    {
                        printf("查无此人");
                    }            
                    break;
                }

            case 5 :
                {            
                    char name1[20],name2[20];
                    printf("请输入要查询的名字\n");
                    scanf("%s",name1);
                    scanf("%s",name2);
                    Define_Relationship(family_tree,name1,name2);
                    break;
                }

            case 6 :
                {
                    char name1[20];
                    printf("请输入要添加孩子的名字\n");
                    scanf("%s",name1);
                    Add_child(family_tree,name1);
                }            
                    break;

            case 7 :
                {
                    Family del;
                    char name1[20];
                    printf("请输入要删除的名字\n");
                    scanf("%s",name1);
                    del = locate(family_tree,name1);
                    del -> flag_self = 0;
                    //隐性删除
                    break;
                }
            case 8 :
                {
                    Family del;
                    char name1[20];
                    printf("请输入要修改的名字\n");
                    scanf("%s",name1);
                    Change_Infomation(family_tree,name1);
                    break;
                }

            case 9 :
                {
                    file = fopen("family_save.txt","w");
                    Save_Data(family_tree,file);
                    fclose(file);
                    break;
                }

            case 10 :
                {
                    file = fopen("family_save.txt","w");
                    Save_Data(family_tree,file);
                    fclose(file);
                    Distroy(family_tree);
                    return (0);
                }
            default:
            {
                printf("输入错误，请重新输入");
                scanf("%d",&choice);
                break;
            }
        }
    }
    system("pause");
    return (0);
}

