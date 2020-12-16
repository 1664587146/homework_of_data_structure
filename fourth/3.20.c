#include<stdio.h>
#include<stdlib.h>
//为了简化了表所以直接用表
#define m 4
#define n 4
static int g[m + 1][n + 1]={ 
    0,0,0,0,0,
    0,1,1,1,1,
    0,1,2,3,1,
    0,1,1,4,5,
    0,5,9,1,7,
};//上下左右都有
int ShowGraph(int g[m + 1][n + 1]);
int ChangeColour(int g[m + 1][n + 1],int i,int j,int colour);

int main()
{
    int i,j,colour;
    ShowGraph(g);
    printf("请输入你要的改的块\n行小于%d但大于0\n列小于%d但大于0\n",m,n);
    scanf("%d%d",&i,&j);
    while(j > m || i > n)
    {
        printf("输入错误\n请输入你要的改的块\n行小于%d但大于0\n列小于%d但大于0\n");
        scanf("%d%d",&i,&j);
    }
    printf("请输入你要改成的颜色\n");
    scanf("%d",&colour);
    ChangeColour(g,i,j,colour);
    ShowGraph(g);
    system("pause");
    return 0;
}

int ChangeColour(int g[m + 1][n + 1],int i,int j,int colour)
{
    if( g == 0) return(0);
    int ColourNow;
    ColourNow = g[i][j];
    g[i][j] = colour;
    if(g[i - 1][j] == ColourNow && (i - 1) > 0)
    {
        ChangeColour(g,i - 1,j,colour);
    }
    if(g[i][j - 1] == ColourNow && (j - 1) > 0 )
    {
        ChangeColour(g,i,j - 1,colour);
    }
    if(g[i + 1][j] == ColourNow && (i + 1) <= m)
    {
        ChangeColour(g,i + 1,j,colour);
    }
    if(g[i][j + 1] == ColourNow && (j + 1) <= n)
    {
        ChangeColour(g,i,j + 1,colour);
    }
    return 0;
}

int ShowGraph(int g[m + 1][n + 1])
{
    int i,j;
    printf("用矩阵的方式输出色块\n");
    for(i = 1; i <= m ; i++)
    {
        printf("|");
        for(j = 1; j <= n ; j++)
        {
            printf("%d\t",g[i][j]);
        }
        printf("|\n");    
    }
}
