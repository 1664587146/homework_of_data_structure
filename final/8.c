/*
    8�������㷨�Ƚ� ��������������
    [��������]
    ���������������10��������ÿ��������20000�������������ʹ��һ�����������򣬵ڶ������������򣩣�
    ����1 ֱ�Ӳ�������1 ϣ������1 ð������1 �������� 1 ѡ�����򡢶����� ���鲢���� �� ��������8�����򷽷���������
    �����Ϊ��С�����˳�򣩣���ͳ��ÿһ�������㷨�Բ�ͬ�������ķѵ�ʱ�䡣
    [����Ҫ��]
    ��1�� ԭʼ���ݴ����ļ��У�����ͬ�����Բ�ͬ�㷨���в��ԣ�
    ��2�� ��Ļ��ʾÿ�������㷨�Բ�ͬ����������ʱ�䣻
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
static int bubble = 0 ;//ʱ�����������ѭ������
int Bubble(int *array)
//ð������
{
    int k;
    for ( int i  = 1; i <= array[0]; i++)
    {
        //����ǰð
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
static int select = 0 ;//ʱ�����������ѭ������
int Select(int *array)
//ѡ������
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

static int insert = 0 ;//ʱ�����������ѭ������
int Insert(int *array)
//ֱ�Ӳ�������
{
    //��������Ƚ�����
    //total_number����ʾ�м���Ԫ��
    //insert��0�����ڱ�
    //��Ϊ���Ա�Ҫ�ƶ�������ֱ�ӴӺ���ǰ��
    int total_number,i,j,k;
    total_number = array[0];
    for (i = 2 ; i <= total_number ; i++)
    {
        //Ĭ��ǰi - 1���Ѿ������
        //i������
        array[0] = array[i];
        //�Ӻ���ǰ
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

static int quick = 0 ;//ʱ�����������ѭ������
//��������
int Partition(int *array , int low ,int high)
/*
    ����˳���L���ӱ�r��low ������ high ���ļ�¼�������¼��λ��������������λ��
    ��ʱ����֮ǰ���󣩵ļ�¼������С�ڣ���
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

// ϣ��
static int shell = 0 ;//ʱ�����������ѭ������
int Shell_Insert(int *array,int dk)//dk ��ÿ�μ��������
//��С
{
    //array[0]��������������ڱ�
    //array[0]��һ��������ǳ���
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
//��������
//�󶥶�
int HeapAdjust(int *array,int s,int m)//һ��ɸѡ�Ĺ���
{
    int rc,j;
    rc = array[s];
    for(j = 2 * s  ;  j <= m  ; j = j * 2)//ͨ��ѭ���ؽϴ�ĺ��ӽ������ɸѡ
    {
        heap ++;
        if(j < m && array[j] < array[j + 1]) //�ҵ�����Ԫ���нϴ���Ǹ�
            j ++;//jΪ�ϴ�ļ�¼���±�
        
        if(rc > array[j])//���������ѵĶѶ��� 
            break;

        array[s] = array[j];
        s = j;
    }
    array[s] = rc;//����
    //rc�ҵ�λ��
    return (6);
}
int HeapSort(int *array,int n)
{
    int temp,i,j;
    for(i = n / 2 ; i > 0 ; i -- )//ͨ��ѭ����ʼ������
    {
        heap ++;
        HeapAdjust(array,i,n);
    }

    for(i = n;i > 0;i -- )
    {
        heap ++;
        temp = array[1];
        array[1] = array[i];
        array[i] = temp;//���Ѷ���¼��δ��������һ����¼����
        //�����к����������
        HeapAdjust(array,1,i - 1);//���µ���Ϊ����
    }
    return (6);
}


//�鲢����
static int merge = 0;
void Merge(int arr[], int low, int mid, int high)
//�鲢
{
    int i, k;
    int *tmp = (int *)malloc((high-low+1)*sizeof(int));
    //����ռ䣬ʹ���СΪ����
    int left_low = low;
    int left_high = mid;
    int right_low = mid + 1;
    int right_high = high;

    for(k=0; left_low<=left_high && right_low<=right_high; k++)
    {  // �Ƚ�����ָ����ָ���Ԫ��
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
        //����һ��������ʣ�ֱ࣬�Ӹ��Ƴ���ճ���ϲ�����β
        //memcpy(tmp+k, arr+left_low, (left_high-left_low+l)*sizeof(int));
        for(i=left_low;i<=left_high;i++)
        {
            merge ++;
            tmp[k++] = arr[i];
        }
    }

    if(right_low <= right_high)
    {
        //���ڶ���������ʣ�ֱ࣬�Ӹ��Ƴ���ճ���ϲ�����β
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
        //������õĸ�ֵ��ȥ
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
         /* ע���ֹ��� */
        Merge_sort(arr, first, mid);
        Merge_sort(arr, mid+1,last);
        Merge(arr,first,mid,last);
    }
    return;
}

//�������򣬲�����ʽ����ʽ̫���������ڴ湻ʹ���÷���ʽ

#define Max_ 200001      
//�������
#define  MAX_COUNT_OF_KET_IN_A_DATA 8  
//һ�����������Ĺؼ��ʸ���


#define KEYNUM 10    
//�ؼ��ָ���������Ϊ����λ��
//���Թؼ����� 0 1 2 3 4 5 6 7 8 9 
//lsf
static int radix = 0 ;

// �ҵ�num�Ĵ�  ��   ��    ��   �ĵ�posλ������
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


//��������  array �������飻count_of_dataΪ�������ݸ��� 

void RadixSort(int* array)
{
	int *radixArrays[KEYNUM];    //�ֱ�Ϊ0~9�����пռ�
    int count_of_data = array [0];
    //[0]����
	for (int i = 0; i < KEYNUM ; i++)
	{
		radixArrays[i] = (int *)malloc(sizeof(int) * ( array [0] + 1));
		radixArrays[i][0] = 0;    //indexΪ0����¼�������ݵĸ���
	}
	
	for (int pos = 1; pos <= MAX_COUNT_OF_KET_IN_A_DATA ; pos++)    //�Ӹ�λ��ʼ��6λ
	{
        radix ++;

		for (int i = 1; i <= count_of_data ; i++)    //�������
		{
            radix ++;
			int num = GetNumInPos(array[i], pos);
            //numΪarray[i]������Ĺؼ���
			int index = ++radixArrays[num][0];
            //indexΪarray[i] ��radixarray��λ��
			radixArrays[num][index] = array[i];
		}
        
		for (int i = 0, j = 1; i < KEYNUM ; i++)    //�ռ�
		{
            radix ++;
			for (int k = 1; k <= radixArrays[i][0]; k++)
			{
                radix ++ ;
                array[j++] = radixArrays[i][k];
            }
            radixArrays[i][0] = 0;    //��λ
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
   //ֱ�Ӳ�������
    Insert(array[0]);
    for ( i = 1; i <= array[0][0]; i++)
    {
        printf("%d ",array[0][i]);
        if(i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\nֱ�Ӳ�����������%d��\n\n",insert);
    //ϣ������
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
    printf("\n\nϣ����������%d��\n\n",insert);
    //ð������
    Bubble(array[2]);
    //��������
    Quick_Sort(array[3],1,20000);
    for ( i = 1; i <= array[3][0]; i++)
    {
        printf("%d ",array[3][i]);
        if(i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n������������%d��\n\n",quick);
    //ѡ������
    Select(array[4]);    
    for ( i = 1; i <= array[4][0]; i++)
    {
        printf("%d ",array[4][i]);
        if(i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\nѡ����������%d��\n\n",select);
    //������ 
    HeapSort(array[5],20000);
    for ( i = 1; i <= array[5][0]; i++)
    {
        printf("%d ",array[5][i]);
        if(i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n������������%d��\n\n",heap);
    //�鲢���� 
    Merge_sort(array[6],1,20000);
    for ( i = 1; i <= array[6][0]; i++)
    {
        printf("%d ",array[6][i]);
        if(i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n�鲢��������%d��\n\n",merge);
    //��ʽ��������
    RadixSort(array[7]);
    for ( i = 1; i <= array[7][0]; i++)
    {
        printf("%d ",array[7][i]);
        if(i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n������������%d��\n\n",radix);
    system("pause");
    return 0;
}