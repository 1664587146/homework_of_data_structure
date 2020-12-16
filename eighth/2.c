#include<stdio.h>
#include<stdlib.h>
#define MAX_LENGTH 80
int Bubble(int *bubble);
int Select(int *select);
int insert(int *insert);
//ð������ѡ�����򣬲�������
//Bubble sort, select sort, insert sort
int main()
{
    //x��0�����м���Ԫ��
	int Bubble_sort[MAX_LENGTH + 1] = {0};
    int Select_sort[MAX_LENGTH + 1] = {0};
    int Insert_sort[MAX_LENGTH + 1] = {0};
    int i;
    printf("��С����\n");
    printf("������������#��β:\n");
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
        //����ǰð
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
    //��������Ƚ�����
    //total_number����ʾ�м���Ԫ��
    //insert��0�����ڱ�
    //��Ϊ���Ա�Ҫ�ƶ�������ֱ�ӴӺ���ǰ��
    int total_number,i,j,k;
    total_number = insert[0];
    for (i = 2; i <= total_number; i++)
    {
        //Ĭ��ǰi - 1���Ѿ������
        //i������
        insert[0] = insert[i];
        //�Ӻ���ǰ
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