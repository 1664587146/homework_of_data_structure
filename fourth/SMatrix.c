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
    int mu,nu,tu;//�� �� ����
}TSMatrix;

int Insert(TSMatrix *matrix,int row1 ,int column1,Elemtype elem)
{
    int i,maxRow = 0,maxCol = 0;
    Triple *node;
    for (i = 0;; i++)
        //ֹͣ�������Ϻ�һ����Ԫ�����ֵ����
        //��ֵһ����ֵ����
        //(δ���������)
        {
            if((matrix -> data + i + 1) -> row > row1) 
            //(matrix -> data + i) -> row = 0ΪԪ�صı�־
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
            printf("��������");
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
    //calloc��ȫ����0���൱�ڳ�ʼ��
    newbase = (TSMatrix *)calloc(1,sizeof(TSMatrix));
    if(!newbase) exit(0);
    *matrix = newbase;
    //Put data into matrix.
    Elemtype elem;
    int row1,column1,i,j,rowMax = 0,colMax = 0;
    printf("�������� �� �;���ֵ����ʽ��row��column��data��һ��������#��β\n");
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
//ѭ�� ����ǰ3Ԫ�������һ������һ����� ������Ԫ���м�Ŀո��á� ������-------------------
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
    printf("����ʹ�õ���GBK��Simplified Chinese using GBK.\n"); 
    TSMatrix *m1,m2;
    printf("��ʼ�ƾ���m1\n");
    CreateSMatrix(&m1);
    printf("ok ������ʾ��m1\n");
    PrintSMatrix((*m1));
    printf("��ʼת�þ���m1�������m2\n");
    TransposeSMatrix(*m1,&m2);
    printf("ok ������ʾ��m2\n");
    PrintSMatrix(m2);
    system("pause");
    return 0;
}