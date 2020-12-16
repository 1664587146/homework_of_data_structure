#include<stdio.h>
#include<stdlib.h>
//用二维数组存储，颜色矩阵。
typedef struct item
{
    int row,column;
} item ;//帮助清

int CreateMartix(int*** martix);
void PrintMartix(int **martix);
int function(int** martix);

int main()
{
    int **martix = 0,row,column;
    CreateMartix(&martix);
    printf("将要进行处理的矩阵：\n");
    PrintMartix(martix);
    printf("处理后的\n");
    function(martix);
    PrintMartix(martix);
    free(martix);
    system("pause");
    return 0;
}

int CreateMartix(int*** martix)
{
    int i,j,row,column;
    printf("请输入颜色矩阵的行列数\n");
    scanf("%d%d",&row,&column);
    *martix = (int ** )(calloc(row + 1,sizeof(int *)));//0不用
    for(i = 0 ; i < row + 1 ;i++)
    {
        (*martix)[i] = (int*)(calloc(column+ 1,sizeof(int)));//0不用
    }
    printf("请输入颜色矩阵每个位置的具体值\n");
    for(i = 1 ; i < row + 1 ;i++)
    {
        for(j = 1 ; j < column +1 ; j++)
        {
            scanf("%d",&(*martix)[i][j]);
        }
    }
    //将行列信息存到martix[0][0]（行）和martix[0][1]（列）
    (*martix)[0][0] = row ;
    (*martix)[0][1] = column ; 
    return (1);
}

void PrintMartix(int **martix)
{
    int i,j;
    for(i = 1 ;i < martix[0][0] + 1;i ++)
    {
        for(j = 1 ;j < martix[0][1] + 1;j ++)
        {
            printf("%d ",martix[i][j]);
        }
        printf("\n");
    }
}

int function(int** martix)
{
    int i,j,contorl1 = 0,contorl2 = 0,k,t = 1;
    //contorl1:横向的
    //contorl2：纵向
    item *it = 0;
    it =( item *)(calloc(martix[0][0] * martix[0][1] + 1,sizeof(item)));
    //辅助处理数组[0][0]不用
    for(i = 1 ;i < martix[0][0] + 1;i ++)//采用以行为主序的扫描方式处理
    {
        for(j = 1 ;j < martix[0][1] + 1;j ++)
        {
            //出现颜色一样的情况为在下方连续两个或以上，或者右方相同；
            //纵向扫描row -1 结束
            //横向column - 1
            if(martix[i][j] == 0)
            {
                continue;
            }
            if(j < martix[0][1] - 1)//横向
            {
                for(contorl1 = 1; j + contorl1 <= martix[0][1];)
                {
                    if(martix[i][j + contorl1] == martix[i][j])
                    {
                        contorl1 ++ ;
                    } 
                    else
                    {
                        break;
                    }
                }
            }
            if(i < martix[0][0] - 1)//纵向
            {
                for(contorl2 = 1;i + contorl2 <= martix[0][0];)
                {
                    if(martix[i + contorl2][j] == martix[i][j])
                    {
                        contorl2 ++ ;
                    } 
                    else
                    {
                        break;
                    }
                }
            }
            if( contorl1 >= 3 )
            {
                if(!it[0].column)
                {
                    for(k = 0 ; k < contorl1 ; k++)
                    {
                        it[t].column = j + k;
                        it[t++].row = i;
                    }
                    it[0].column += contorl1;
                    contorl1 = 0;
                } 
                else
                {
                    int a;
                    for(k = 0 ; k < contorl1 ; k++)
                    {
                        int state = 1;
                        for(a = 1 ; a <= it[0].column ;a ++ )
                        {
                            if( it[a].column == j + k &&  it[a].row == i)
                             state = 0;
                        }
                        if (state)
                        {
                             it[t].column = j + k;
                            it[t++].row = i;
                            it[0].column += 1;
                        }
                    }
                    contorl1 = 0;
                }
            }
            if( contorl2 >= 3 )
            {
                if(!it[0].column)
                {
                    for(k = 0 ; k < contorl2 ; k++)
                    {
                        it[t ].column = j;
                        it[t++].row = i + k;
                    }
                    it[0].column += contorl2;
                    contorl2 = 0;
                } 
                else
                {
                    int a;
                    for(k = 0 ; k < contorl2 ; k++)
                    {
                        int state = 1;
                        for(a = 1 ; a <= it[0].column ;a ++ )
                        {
                            if( it[a].column == j &&  it[a].row == i + k)
                             state = 0;
                        }
                        if (state)
                        {
                             it[t].column = j;
                            it[t++].row = i  + k;
                            it[0].column += 1;
                        }
                    }
                    contorl2 = 0;
                }                
            }
        }
    }
    for(k = 0; k < t; k++)
    {
        martix[it[k].row][it[k].column] = 0;
    }
    free(it);
    return (1);
}