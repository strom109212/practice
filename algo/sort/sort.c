#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SORT_SUCCESS  0
#define SORT_FAILURE  1
#define MAX_ARRAY_LEN 1024
#define FALSE 0
#define TRUE 1

int g_testcase1[]={0,1,2,3,8,7,6,5,4,9};
int g_testcase2[]={2,1,0,3,8,7,6,5,4,9,11,19,18,17,16,10,13,12,14,15};
//auxiliary array
int g_iAuxArr[MAX_ARRAY_LEN];


typedef void (*pSortFun)(int arr[], int length);

int TestSort(pSortFun SortFun, int arr[], int length)
{
    if(SortFun ==NULL || arr == NULL || length == 0)
    {
        return SORT_FAILURE;
    }
    
    int* pTempArr = malloc(sizeof(int)*length);
    if(pTempArr == NULL)
    {
        return SORT_FAILURE;
    }
    memcpy(pTempArr, &arr[0], sizeof(int)*length);

    int i;
    printf("befor sort:");
    for(i = 0; i < length; i++)
    {
        printf("%d ", pTempArr[i]);
    }
    printf("\n");
    
    SortFun(pTempArr,length);
    
    printf("after sort:");
    for(i = 0; i < length; i++)
    {
        printf("%d ", pTempArr[i]);
    }
    printf("\n");

    //is sort success
    for(i = 0; i < length-1; i++)
    {
        if(pTempArr[i] > pTempArr[i+1])
        {
            free(pTempArr);
            return SORT_FAILURE;
        }
    }
    free(pTempArr);
    return SORT_SUCCESS;
}

//�����㷨���ܲ���
//����һ������� 1024*1024*1024*100  100M �������
//ͳ������ʱ��

void CheckSortResult(int SortResult, char* FuncName)
{
    if(SortResult == SORT_SUCCESS)             
    {                                     
        printf("exec %s success\n\n", FuncName);    
    }                                    
    else 
    {
        printf("exec %s failure\n\n", FuncName); 
    }
    return;
}

void exchange(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void BubbleSort(int arr[], int length)
{
    int i, j;
    int NotSorted = TRUE;
    for(i = 0; i < length -1 && NotSorted; i++)
    {
        NotSorted = FALSE;
        for(j = length-2; j >= i; j--)
        {
            if(arr[j] > arr[j+1])
            {
                NotSorted = TRUE;
                exchange(&arr[j], &arr[j+1]);  
            }
        }
    }
    return;
}

void SelectSort(int arr[], int length)
{
    int i, j;
    int minIndex;
    for(i = 0; i < length; i++)
    {
        minIndex = i;
        for(j = i+1; j < length; j++)
        {
            if(arr[minIndex] > arr[j])
            {
                minIndex = j;
            }
        }
        exchange(&arr[i], &arr[minIndex]);  
    }
    return;
}

void InsertSort(int arr[], int length)
{
    int i,j;
    for(i = 1; i < length; i++)
    {
        for(j = i; j > 0; j--)
        {
            if(arr[j] < arr[j-1])
            {
                exchange(&arr[j], &arr[j-1]);
            }
        }
    }
    return;
}

//  ����  ����:
//  �㷨  ˵��:
//  ʱ�临�Ӷ�:
//  �ռ临�Ӷ�:
//  ��      ��:��
//  Ӧ��  ����:
//
void ShellSort(int arr[], int length)
{
    int i, j;
    //������ʹ�����������ÿһ���������ȵ�С��������
    int increment = length;
    while(increment > 1)
    {
        increment = increment/3 + 1;
        for(i = increment; i < length; i++)
        {
            if( arr[i] < arr[i- increment])
            {
                //��Ծʽ�ƶ�
                for(j = i; j >= increment; j-=increment)
                {
                    if(arr[j] < arr[j - increment])
                    {
                        exchange(&arr[j], &arr[j - increment]);
                    }
                }
            }
        }
    }
    return;
}

//MergeSort
static void Merge(int arr[], int low, int mid, int high)
{   
    int i,j,k;
    i = low, j = mid+1;
    for(k = low; k <= high; k++)
    {
        g_iAuxArr[k] = arr[k];
    }
    
    for(k = low; k <= high; k++)
    {  
        if (i > mid) arr[k] = g_iAuxArr[j++];
        else if (j > high) arr[k] = g_iAuxArr[i++];
        else if(g_iAuxArr[i] < g_iAuxArr[j]) arr[k] = g_iAuxArr[i++];
        else arr[k] = g_iAuxArr[j++];
    }
}
static void MergeSort_ex(int arr[], int low,int  high)
{
    if(high <= low)
        return;
    int mid = low+(high -low)/2;
    MergeSort_ex(arr, low, mid);
    MergeSort_ex(arr, mid+1, high);
    Merge(arr, low, mid, high);
    return;
}
void MergeSort(int arr[], int length)
{
    MergeSort_ex(arr, 0, length -1);
    return;
}

static int partition(int arr[], int lo, int hi)
{
    int i = lo;
    int j = hi+1; //������1�� ����ѭ���ȼ�ȥ1�ٱȽ�
    int v = arr[lo];

    while(1)
    {  
        while(arr[++i] < v)
        {
            if(i == hi)
                break;
        }
        while(v < arr[--j])
        {
            if(j == lo)
                break;
        }

        if(i >= j)
            break;
        exchange(&arr[i], &arr[j]);
    }
    exchange(&arr[lo], &arr[j]);
    return j;
}

static void quick_sort(int arr[], int lo, int hi)
{
    if(lo >= hi)
        return;
    int mid = partition(arr, lo, hi);
    quick_sort(arr,lo, mid - 1);
    quick_sort(arr, mid+1, hi);
    return;
}

void QuickSort(int arr[], int length)
{
    quick_sort(arr, 0, length -1);
    return;
}


void main()
{   
    int iIsSort;
    iIsSort = TestSort(BubbleSort, g_testcase2, 20);
    CheckSortResult(iIsSort, "BubbleSort");
    
    iIsSort = TestSort(SelectSort, g_testcase1, 10);
    CheckSortResult(iIsSort, "SelectSort");

    iIsSort = TestSort(InsertSort, g_testcase1, 10);
    CheckSortResult(iIsSort, "InsertSort");

    iIsSort = TestSort(ShellSort, g_testcase2, 20);
    CheckSortResult(iIsSort, "ShellSort");
    
    iIsSort = TestSort(MergeSort, g_testcase2, 20);
    CheckSortResult(iIsSort, "MergeSort");

    iIsSort = TestSort(QuickSort, g_testcase2, 20);
    CheckSortResult(iIsSort, "QuickSort");
    return;
}
