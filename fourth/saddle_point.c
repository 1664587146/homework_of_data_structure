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
    //calloc会全部置0，相当于初始化
    //第0行不用
    newbase = (int **)calloc(row + 1,sizeof(int *));
    if(!newbase) exit(0);
    (*matrix) = newbase;
    for(i = 1;i <= row ; i++)
    {
        *((*matrix) + i) = (int *)calloc(column + 1,sizeof(int ));
    }
    printf("请输入行 列 和具体值，格式（row，column，data）以#结尾\n");
    for(;;)
    {
        scanf("(%d,%d,%d)",&row1,&column1,&data);
        if(row1 > row ||column > column)
        {
            printf("输入错误，请重新输入格式（row，column，data）\n");
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
//循环 0用空格处理
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

//先将矩阵中的所有行最小找到，放于x[m]
//后将列最大找到放于y[n]
//在xy z中找到一样的即鞍点 O(m*n)

int Saddle_Point(int  **matrix,int row ,int column)
{
    int i,j,compare,row1,column1,state;
    Triple *x,*y;
    x = (Triple *)calloc(row + 1,sizeof(Triple));
    y = (Triple *)calloc(column + 1,sizeof(Triple));
    //行最小
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
                printf("马鞍点:(%d,%d,%d)\n",x[i].row,x[i].column,x[i].data);
                state = 1;
            }
        }
    }
    if(state == 0) printf("无马鞍点\n");
}

int main()
{
    printf("中文使用的是GBK。Simplified Chinese using GBK.\n"); 
    int **m1,row,column;
    printf("矩阵的行列数\n");
    scanf("%d%d",&row,&column);
    getchar();
    printf("开始制矩阵m1\n");
    CreateMatrix(&m1,row,column);
    printf("ok 结束显示阵m1\n");
    PrintMatrix(m1,row,column);
    printf("开始找马鞍点\n");
    Saddle_Point(m1,row,column);
    system("pause");
    return 0;
}