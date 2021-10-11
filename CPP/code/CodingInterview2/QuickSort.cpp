

//快速排序
#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

class CQuickSort
{

    public:
        void QuickSort(vector<int> &arr, int start, int end);
        int Partition(vector<int> &arr, int start, int end);
        int RandomInRange(int start, int end);

};

int CQuickSort::RandomInRange(int start, int end)
{
    //printf("end-start = %d\n", end-start);
    return rand() % (end - start + 1) + start;

}


int CQuickSort::Partition(vector<int> &arr, int start, int end)
{//划分，一趟排序

    if(start < 0 || start > end) return -1;

    //产生一个随机数
    int index = RandomInRange(start, end);
    //printf("---rand = %d\n", index);
    
    swap(arr[index], arr[end]); //将最后一个元素作为枢轴元素

    int small = start - 1;  //small指向第一个大于枢轴元素的位置

    for( int index = start; index < end; ++index )
    {
        if(arr[index] < arr[end])
        {
            ++small;
            if(small != index)
            {                
                swap(arr[small], arr[index]);
            }
        }
    }

    ++small;
    swap(arr[small], arr[end]);
    
    return small;

}


void CQuickSort::QuickSort(vector<int> &arr, int start, int end)
{

    if(arr.empty()) return ;
    
    int index = Partition(arr, start, end);
    
    //printf("+++Par = %d\n", index);
    if(start < index)
    {
        QuickSort(arr, start, index - 1);
        
    }

    if(index < end)
    {
        QuickSort(arr, index + 1, end);
        
    }


}


int main()
{

    int n, x;
    vector<int> arr;
    printf("Please input the N: ");
    scanf("%d", &n);


    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        arr.push_back(x);
    }

    srand((unsigned)time(NULL));

    CQuickSort Qsort;
    Qsort.QuickSort(arr, 0, n-1);

    for(int i = 0; i != arr.size(); ++i)
    {
        if(i != 0) printf(" ");
        printf("%d",arr[i]);           

    }

    printf("\n");

    return 0;

}