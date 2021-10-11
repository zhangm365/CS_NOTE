

/*
    将一系列给定数字插入一个初始为空的小顶堆H[]。随后对任意给
    定的下标`i`，打印从H[i]到根结点的路径。
*/

#include <iostream>


using namespace std;

typedef int ElementType;

typedef struct HNode *MinHeap;

const int MaxSize = 20;


struct HNode
{
    ElementType *Data;
    int Size;   //数组中元素个数
    int Capacity;   //数组的最大容量

};


//建立最小堆：容量为MaxSize的空的最小堆
MinHeap CreateHeap(int MaxSize)
{

    MinHeap H;
    H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType *)malloc(sizeof(int)*(MaxSize+1));
    H->Capacity = MaxSize;
    H->Size = 0;

    return H;

}


void InsertHeap(MinHeap H, ElementType x)
{//将元素x插入到最小堆中

    int i;
    i = ++H->Size;  //i指向插入元素位置的下标
    for(; i>1 && H->Data[i/2] > x; i/=2)
    {
        H->Data[i] = H->Data[i/2];
    }

    H->Data[i] = x;

}


void Print_Path(MinHeap H, ElementType m)
{
    int i;
    printf("%d", H->Data[m]);
    for(i = m/2; i>=1; i/=2)
    {
        printf(" %d", H->Data[i]);
    }
    printf("\n");

}



int main()
{
     int n, m;
     scanf("%d %d", &n, &m);
     int i;
     int x;
     MinHeap H;
     H = CreateHeap(MaxSize);
     
     for(i = 0; i < n; ++i)
     {
        scanf("%d", &x);
        InsertHeap(H, x);
     }

    // for(i = 1; i <=n; ++i)
    // {
    //     printf("%d ", H->Data[i]);
    // }
    // printf("\n");

    for(i = 0; i < m; ++i)
    {
        scanf("%d", &x);
        Print_Path(H, x);
    }

    return 0;
}