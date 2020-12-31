/*
Huffman编码与解码(必做)（Huffman编码、二叉树）
[问题描述]
对一篇不少于5000字符的英文文章（source.txt），统计各字符出现的次数，实现Huffman编码(code.dat)，以及对编码结果的解码(recode.txt)。
[基本要求]
（1） 输出每个字符出现的次数和编码,并存储文件(Huffman.txt)。
（2） 在Huffman编码后，英文文章编码结果保存到文件中(code.dat)，编码结果必须是二进制形式，即0 1的信息用比特位表示，不能用字符’0’和’1’表示（*）。
（3） 实现解码功能。
*/

/*
    可能出现a-z A-Z , .  " ` 0-9 ? ! - '\n' 空格
    一共 26 + 26 + 10 + 9 = 71个
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define COUNT_OF_CHAR 71

/*
    这里树的节点将放置于一个数组内，每次回进行维护，消失的顶点则会将权值置零。
    测试例子可查看书上
*/
//node的定义
#define  max_weight INT_MAX
typedef struct
{
	int weight;//权值
    char info;
	int parent,lchild,rchild;
}HTNode, *HuffmanTree;
//这上面辅助空间是线性表
typedef char **HuffmanCode;

static char character[COUNT_OF_CHAR] =
/*
    可能出现的字符
*/
{
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V',
    'W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r',
    's','t','u','v','w','x','y','z',',','.','"','`','0','1','2','3','4','5','6','7','8','9',
    '?','!','-',' ','\n'
};

int read_and_statistic(int *times)
{
    //times是计数数组,对应关系 characters[i]的出现次数 =  times[i]
    FILE *file = fopen("resource.txt","r");
    if(!file)
    {
        printf("文件操作失败；\n");
        exit (0);
    }
    char a_line_of_data_in_file[7000];
    int i , j ,max_count;
    max_count = 7000;
    while (feof(file) == 0)
    {
        fgets(a_line_of_data_in_file,max_count,file);
        for ( i = 0; i < max_count && a_line_of_data_in_file[i - 1] != '\n' ; i++)
        {
            for ( j = 0; j < COUNT_OF_CHAR; j++)
            {
                if(a_line_of_data_in_file[i] == character[j])
                {
                    times[j]++;
                    break;
                }
            }
        }
    }
    fclose(file);
    return (1);
}

int HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC , int *times)
{
    //times是计数数组,对应关系 characters[i]的出现次数 =  times[i]
    int size, room;
    //size 节点数

    //(size *2 - 1) 是霍夫曼树的空间
    //m 
    size = COUNT_OF_CHAR ;
    room = (size *2 - 1);
    (*HT) = ( HuffmanTree ) calloc( room ,sizeof(HTNode));
    int i , j , p , min1 , min2;
    //下面开始初始化
    for (i = 0 ,p = 0 ; i < size; i++ , p++)
    {
        (*HT)[p]. weight = times[i];
        (*HT)[p].info = character[i]; 
        (*HT)[p]. parent = 0;
        (*HT)[p]. lchild = 0;
        (*HT)[p]. rchild = 0;
    }
    //因为是calloc 所以其他在申请时自动清空了
    //下面开始建树
    int state ; 
    for(i = size ; i < room ; i++)
    {
        //选择parent = 0；且最小的两个
        //找点
        for(p = 0,state = 0,min1  = max_weight;p < i; p ++)
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
        for (p = 0,state = 0,min2 = max_weight ;p < i; p ++)
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
    *HC = (HuffmanCode) calloc((size ) , sizeof(char *));
	cd = (char*) calloc (size ,sizeof(char));	
	cd[size -1] = '\0';
	for(int i= 0; i<= size ; ++i)
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
    FILE *file = fopen("Huffman.txt","w");
    if(!file)
    {
        printf("Huffman.txt,创建失败");
        exit(0);
    }
    for ( j = 0; j < COUNT_OF_CHAR; j++)
    {
        fprintf(file,"%c,%s,%d\n",character[j],(*HC)[j],times[j]);
    }
    fclose(file);
    return 2;
}

int saving(HuffmanCode HC)
//因为技术不足，无法按bit位写入，所以还是"0","1"了
{
    FILE *file_r = fopen("resource.txt","r"),*file_w = fopen("code.dat","wb");
    if(!file_r ||!file_w )
    {
        printf("文件操作失败；\n");
        exit (0);
    }
    char a_line_of_data_in_file[7000];
    int i , j ,max_count;
    max_count = 7000;
    while (feof(file_r) == 0)
    {
        fgets(a_line_of_data_in_file,max_count,file_r);
        for ( i = 0; i < max_count && a_line_of_data_in_file[i - 1] != '\n' ; i++)
        {
            for ( j = 0; j < COUNT_OF_CHAR; j++)
            {
                if(a_line_of_data_in_file[i] == character[j])
                {
                    fwrite(HC[j],sizeof(char),strlen(HC[j]),file_w);
                }
            }
        }
    }
    fclose(file_r);
    fclose(file_w);
    return (5);
}


#define MAX_BYTE 16

int recoding(HuffmanTree *HT)
/*
    解码：
    每次最多读16个字节，然后如果找到了，
    就将后面未处理的处理，
    如果已读取的字节不够了，则再读取16个字节
*/
{
    FILE *file_r = fopen("code.dat","rb");
    FILE *file_w = fopen("recode.txt","w");
    if(!file_r ||!file_w )
    {
        printf("文件操作失败；\n");
        exit (0);
    }
    char a_line_of_data_in_file[MAX_BYTE];
    int i = 0;
    int state = 1;
    //是循环变量
    int  node = COUNT_OF_CHAR * 2 - 1 - 1;
    //就是建哈夫曼树时的room = (size *2 - 1);
    //而且从0开始
    fread(a_line_of_data_in_file, 1 ,MAX_BYTE,file_r);
    //下面开始在Huffman树找
    for (;;)
    {
        if((*HT)[node] .lchild == 0 && (*HT)[node] .rchild == 0)
        {
            fputc((*HT)[node] . info ,file_w); 
            //node复位
            node = COUNT_OF_CHAR * 2 - 1 - 1;
        }
        else if(a_line_of_data_in_file[i] == '0' )
        //左孩子0 右孩子1
        {
            node = (*HT)[node] . lchild;
            i ++ ;
            i = i  % MAX_BYTE;
            //读到结尾
            if(i == 0)
            {
                state = fread(a_line_of_data_in_file, sizeof(char) ,MAX_BYTE,file_r);
            }
        }
        //右孩子差不多
        else if(a_line_of_data_in_file[i] == '1' )
        {
            node = (*HT)[node] . rchild;
            i ++;
            i = i % MAX_BYTE;
            //读到结尾
            if(i == 0)
            {
                state = fread(a_line_of_data_in_file, sizeof(char) ,MAX_BYTE,file_r);
            }
        }
        if(feof(file_r) == 1 || !state)
        {
            break ;
        }
    }
    fclose(file_r);
    fclose(file_w);
    return (7);
}

int main()
{
    int times[COUNT_OF_CHAR] = {0};
    HuffmanCode HC = 0;
    HuffmanTree HT = 0;
    read_and_statistic(times);
    HuffmanCoding(&HT,&HC,times);
    int i;/*
    for( i = 0;i < COUNT_OF_CHAR ; i++)
        printf("%c的编码是:%s\n",HT[i].info ,HC[i]);*/
    saving(HC);
    recoding(&HT);
    for ( i = 0; i < COUNT_OF_CHAR ; i++)
    {
        free(HC[i]);
    }
    //hc 和 ht相当于主程序申请，会和主程序一起消失
    system("Pause");
    return (0);
}
