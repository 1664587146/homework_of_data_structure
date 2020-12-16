#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
    �������Ľڵ㽫������һ�������ڣ�ÿ�λؽ���ά������ʧ�Ķ�����ὫȨֵ���㡣
    �������ӿɲ鿴����
*/
//node�Ķ���
#define  max_weight INT_MAX
typedef struct
{
	int weight;//Ȩֵ
	int parent,lchild,rchild;
}HTNode, *HuffmanTree;
//�����渨���ռ������Ա�
typedef char **HuffmanCode;

int     HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC);

int main()
{
    int i;
    HuffmanTree HT ;
    HuffmanCode HC ; 
    HuffmanCoding(&HT,&HC);
    for( i = 1;i <= HT[0].weight ; i++)
        printf("Ȩֵ%d�ı�����:%s\n",HT[i].weight ,HC[i]);
    system("pause"); 
    return 0;
}

int     HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC)
{
    int size, m;
    printf("�������м����ڵ�:\n");
    scanf("%d",&size);
    while (size <= 1)
    {
        printf("����������:\n");
        scanf("%d",&size);        
    }
    //(size *2 - 1) �ǻ��������Ŀռ�
    m = (size *2 - 1);
    (*HT) = ( HuffmanTree ) calloc((size *2 - 1) + 1,sizeof(HTNode));
    //��0�����м���
    (*HT)[0]. weight = size ;
    printf("���������Ȩֵ:\n");
    int i , j , p , min1 , min2;
    for (i = 1 ,p = 1 ; i <= size; i++ , p++)
    {
        scanf("%d",&j);
        (*HT)[p]. weight = j; 
        (*HT)[p]. parent = 0;
        (*HT)[p]. lchild = 0;
        (*HT)[p]. rchild = 0;
    }//��Ϊ��calloc ��������������ʱ�Զ������
    //���濪ʼ����
    int state ; 
    for(i = size  + 1; i <= m ; i++)
    {
        //ѡ��parent = 0������С������
        //�ҵ�
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
            min1 = j ;//��������˽�����Ҫ���¸�ֵ��min2һ��
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
        //�������ҵ�
        //���濪ʼ����
        (*HT)[min1]  . parent = (*HT)[min2] . parent = i;
        (*HT)[i] . lchild = min1;
        (*HT)[i] . rchild = min2;
        (*HT)[i] . weight = (*HT)[min1] . weight + (*HT)[min2] . weight;
    }
    //���濪ʼ����
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
