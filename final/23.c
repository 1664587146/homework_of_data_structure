/*
    23、【4】电子小字典（选做）（查找）
    [问题描述]
    利用键树结构，建立一个微型电子字典。
    [基本要求]
    实现生词的加入，单词的查找、删除，修改等操作。
*/

//键树结构：孩子兄弟树
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 200

typedef struct Words
{
    char Meaning[MAX];//意思
    char word[MAX];//对应的单词

}Words;
//words 只是接口里面可以加其他东西

typedef struct Key_Node
{
    char KeyValue;//这个节点的键
    int flag;//查看这个点的word是否激活，为后面删除准备
    Words word;
    Key_Node *child,*sibling;
}Key_Node,*Key_Tree;

Key_Tree Insert_And_Seach(Key_Tree *tree,Words word);
void Show_Info(Key_Tree tree);
int Delete_Word(Key_Tree *tree,Words word);
int change(Key_Tree *tree,Words word);
void menu();  

int main()
{
    int state = 1;
    int choice;
    Key_Tree *tree = 0;
    tree =(Key_Tree* ) calloc(1,sizeof(Key_Tree));
    while (state)
    {
        menu();
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
            {
                Words word;
                Key_Tree help;
                printf("请输入单词\n");
                scanf("%s",word.word);
                help = Insert_And_Seach(tree,word);
                if(help == 0)
                {
                    printf("已加入\n");
                }
                else
                {
                    Show_Info(help);
                }
                break;
            }
            
            case 2:
            {   
                Words word;
                printf("请输入单词\n");
                scanf("%s",word.word);
                change(tree,word);
                break;
            }

            case 3 :
            {
                Words word;
                printf("请输入单词\n");
                scanf("%s",word.word);
                Delete_Word(tree,word);                
                break;
            }

            case 4:
            {
                state = 0;
                break;
            }

            default:
            {   
                printf("输入错误，请重新输入\n");
                scanf("%d",&choice);
                break;
            }
        }
    }
    return 0;
}

void menu()  
{  
	printf("主菜单\n");  
	printf("1:查找单词\n");  
	printf("2:修改单词\n");  
	printf("3:删除单词\n");
    printf("4:结束程序\n");
}  


Key_Tree Insert_And_Seach(Key_Tree *tree,Words word)
//查找，插入键树
//包括创建
//查找后没有打印信息，打印信息在下面
{
    if(*tree == 0 )
    //是棵空树
    {
        int key_position = 0;
        //key的位置 nuaa为例 key为n是 key_position = 0；
        Key_Tree help_point1,help_point2;//辅助指针
        *tree = (Key_Tree)calloc(1,sizeof(Key_Node));
        if(*tree)
        {
            (*tree) -> KeyValue = word.word[0];//加入键值
            help_point1 = help_point2 = *tree;
            if(key_position + 1== strlen(word.word))
            //如果word的关键字都加入
            {
                printf("原单词本里没有这个单词\n");
                help_point2 -> flag = 1;//激活tree的words
                //将word赋值到words内
                strcpy( help_point2 ->word.word ,word.word);
                printf("请输入意思\n");
                scanf("%s",help_point2 ->word.Meaning);
                return(0);
            }
            else
            {
                help_point1 = *tree;
                while (key_position < strlen(word.word))
                //将整个单词的key加入
                {
                    help_point2 = (Key_Tree)calloc(1,sizeof(Key_Node));
                    if(help_point2)
                    {
                        help_point1 -> child = help_point2;
                        key_position ++;
                        help_point2 -> KeyValue = word.word[key_position];
                        if(key_position + 1== strlen(word.word))
                        //如果word的关键字都加入
                        {
                            printf("原单词本里没有这个单词\n");
                            help_point2 -> flag = 1;//激活tree的words
                            //将word赋值到words内
                            strcpy( help_point2 ->word.word ,word.word);
                            printf("请输入意思\n");
                            scanf("%s",help_point2 ->word.Meaning);
                            return ( 0 );
                        }
                        else
                        {
                            help_point1 = help_point1 -> child;//继续加入
                        }
                        
                    }
                }
            }
        }
    }
    else
    //如果不是空树
    { 
        int key_position = 0;
        //key的位置 nuaa为例 key为n是 key_position = 0；
        Key_Tree help_point1,help_point2;//辅助指针
        help_point1 = *tree;//help_point1 ->赋值
        while (key_position < strlen(word.word))
        //开始查找或者加入
        {
            while ( help_point1 -> KeyValue != word.word[key_position] && help_point1 ->sibling != 0 )
            {
                help_point1 = help_point1 ->sibling;//同层兄弟不同keyvalue的查找
                if (help_point1 -> KeyValue == word.word[key_position])
                {
                    break;
                }
            }
            //如果直接找到
            if(key_position + 1 == strlen(word.word) && help_point1 -> KeyValue == word.word[key_position])
            {
                
                if(help_point1 ->flag == 0)//删除以后再加入
                {
                    printf("原单词本里没有这个单词\n");
                    help_point1 -> flag = 1;//激活tree的words
                    //将word赋值到words内
                    strcpy( help_point1 ->word.word ,word.word);
                    printf("请输入意思\n");
                    scanf("%s",help_point1 ->word.Meaning);
                    return (0);
                }
                else
                {
                    return(help_point1);
                }
            }
            if (help_point1 -> KeyValue == word.word[key_position])
            //如果有到孩子里面找
            {
                if(help_point1 -> child )
                //如果有孩子
                {
                    key_position ++;
                    help_point1 = help_point1 -> child;
                    //找到
                    if(key_position + 1 == strlen(word.word))
                    {
                        
                        if(help_point1 ->flag == 0)//删除以后再加入
                        {
                            printf("原单词本里没有这个单词\n");
                            help_point1 -> flag = 1;//激活tree的words
                            //将word赋值到words内
                            strcpy( help_point1 ->word.word ,word.word);
                            printf("请输入意思\n");
                            scanf("%s",help_point1 ->word.Meaning);
                            return (0);
                        }
                        else
                        {
                            return(help_point1);
                        }
                    }
                }
                else
                //没有开始添加，和前面类似
                {
                    while (key_position  < strlen(word.word))
                    //将整个单词剩余key加入
                    {
                        help_point2 = (Key_Tree)calloc(1,sizeof(Key_Node));
                        if(help_point2)
                        {
                            help_point1 -> child = help_point2;
                            help_point2 -> KeyValue = word.word[key_position];
                            key_position ++;
                            if(key_position + 1 == strlen(word.word))
                            //如果word的关键字都加入
                            {
                                printf("原单词本里没有这个单词\n");
                                help_point2 -> flag = 1;//激活tree的words
                                //将word赋值到words内
                                strcpy( help_point2 ->word.word ,word.word);
                                printf("请输入意思\n");
                                scanf("%s",help_point2 ->word.Meaning);
                                return (0);
                            }
                            else
                            {
                                help_point1 = help_point1 -> child;//继续加入
                            }
                        }
                    }
                    return(0);
                }
            }

            else
            //没有则 开始加入操作
            //同时一定也没有孩子
            {
                help_point2 = (Key_Tree)calloc(1,sizeof(Key_Node));
                if(help_point2)
                {
                    help_point1 -> sibling = help_point2;
                    help_point2 -> KeyValue = word.word[key_position];
                    key_position ++;
                    if(key_position == strlen(word.word))
                    //如果word的关键字都加入
                    {
                        printf("原单词本里没有这个单词\n");
                        help_point2 -> flag = 1;//激活tree的words
                        //将word赋值到words内
                        strcpy( help_point2 ->word.word ,word.word);
                        printf("请输入意思\n");
                        scanf("%s",help_point2 ->word.Meaning);
                        return (0);
                    }
                    help_point1 = help_point1 -> sibling;
                }
                while (key_position < strlen(word.word))
                //将整个单词剩余key加入
                {
                    help_point2 = (Key_Tree)calloc(1,sizeof(Key_Node));
                    if(help_point2)
                    {
                        help_point1 -> child = help_point2;
                        help_point2 -> KeyValue = word.word[key_position];
                        key_position ++;
                        if(key_position  == strlen(word.word))
                        //如果word的关键字都加入
                        {
                            printf("原单词本里没有这个单词\n");
                            help_point2 -> flag = 1;//激活tree的words
                            //将word赋值到words内
                            strcpy( help_point2 ->word.word ,word.word);
                            printf("请输入意思\n");
                            scanf("%s",help_point2 ->word.Meaning);
                            return (0);
                        }
                        else
                        {
                            help_point1 = help_point1 -> child;//继续加入
                        }
                    }
                }
            }
        }
        //这个时候找到了在，返回所在节点
    }
}

void Show_Info(Key_Tree tree)
//因为是和其他组合使用所有没有tree的输入检查
{        
    if(tree -> flag )
    {            
        printf("当前信息如下\n");
        printf("%s的意思：%s\n",tree -> word.word,tree ->word .Meaning);
    }
    else
    {
        printf("当前节点无信息\n");        
    }
    
}

int Delete_Word(Key_Tree *tree,Words word)
//首先要保证有（用户确定，因为没有自动加入再删除，没什么意思,但函数会考虑
//主要算法隐删除
{
    Key_Tree help;
    if(help = Insert_And_Seach(tree,word))
        help -> flag = 0;
    else
    {
        help = Insert_And_Seach(tree,word);
        help -> flag = 0;
    }
    return (1);
}

int change(Key_Tree *tree,Words word)
//首先要保证有（用户确定，因为没有自动加入再修改，没什么意思
//主要算法直接修改
{
    Key_Tree help;
    help = Insert_And_Seach(tree,word);
    Show_Info(help);
    printf("是否修改\n1：是\n2:不是\n");
    int choice;
    scanf("%d" , &choice);
    if (choice == 1)
    {
        printf("请输入意思\n");
        scanf("%s",help ->word.Meaning);
        return (3);
    }
    if (choice == 2)
    {
        return (3);
    }
}

