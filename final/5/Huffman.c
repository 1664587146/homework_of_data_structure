/*
    ���ܳ���a-z A-Z , .  " ` 0-9 ? ! - '\n' �ո�
    һ�� 26 + 26 + 10 + 9 = 71��
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define COUNT_OF_CHAR 71

/*
    �������Ľڵ㽫������һ�������ڣ�ÿ�λؽ���ά������ʧ�Ķ�����ὫȨֵ���㡣
    �������ӿɲ鿴����
*/
//node�Ķ���
#define  max_weight INT_MAX
typedef struct
{
	int weight;//Ȩֵ
    char info;
	int parent,lchild,rchild;
}HTNode, *HuffmanTree;
//�����渨���ռ������Ա�
typedef char **HuffmanCode;

static char character[COUNT_OF_CHAR] =
/*
    ���ܳ��ֵ��ַ�
*/
{
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V',
    'W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r',
    's','t','u','v','w','x','y','z',',','.','"','`','0','1','2','3','4','5','6','7','8','9',
    '?','!','-',' ','\n'
};

int read_and_statistic(int *times)
{
    //times�Ǽ�������,��Ӧ��ϵ characters[i]�ĳ��ִ��� =  times[i]
    FILE *file = fopen("resource.txt","r");
    if(!file)
    {
        printf("�ļ�����ʧ�ܣ�\n");
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
    //times�Ǽ�������,��Ӧ��ϵ characters[i]�ĳ��ִ��� =  times[i]
    int size, room;
    //size �ڵ���

    //(size *2 - 1) �ǻ��������Ŀռ�
    //m 
    size = COUNT_OF_CHAR ;
    room = (size *2 - 1);
    (*HT) = ( HuffmanTree ) calloc( room ,sizeof(HTNode));
    int i , j , p , min1 , min2;
    //���濪ʼ��ʼ��
    for (i = 0 ,p = 0 ; i < size; i++ , p++)
    {
        (*HT)[p]. weight = times[i];
        (*HT)[p].info = character[i]; 
        (*HT)[p]. parent = 0;
        (*HT)[p]. lchild = 0;
        (*HT)[p]. rchild = 0;
    }
    //��Ϊ��calloc ��������������ʱ�Զ������
    //���濪ʼ����
    int state ; 
    for(i = size ; i < room ; i++)
    {
        //ѡ��parent = 0������С������
        //�ҵ�
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
            min1 = j ;//��������˽�����Ҫ���¸�ֵ��min2һ��
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
        printf("Huffman.txt,����ʧ��");
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
//��Ϊ�������㣬�޷���bitλд�룬���Ի���"0","1"��
{
    FILE *file_r = fopen("resource.txt","r"),*file_w = fopen("code.dat","wb");
    if(!file_r ||!file_w )
    {
        printf("�ļ�����ʧ�ܣ�\n");
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
    ���룺
    ÿ������16���ֽڣ�Ȼ������ҵ��ˣ�
    �ͽ�����δ����Ĵ���
    ����Ѷ�ȡ���ֽڲ����ˣ����ٶ�ȡ16���ֽ�
*/
{
    FILE *file_r = fopen("code.dat","rb");
    FILE *file_w = fopen("recode.txt","w");
    if(!file_r ||!file_w )
    {
        printf("�ļ�����ʧ�ܣ�\n");
        exit (0);
    }
    char a_line_of_data_in_file[MAX_BYTE];
    int i = 0;
    int state = 1;
    //��ѭ������
    int  node = COUNT_OF_CHAR * 2 - 1 - 1;
    //���ǽ���������ʱ��room = (size *2 - 1);
    //���Ҵ�0��ʼ
    fread(a_line_of_data_in_file, 1 ,MAX_BYTE,file_r);
    //���濪ʼ��Huffman����
    for (;;)
    {
        if((*HT)[node] .lchild == 0 && (*HT)[node] .rchild == 0)
        {
            fputc((*HT)[node] . info ,file_w); 
            //node��λ
            node = COUNT_OF_CHAR * 2 - 1 - 1;
        }
        else if(a_line_of_data_in_file[i] == '0' )
        //����0 �Һ���1
        {
            node = (*HT)[node] . lchild;
            i ++ ;
            i = i  % MAX_BYTE;
            //������β
            if(i == 0)
            {
                state = fread(a_line_of_data_in_file, sizeof(char) ,MAX_BYTE,file_r);
            }
        }
        //�Һ��Ӳ��
        else if(a_line_of_data_in_file[i] == '1' )
        {
            node = (*HT)[node] . rchild;
            i ++;
            i = i % MAX_BYTE;
            //������β
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
        printf("%c�ı�����:%s\n",HT[i].info ,HC[i]);*/
    saving(HC);
    recoding(&HT);
    for ( i = 0; i < COUNT_OF_CHAR ; i++)
    {
        free(HC[i]);
    }
    //hc �� ht�൱�����������룬���������һ����ʧ
    system("Pause");
    return (0);
}
