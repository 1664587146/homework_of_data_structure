#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
    这里树的节点将放置于一个数组内，每次回进行维护，消失的顶点则会将权值置零。
    测试例子可查看书上
*/
//node的定义
#define  max_weight INT_MAX
typedef struct
{
	int weight;//权值
	int parent,lchild,rchild;
}HTNode, *HuffmanTree;
//这上面辅助空间是线性表
typedef char **HuffmanCode;

int     HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC);

int main()
{
    int i;
    HuffmanTree HT ;
    HuffmanCode HC ; 
    HuffmanCoding(&HT,&HC);
    for( i = 1;i <= HT[0].weight ; i++)
        printf("权值%d的编码是:%s\n",HT[i].weight ,HC[i]);
    system("pause"); 
    return 0;
}

int     HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC)
{
    int size, m;
    printf("请输入有几个节点:\n");
    scanf("%d",&size);
    while (size <= 1)
    {
        printf("请重新输入:\n");
        scanf("%d",&size);        
    }
    //(size *2 - 1) 是霍夫曼树的空间
    m = (size *2 - 1);
    (*HT) = ( HuffmanTree ) calloc((size *2 - 1) + 1,sizeof(HTNode));
    //【0】存有几个
    (*HT)[0]. weight = size ;
    printf("请输入具体权值:\n");
    int i , j , p , min1 , min2;
    for (i = 1 ,p = 1 ; i <= size; i++ , p++)
    {
        scanf("%d",&j);
        (*HT)[p]. weight = j; 
        (*HT)[p]. parent = 0;
        (*HT)[p]. lchild = 0;
        (*HT)[p]. rchild = 0;
    }//因为是calloc 所以其他在申请时自动清空了
    //下面开始建树
    int state ; 
    for(i = size  + 1; i <= m ; i++)
    {
        //选择parent = 0；且最小的两个
        //找点
        for(p = 1,state = 0,min1  = max_weight;p < i; p ++)
        {
            if((*HT)[p] . weight < min1 && !(*HT)[p] . parent)
            {
                min1 = (*HT)[p] .  weight;
                j = p;
                state = 1;
            }
        }
        if(state)
            min1 = j ;//如果发生了交换则要重新赋值，min2一样
        else
        {
            min1 = 1;
        }
        (*HT)[min1] . parent = 1; 
        for (p = 1,state = 0,min2 = max_weight ;p < i; p ++)
        {
            if((*HT)[p] . weight < min2 && !(*HT)[p] . parent)
            {
                min2 =(*HT)[p] . weight;
                j = p;
                state = 1;
            }
        }
        if(state) 
            min2 = j ;
        else
        {
            min2 = 1;
        }
        (*HT)[min2] . parent = 1; 
        //两个点找到
        //下面开始建树
        (*HT)[min1]  . parent = (*HT)[min2] . parent = i;
        (*HT)[i] . lchild = min1;
        (*HT)[i] . rchild = min2;
        (*HT)[i] . weight = (*HT)[min1] . weight + (*HT)[min2] . weight;
    }
    //下面开始编码
    char *cd;
    int start;
    *HC = (HuffmanCode)malloc((size + 1) * sizeof(char *));
	cd = (char*)malloc(size *sizeof(char));	
	cd[size -1] = '\0';
	for(int i=1; i<= size ; ++i)
    {
		start = size -1;
		for(int c=i, f=(*HT)[i].parent; f!=0; c=f, f=(*HT)[f].parent)
        {
			if((*HT)[f].lchild == c)	cd[--start] = '0';
			else cd[--start] = '1';
		}
		(*HC)[i] = (char*)malloc((size-start) * sizeof(char));
		strcpy((*HC)[i], &cd[start]);
	}
    return 0;
}
