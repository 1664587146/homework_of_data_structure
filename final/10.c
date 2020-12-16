/*
    10、【1】 朋友圈（选做）（集合的等价关系）
    [问题描述]
    某学校有N个学生，形成M个俱乐部。每个俱乐部里的学生有着相似的兴趣爱好，形成一个朋友圈。
    一个学生可以同时属于若干个不同的俱乐部。根据“我的朋友的朋友也是我的朋友”这个推论可以得出，
    如果A和B是朋友，且B和C是朋友，则A和C也是朋友。请编写程序计算最大朋友圈中有多少人。 
    [基本要求]
    （1）输入说明：输入的第一行包含两个正整数N (N<=30 000)和M (M<=1000)，
    分别代表学校的学生总数和俱乐部的个数。随后的M行每行按以下格式给出一个俱乐部的信息，
    其中学生从1-N编号：
    第i个俱乐部的人数Mi（空格）学生1（空格）学生2… 学生Mi 
    （2）输出说明：输出一个整数，表示在最大朋友圈中有多少人。
    （3）测试用例： 
    输入  7 4
        3 1 2 3
        2 1 4
        3 5 6 7
        1 6 
  输出  4
*/
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int number_club,number_student;
    //输入学生数和俱乐部数
    scanf("%d%d",&number_student,&number_club);
    int i,count_of_club_members,j,k,l;
    int *student;
    student = (int *)calloc( number_student  + 1, sizeof(int ));
    int help,help1, max = 0;
    for ( i = 1; i <= number_club; i++)
    {
        int state = 1;
        help1 = help = 0;
        scanf("%d",&count_of_club_members);
        for ( j = 0; j < count_of_club_members ; j++)
        {
            if(state)
            //如果前面没有输入到重复元素，即前面的都不认识
            {
                scanf("%d",&k);
                //学生k第一次出现
                if (student[k] == 0)
                //
                {
                    student[k] = i;//说明是第几个club；
                    continue;
                }
                else
                {
                    help = student[k];
                    //将前面的student == i都改成help                    
                    for ( l = 1 ; l <= number_student ; l++)
                    {
                        if(student[l] == i)
                        {
                            student[l] = help;
                        }
                    }
                    state = 0;
                    continue;
                }
            }
            else
            //已经有了相重复的
            {   
                scanf("%d",&k);

                if (student[k] == 0 || student[k] == help)
                {
                    student[k] = help ;
                }
                else
                {
                    //这是第二个重复
                    help1 = student[k];
                    //将前面的student == i都改成student = help1      
                    for ( l = 1 ; l <= number_student ; l++)
                    {
                        if(student[l] == i || student[l] == help  )
                        {
                            student[l] = help1;
                        }
                    }
                    help = help1;
                }
            }
        }
    }
    int *max_number;
    max_number = (int *)calloc(number_club + 1, sizeof(int));
    //下面开始计算最大朋友圈
    for ( j = 1; j <= number_student; j++)
    {
        max_number[student[j]]++;
    }
    for ( i = 1; i <= number_club; i++)
    {    if(max_number[max] < max_number[i])
        {
            max = i;
        }
    }        
    printf("%d\n",max_number[max]);
    printf("分别是:");
    for ( i = 1; i <= number_student; i++)
    {    if(student[i] == max)
        {
            printf("%d ",i);
        }
    } 
    printf("\n");
    free(max_number);
    free(student);
    system("pause");
    return 0;
}