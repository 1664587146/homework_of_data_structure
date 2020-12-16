#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 12500
#define MAXROW 1440
typedef struct 
{
    int data;
}Elemtype;

typedef struct
{
    int row,column;
    Elemtype data;
}Triple;

typedef struct
{
    Triple data[MAXSIZE + 1];//data[0] is not used
    int mu,nu,tu;//行 列 总数
}TSMatrix;

int Insert(TSMatrix *matrix,int row1 ,int column1,Elemtype elem)
{
    int i,maxRow = 0,maxCol = 0;
    Triple *node;
    for (i = 0;; i++)
        //停止条件：上和一个三元组比行值更大
        //行值一样列值更大
        //(未给输错冗余)
        {
            if((matrix -> data + i + 1) -> row > row1) 
            //(matrix -> data + i) -> row = 0为元素的标志
            break ;
            if((matrix -> data + i ) -> row == row1)
            {
                if((matrix -> data + i + 1) -> column > column1 )
                break;
            }
            if(row1 > matrix -> mu)
            {
                i = matrix -> tu;
                break;
            }
        }
        if(matrix -> tu + 1 > MAXSIZE)
        {
            printf("矩阵已满");
            return(0);
        }
        node = (matrix ->data + (matrix -> tu + 1));
        for(;node != (matrix -> data + i) ;node --) 
            *node = *(node -1);
        matrix -> tu ++;
        (matrix -> data + i + 1) -> row = row1 ;
        (matrix -> data + i + 1) -> column = column1;
        (matrix -> data + i + 1) ->data =elem;
        for(i = 1;i <= matrix -> tu ;i++ )
        {
            if((matrix -> data + i ) -> row > maxRow)
            maxRow = (matrix -> data + i ) -> row;
            if((matrix -> data + i ) -> column > maxCol)
            maxCol = (matrix -> data + i ) -> column;
        }
        matrix -> mu = maxRow;
        matrix -> nu = maxCol;
}

int CreateSMatrix(TSMatrix **matrix)
{
    TSMatrix *newbase;
    //calloc会全部置0，相当于初始化
    newbase = (TSMatrix *)calloc(1,sizeof(TSMatrix));
    if(!newbase) exit(0);
    *matrix = newbase;
    //Put data into matrix.
    Elemtype elem;
    int row1,column1,i,j,rowMax = 0,colMax = 0;
    printf("请输入行 列 和具体值，格式（row，column，data）一次输完以#结尾\n");
    for(;;)
    {
        scanf("(%d,%d,%d)",&row1,&column1,&elem.data);
        Insert(*matrix,row1,column1,elem);
        if(getchar() == '#')
        {
            break;
        }
    }
    return (1);
}
//create success 1  
//newbase = 0 exit(0);

int PrintSMatrix(TSMatrix matrix)
//循环 若当前3元组进入下一行则下一行输出 两个三元组中间的空格用“ ”处理-------------------
{
    int row,i,j,k,column;
    row = matrix.mu;
    column = matrix.nu;
    for(i = 1, j = 1;j <= row;j++)
    {
        printf("|");        
        for(k = 1;k <= column;k++)
        {
            if(( matrix.data + i )->column == k)
            {
                printf("%d",(matrix.data + i)->data);
                i++;
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

int TransposeSMatrix(TSMatrix M,TSMatrix *T)
{
    T -> mu = M.nu;
    T -> nu = M.mu;
    T -> tu = M.tu;
    if(T -> tu)
    {
        int col,p,q = 1,i = 1;
        for(col = 1;col <= M.nu;++col)
            for(p = 1; p <= M.tu; ++p)
                if(M.data[p].column == col)
                {
                    T -> data[q].row = M.data[p].column;
                    T -> data[q].column = M.data[p].row;
                    T -> data[q++].data = M.data[p].data;
                }
    } 
    return (3);
}

int main()
{
    printf("中文使用的是GBK。Simplified Chinese using GBK.\n"); 
    TSMatrix *m1,m2;
    printf("开始制矩阵m1\n");
    CreateSMatrix(&m1);
    printf("ok 结束显示阵m1\n");
    PrintSMatrix((*m1));
    printf("开始转置矩阵m1结果放于m2\n");
    TransposeSMatrix(*m1,&m2);
    printf("ok 结束显示阵m2\n");
    PrintSMatrix(m2);
    system("pause");
    return 0;
}