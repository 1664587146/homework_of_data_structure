#include<stdio.h>
#include<stdlib.h>
#define MAX_LENGTH 80
int Quick_Sort(int *array,int low ,int high);
int main()
{
    //x��0�����м���Ԫ��
	int Array_For_Quick_Sort[MAX_LENGTH + 1] = {0};
    int i;
    printf("��С����\n");
    printf("������������#��β:\n");
    for(i = 1 ; i <= MAX_LENGTH ; i++)
    {
        scanf("%d", &Array_For_Quick_Sort[i]);
        Array_For_Quick_Sort[0] ++;
        if(getchar() == '#')
        {
            break;
        }
    }
    Quick_Sort(Array_For_Quick_Sort,1,Array_For_Quick_Sort[0]);
    for ( i = 1; i <= Array_For_Quick_Sort[0]; i++)
    {
        printf("%d ",Array_For_Quick_Sort[i]);
    }
    printf("\n");    
    system("pause");
    return 0;
}

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
        array[low] = array [high];
        for (; high > low &&  array[low] <= pivotkey; low ++);
        array[high] = array [low];
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
}