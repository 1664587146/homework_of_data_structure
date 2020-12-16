#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 12500
#define MAXROW 1440

typedef struct
{
    int row,column;
    int data;
}Triple;

int CreateMatrix(int ***matrix,int row,int column)
{
    int **newbase,i,row1,column1,data;
    //calloc��ȫ����0���൱�ڳ�ʼ��
    //��0�в���
    newbase = (int **)calloc(row + 1,sizeof(int *));
    if(!newbase) exit(0);
    (*matrix) = newbase;
    for(i = 1;i <= row ; i++)
    {
        *((*matrix) + i) = (int *)calloc(column + 1,sizeof(int ));
    }
    printf("�������� �� �;���ֵ����ʽ��row��column��data����#��β\n");
    for(;;)
    {
        scanf("(%d,%d,%d)",&row1,&column1,&data);
        if(row1 > row ||column > column)
        {
            printf("������������������ʽ��row��column��data��\n");
            scanf("(%d,%d,%d)",&row1,&column1,&data);
        }
        (*matrix)[row1][column1] = data;
        if(getchar() == '#')
        {
            break;
        }
    }
    return (1);
}
//create success 1  
//newbase = 0 exit(0);

int PrintMatrix(int  **matrix,int row ,int column)
//ѭ�� 0�ÿո���
{
    int i,j;
    for(i = 1;i <= row;i++)
    {
        printf("|");        
        for(j = 1;j <= column;j++)
        {
            if(matrix[i][j])
            {
                printf("%d",matrix[i][j]);
            }
            else
            {
                printf(" ");
            }
        }
        printf("|\n");
    }
    return(2);
}

//�Ƚ������е���������С�ҵ�������x[m]
//��������ҵ�����y[n]
//��xy z���ҵ�һ���ļ����� O(m*n)

int Saddle_Point(int  **matrix,int row ,int column)
{
    int i,j,compare,row1,column1,state;
    Triple *x,*y;
    x = (Triple *)calloc(row + 1,sizeof(Triple));
    y = (Triple *)calloc(column + 1,sizeof(Triple));
    //����С
    for(i = 1; i < row +1 ; i++)
    {
        for(j = 1,row1 = i, column1 = 1,compare = matrix[i][1] ; j < column +1 ; j++)
        {
            if(matrix[i][j] < compare)
            {
                compare = matrix[i][j];
                row1 = i;
                column1 = j;
            }
        }
        x[i].data = compare;
        x[i].row = row1;
        x[i].column = column1;
    }
    for(i = 1; i < column +1 ; i++)
    {
        for(j = 1,row1 = 1, column1 = i,compare = matrix[1][i] ; j < row +1 ; j++)
        {
            if(matrix[j][i] > compare)
            {
                compare = matrix[j][i];
                row1 = j;
                column1 = i;
            }
        }
        y[i].data = compare;
        y[i].row = row1;
        y[i].column = column1;
    }
    for(i = 1 , state = 0 ; i < column +1 ; i++)
    {
        for(j = 1; j < row + 1 ; j++)
        {
            if(x[i].column == y[j].column && x[i].row == y[j].row)
            {
                printf("����:(%d,%d,%d)\n",x[i].row,x[i].column,x[i].data);
                state = 1;
            }
        }
    }
    if(state == 0) printf("������\n");
}

int main()
{
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n"); 
    int **m1,row,column;
    printf("�����������\n");
    scanf("%d%d",&row,&column);
    getchar();
    printf("��ʼ�ƾ���m1\n");
    CreateMatrix(&m1,row,column);
    printf("ok ������ʾ��m1\n");
    PrintMatrix(m1,row,column);
    printf("��ʼ������\n");
    Saddle_Point(m1,row,column);
    system("pause");
    return 0;
}