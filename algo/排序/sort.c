#include <stdio.h>

#define SORT_SUCCESS  0
#define SORT_FAILURE  1


int g_testcase1[]={0,1,2,3,8,7,6,5,4,9};
int g_testcase2[]={0,1,2,3,8,7,6,5,4,9};

typedef void (*pSortFun)(int arr[], int length);

int TestSort(pSortFun SortFun, int arr[], int length)
{
    if(arr == NULL || length == 0)
    {
        return SORT_FAILURE;
    }
    int i;
    printf("befor sort:");
    for(i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    SortFun(arr,length);
    
    printf("after sort:");
    for(i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    //is sort success
    for(i = 0; i < length-1; i++)
    {
        if(arr[i] > arr[i+1])
        {
            return SORT_FAILURE;
        }
    }
    return SORT_SUCCESS;
}

//排序算法性能测试
//产生一组随机数 1024*1024*1024*100  100M 的随机数
//统计统计排序时间

void CheckSortResult(int SortResult, char* FuncName)
{
    if(SortResult == SORT_SUCCESS)             
        {                                     
            printf("%s success\n", FuncName);    
        }                                    
        else 
        {
            printf("%s failure\n", FuncName); 
        }
    return;
}

int less(int a, int b)
{
    return a < b;
}

void exchange(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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
    int temp;
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

void main()
{   
    int iIsSort;
    iIsSort = TestSort(SelectSort, g_testcase1, 10);
    CheckSortResult(iIsSort, "SelectSort");

    iIsSort = TestSort(InsertSort, g_testcase2, 10);
    CheckSortResult(iIsSort, "InsertSort");
    return;
}
