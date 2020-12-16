/*
    8、排序算法比较 （必做）（排序）
    [问题描述]
    利用随机函数产生10个样本，每个样本有20000个随机整数（并使第一个样本是正序，第二个样本是逆序），
    利用1 直接插入排序、1 希尔排序，1 冒泡排序、1 快速排序、 1 选择排序、堆排序 、归并排序 、 基数排序8种排序方法进行排序
    （结果为由小到大的顺序），并统计每一种排序算法对不同样本所耗费的时间。
    [基本要求]
    （1） 原始数据存在文件中，用相同样本对不同算法进行测试；
    （2） 屏幕显示每种排序算法对不同样本所花的时间；
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
static int bubble = 0 ;//时间变量，就是循环次数
int Bubble(int *array)
//冒泡排序
{
    int k;
    for ( int i  = 1; i <= array[0]; i++)
    {
        //后往前冒
        for ( int j = array[0] ; j  >  1 ; j -- )
        {
            bubble ++;
            if( array[j]  < array [ j - 1])
            {
                k = array[j];
                array[j] = array[j  - 1];
                array[j - 1] = k ;
            }
        }
    }
    return (1);
}
static int select = 0 ;//时间变量，就是循环次数
int Select(int *array)
//选择排序
{
    int min,k;
    for ( int i = 1; i <= array[0]; i++)
    {
        int min = i; 
        for ( int j = i; j <= array[0]; j++)
        {
            select ++;
            if( array[j]  < array[min])
            {
                min = j ;
            }
        }
        if( min != i)
        {
          k = array[i];
          array[i] = array[min];
          array[min] = k ;
        }
    }
    return (2);
}

static int insert = 0 ;//时间变量，就是循环次数
int Insert(int *array)
//直接插入排序
{
    //插入排序比较特殊
    //total_number将表示有几个元素
    //insert【0】是哨兵
    //因为线性表要移动，所以直接从后向前了
    int total_number,i,j,k;
    total_number = array[0];
    for (i = 2 ; i <= total_number ; i++)
    {
        //默认前i - 1个已经排序好
        //i待排序
        array[0] = array[i];
        //从后向前
        for ( j = i ;  j ; j --)
        {
            insert ++ ;
            if(array[j] <= array[j - 1])
            {
                k = array[j];
                array[j] = array[j - 1];
                array[j - 1] = k; 
            }
            else
            {
                break;     
            }
            
        }
    }
    array[0] = total_number ;
    return (3);
}

static int quick = 0 ;//时间变量，就是循环次数
//快速排序
int Partition(int *array , int low ,int high)
/*
    交换顺序表L中子表r【low 。。。 high 】的记录，枢轴记录到位，并返回其所在位置
    此时在它之前（后）的记录均不大（小于）它
*/
{

    int pivotkey,total_number;
    total_number = array [0];
    array[0] = array[low];
    pivotkey = array[low];
    while (high > low)
    {
        for (; high > low &&  array[high] >= pivotkey;high -- );
        {
            quick ++;
            array[low] = array [high];
        }
        for (; high > low &&  array[low] <= pivotkey; low ++);
        {
            quick ++;
            array[high] = array [low];
        }
    }
    array[low] = array[0];
    array [0] = total_number;
    return low ;
}
int Quick_Sort(int *array,int low ,int high)
{
    int pivotloc =  Partition(array,low,high); 
    if(low < high)
    {
        Quick_Sort(array,low ,pivotloc - 1);
        Quick_Sort(array, pivotloc + 1,high);
    }
    return (4);
}

// 希尔
static int shell = 0 ;//时间变量，就是循环次数
int Shell_Insert(int *array,int dk)//dk 是每次间隔的数字
//大到小
{
    //array[0]在排序过程中是哨兵
    //array[0]在一般情况下是长度
    int i ,j ,k = array[0];
    for ( i = dk +  1; i <= k; i++)
    {   
        shell ++;
        if(array[i] < array[i -dk] )
            continue;
        else
        {
            array[0] = array[i]; 
            for ( j = i -dk ; j > 0 && array[ 0 ] >  array[ j ] ; j -= dk)
            {
                shell ++;
                array [j +dk ] = array[j];
                array [ j ] = array[0];
            }
        }
    }
    array[0] = k;
    return 0;
}
int Shell_Sort(int *array,int dlta[],int t)
{
    for (int i = 0; i < t; i++)
    {
        shell ++;
        Shell_Insert(array,1);
    }
    return(5);
}


static int heap = 0;
//计数变量
//大顶堆
int HeapAdjust(int *array,int s,int m)//一次筛选的过程
{
    int rc,j;
    rc = array[s];
    for(j = 2 * s  ;  j <= m  ; j = j * 2)//通过循环沿较大的孩子结点向下筛选
    {
        heap ++;
        if(j < m && array[j] < array[j + 1]) //找到左右元素中较大的那个
            j ++;//j为较大的记录的下标
        
        if(rc > array[j])//如果比这个堆的堆顶大 
            break;

        array[s] = array[j];
        s = j;
    }
    array[s] = rc;//插入
    //rc找到位置
    return (6);
}
int HeapSort(int *array,int n)
{
    int temp,i,j;
    for(i = n / 2 ; i > 0 ; i -- )//通过循环初始化顶堆
    {
        heap ++;
        HeapAdjust(array,i,n);
    }

    for(i = n;i > 0;i -- )
    {
        heap ++;
        temp = array[1];
        array[1] = array[i];
        array[i] = temp;//将堆顶记录与未排序的最后一个记录交换
        //即队列后面是有序的
        HeapAdjust(array,1,i - 1);//重新调整为顶堆
    }
    return (6);
}


//归并排序
static int merge = 0;
void Merge(int arr[], int low, int mid, int high)
//归并
{
    int i, k;
    int *tmp = (int *)malloc((high-low+1)*sizeof(int));
    //申请空间，使其大小为两个
    int left_low = low;
    int left_high = mid;
    int right_low = mid + 1;
    int right_high = high;

    for(k=0; left_low<=left_high && right_low<=right_high; k++)
    {  // 比较两个指针所指向的元素
        merge ++;
        if(arr[left_low]<=arr[right_low])
        {
            tmp[k] = arr[left_low++];
        }else
        {
            tmp[k] = arr[right_low++];
        }
    }

    if(left_low <= left_high)
    {  
        //若第一个序列有剩余，直接复制出来粘到合并序列尾
        //memcpy(tmp+k, arr+left_low, (left_high-left_low+l)*sizeof(int));
        for(i=left_low;i<=left_high;i++)
        {
            merge ++;
            tmp[k++] = arr[i];
        }
    }

    if(right_low <= right_high)
    {
        //若第二个序列有剩余，直接复制出来粘到合并序列尾
        //memcpy(tmp+k, arr+right_low, (right_high-right_low+1)*sizeof(int));
        for(i=right_low; i<=right_high; i++)
        {
            merge ++;
            tmp[k++] = arr[i];
        }
    }

    for(i=0; i<high-low+1; i++)
    {
        merge ++ ;
        arr[low+i] = tmp[i];
        //将排序好的赋值回去
    }
    free(tmp);
    return;
}

void Merge_sort(int arr[], unsigned int first, unsigned int last)
{
    int mid = 0;
    if(first<last)
    {
        merge ++;
        mid = (first+last)/2;
         /* 注意防止溢出 */
        Merge_sort(arr, first, mid);
        Merge_sort(arr, mid+1,last);
        Merge(arr,first,mid,last);
    }
    return;
}

//基数排序，不用链式，链式太长，而且内存够使用用非链式

#define Max_ 200001      
//数组个数
#define  MAX_COUNT_OF_KET_IN_A_DATA 8  
//一个数据中最多的关键词个数


#define KEYNUM 10    
//关键字个数，这里为整形位数
//所以关键字是 0 1 2 3 4 5 6 7 8 9 
//lsf
static int radix = 0 ;

// 找到num的从  低   到    高   的第pos位的数据
int GetNumInPos(int num,int pos)
{
	int temp = 1;
	for (int i = 0 ; i < pos - 1; i++)
	{
        radix ++;
    	temp *= 10;
    }
	return ((num / temp) % 10);
}


//基数排序  array 无序数组；count_of_data为无序数据个数 

void RadixSort(int* array)
{
	int *radixArrays[KEYNUM];    //分别为0~9的序列空间
    int count_of_data = array [0];
    //[0]不用
	for (int i = 0; i < KEYNUM ; i++)
	{
		radixArrays[i] = (int *)malloc(sizeof(int) * ( array [0] + 1));
		radixArrays[i][0] = 0;    //index为0处记录这组数据的个数
	}
	
	for (int pos = 1; pos <= MAX_COUNT_OF_KET_IN_A_DATA ; pos++)    //从个位开始到6位
	{
        radix ++;

		for (int i = 1; i <= count_of_data ; i++)    //分配过程
		{
            radix ++;
			int num = GetNumInPos(array[i], pos);
            //num为array[i]在这里的关键字
			int index = ++radixArrays[num][0];
            //index为array[i] 在radixarray的位置
			radixArrays[num][index] = array[i];
		}
        
		for (int i = 0, j = 1; i < KEYNUM ; i++)    //收集
		{
            radix ++;
			for (int k = 1; k <= radixArrays[i][0]; k++)
			{
                radix ++ ;
                array[j++] = radixArrays[i][k];
            }
            radixArrays[i][0] = 0;    //复位
		}
	}
	for (int i = 0; i < KEYNUM ; i++)
	{
        free(radixArrays[i]);
	}
	
}

int main()
{
    int *array[10];
    int i,j;
    for (  i = 0; i < 10; i++)
    {
        array[i] = (int*)calloc(20001,sizeof(int));
        array[i][0] = 20000;
    }
    for ( i = 1; i <= array[0][0]; i++)
    {
        j = rand();
        array[0][i] = array[1][i] = array[2][i] = j;
        array[3][i] = array[4][i] = array[5][i] = j;
        array[6][i] = array[7][i] = array[8][i] = array[9][insert] = j;
    }
   //直接插入排序
    Insert(array[0]);
    for ( i = 1; i <= array[0][0]; i++)
    {
        printf("%d ",array[0][i]);
        if(i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n直接插入排序用了%d次\n\n",insert);
    //希尔排序
    int shell_sort[3] = {5,3,1};
    Shell_Sort(array[1],shell_sort,3);
    for ( i = 1; i <= array[1][0]; i++)
    {
        printf("%d ",array[1][i]);
        if(i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n希尔排序用了%d次\n\n",insert);
    //冒泡排序
    Bubble(array[2]);
    //快速排序
    Quick_Sort(array[3],1,20000);
    for ( i = 1; i <= array[3][0]; i++)
    {
        printf("%d ",array[3][i]);
        if(i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n快速排序用了%d次\n\n",quick);
    //选择排序
    Select(array[4]);    
    for ( i = 1; i <= array[4][0]; i++)
    {
        printf("%d ",array[4][i]);
        if(i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n选择排序用了%d次\n\n",select);
    //堆排序 
    HeapSort(array[5],20000);
    for ( i = 1; i <= array[5][0]; i++)
    {
        printf("%d ",array[5][i]);
        if(i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n堆拍排序用了%d次\n\n",heap);
    //归并排序 
    Merge_sort(array[6],1,20000);
    for ( i = 1; i <= array[6][0]; i++)
    {
        printf("%d ",array[6][i]);
        if(i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n归并排序用了%d次\n\n",merge);
    //链式基数排序
    RadixSort(array[7]);
    for ( i = 1; i <= array[7][0]; i++)
    {
        printf("%d ",array[7][i]);
        if(i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n基数排序用了%d次\n\n",radix);
    system("pause");
    return 0;
}