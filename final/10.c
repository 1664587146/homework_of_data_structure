/*
    10����1�� ����Ȧ��ѡ���������ϵĵȼ۹�ϵ��
    [��������]
    ĳѧУ��N��ѧ�����γ�M�����ֲ���ÿ�����ֲ����ѧ���������Ƶ���Ȥ���ã��γ�һ������Ȧ��
    һ��ѧ������ͬʱ�������ɸ���ͬ�ľ��ֲ������ݡ��ҵ����ѵ�����Ҳ���ҵ����ѡ�������ۿ��Եó���
    ���A��B�����ѣ���B��C�����ѣ���A��CҲ�����ѡ����д��������������Ȧ���ж����ˡ� 
    [����Ҫ��]
    ��1������˵��������ĵ�һ�а�������������N (N<=30 000)��M (M<=1000)��
    �ֱ����ѧУ��ѧ�������;��ֲ��ĸ���������M��ÿ�а����¸�ʽ����һ�����ֲ�����Ϣ��
    ����ѧ����1-N��ţ�
    ��i�����ֲ�������Mi���ո�ѧ��1���ո�ѧ��2�� ѧ��Mi 
    ��2�����˵�������һ����������ʾ���������Ȧ���ж����ˡ�
    ��3������������ 
    ����  7 4
        3 1 2 3
        2 1 4
        3 5 6 7
        1 6 
  ���  4
*/
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int number_club,number_student;
    //����ѧ�����;��ֲ���
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
            //���ǰ��û�����뵽�ظ�Ԫ�أ���ǰ��Ķ�����ʶ
            {
                scanf("%d",&k);
                //ѧ��k��һ�γ���
                if (student[k] == 0)
                //
                {
                    student[k] = i;//˵���ǵڼ���club��
                    continue;
                }
                else
                {
                    help = student[k];
                    //��ǰ���student == i���ĳ�help                    
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
            //�Ѿ��������ظ���
            {   
                scanf("%d",&k);

                if (student[k] == 0 || student[k] == help)
                {
                    student[k] = help ;
                }
                else
                {
                    //���ǵڶ����ظ�
                    help1 = student[k];
                    //��ǰ���student == i���ĳ�student = help1      
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
    //���濪ʼ�����������Ȧ
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
    printf("�ֱ���:");
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