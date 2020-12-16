#include<stdio.h>
#include<stdlib.h>
//�ö�ά����洢����ɫ����
typedef struct item
{
    int row,column;
} item ;//������

int CreateMartix(int*** martix);
void PrintMartix(int **martix);
int function(int** martix);

int main()
{
    int **martix = 0,row,column;
    CreateMartix(&martix);
    printf("��Ҫ���д���ľ���\n");
    PrintMartix(martix);
    printf("������\n");
    function(martix);
    PrintMartix(martix);
    free(martix);
    system("pause");
    return 0;
}

int CreateMartix(int*** martix)
{
    int i,j,row,column;
    printf("��������ɫ�����������\n");
    scanf("%d%d",&row,&column);
    *martix = (int ** )(calloc(row + 1,sizeof(int *)));//0����
    for(i = 0 ; i < row + 1 ;i++)
    {
        (*martix)[i] = (int*)(calloc(column+ 1,sizeof(int)));//0����
    }
    printf("��������ɫ����ÿ��λ�õľ���ֵ\n");
    for(i = 1 ; i < row + 1 ;i++)
    {
        for(j = 1 ; j < column +1 ; j++)
        {
            scanf("%d",&(*martix)[i][j]);
        }
    }
    //��������Ϣ�浽martix[0][0]���У���martix[0][1]���У�
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
    //contorl1:�����
    //contorl2������
    item *it = 0;
    it =( item *)(calloc(martix[0][0] * martix[0][1] + 1,sizeof(item)));
    //������������[0][0]����
    for(i = 1 ;i < martix[0][0] + 1;i ++)//��������Ϊ�����ɨ�跽ʽ����
    {
        for(j = 1 ;j < martix[0][1] + 1;j ++)
        {
            //������ɫһ�������Ϊ���·��������������ϣ������ҷ���ͬ��
            //����ɨ��row -1 ����
            //����column - 1
            if(martix[i][j] == 0)
            {
                continue;
            }
            if(j < martix[0][1] - 1)//����
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
            if(i < martix[0][0] - 1)//����
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