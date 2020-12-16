#include<stdio.h>
#include<stdlib.h>
#define MAX_LENGTH 80
int Bubble(int *bubble);
int Select(int *select);
int insert(int *insert);
//冒泡排序，选择排序，插入排序
//Bubble sort, select sort, insert sort
int main()
{
    //x【0】放有几个元素
	int Bubble_sort[MAX_LENGTH + 1] = {0};
    int Select_sort[MAX_LENGTH + 1] = {0};
    int Insert_sort[MAX_LENGTH + 1] = {0};
    int i;
    printf("从小到大\n");
    printf("请输入数字以#结尾:\n");
    for(i = 1 ; i <= MAX_LENGTH ; i++)
    {
        scanf("%d", &Bubble_sort[i]);
        Select_sort[i] = Insert_sort[i] = Bubble_sort[i] ;
        Bubble_sort[0] ++; 
        Select_sort[0] ++;
        Insert_sort[0] ++;
        if(getchar() == '#')
        {
            break;
        }
    }  
    Bubble(Bubble_sort);
    Select(Select_sort);
    insert(Insert_sort);
    printf("bubble:\n");
    for ( i = 1; i <= Bubble_sort[0]; i++)
    {
        printf("%d ",Bubble_sort[i]);
    }
    printf("\n");
    printf("select:\n");
    for ( i = 1; i <= Select_sort[0]; i++)
    {
        printf("%d ",Select_sort[i]);
    }
    printf("\n");
    printf("Insert:\n");
    for ( i = 1; i <= Insert_sort[0]; i++)
    {
        printf("%d ",Insert_sort[i]);
    }
    printf("\n");
    system("pause");
    return (0);
}

int Bubble(int *bubble)
{
    int k;
    for ( int i  = 1; i <= bubble[0]; i++)
    {
        //后往前冒
        for ( int j = bubble[0] ; j  >  1 ; j -- )
        {
            
            if( bubble[j]  < bubble [ j - 1])
            {
                k = bubble[j];
                bubble[j] = bubble[j  - 1];
                bubble[j - 1] = k ;
            }
        }
    }
    return (1);
}


int Select(int *select)
{
    int min,k;
    for ( int i = 1; i <= select[0]; i++)
    {
        int min = i; 
        for ( int j = i; j <= select[0]; j++)
        {
            if( select[j]  < select[min])
            {
                min = j ;
            }
        }
        if( min != i)
        {
          k = select[i];
          select[i] = select[min];
          select[min] = k ;
        }
    }
    return (2);
}


int insert(int *insert)
{
    //插入排序比较特殊
    //total_number将表示有几个元素
    //insert【0】是哨兵
    //因为线性表要移动，所以直接从后向前了
    int total_number,i,j,k;
    total_number = insert[0];
    for (i = 2; i <= total_number; i++)
    {
        //默认前i - 1个已经排序好
        //i待排序
        insert[0] = insert[i];
        //从后向前
        for ( j = i ;  j ; j --)
        {
            if(insert[j] <= insert[j - 1])
            {
                k = insert[j];
                insert[j] = insert[j - 1];
                insert[j - 1] = k; 
            }
            else
            {
                break ;
            }
        }
    }
    insert[0] = total_number ;
    return (3);
}