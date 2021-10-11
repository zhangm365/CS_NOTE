

//最大堆的相关操作:建堆, 堆的插入, 堆的删除等

#include <iostream>

const int MaxEleHeap = 1000;

typedef struct HNode * MaxHeap;
typedef int ElementType;

struct HNode
{
    ElementType *EleHeap;   //存储堆元素的数组
    int Size;   //堆的当前元素的个数
    int Capacity;   //堆的最大容量
};

//最大堆的建立
MaxHeap CreateHeap(int n)
{//建立容量为n的空的最大堆

    MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
    H->EleHeap = (ElementType *)malloc((n+1)*sizeof(ElementType));
    H->Capacity = n;
    H->Size = 0;
    //定义"哨兵"为大于堆中所有可能元素的值, 以提高效率
    H->EleHeap[0] = MaxEleHeap;

    return H;

}

//判断最大堆是否已满
bool IsFull(MaxHeap H)
{
    return (H->Size == H->Capacity);
   
}

//判断最大堆是否为空
bool IsEmpty(MaxHeap H)
{
    return (H->Size == 0);
    
}

//新增节点到最大堆中
bool Insert(MaxHeap H, ElementType x)
{//将元素x插入到最大堆中

    if(IsFull(H))
    {
        printf("最大堆已满!\n");
        return false;
    }

    int i;
    i = ++H->Size;    //i指向插入后堆中的最后一个元素的位置

    for( ; H->EleHeap[i/2] < x; i/=2)
    {
        H->EleHeap[i] = H->EleHeap[i/2];    //向下过滤结点
    }

    H->EleHeap[i] = x;    //将x插入堆中

    return true;

}


//最大堆的删除
ElementType DeleteHeap(MaxHeap H)
{//从最大堆H中取出键值最大的元素, 并删除一个结点

    int Parent, Child;
    if(IsEmpty(H))
    {
        printf("最大堆已空!\n");
        return -1;
    }

    ElementType MaxItem, temp;
    MaxItem = H->EleHeap[1];    //取出根结点的最大值
    temp = H->EleHeap[H->Size--];   //取出最后一个元素, 并将当前数组中元素的个数减1

    for(Parent = 1; Parent*2 <= H->Size; Parent = Child)
    {//用最大堆中的最后一个元素从根结点开始向上过滤下层结点
        Child = Parent*2;
        //找出当前结点的左右孩子中的最大结点
        if ((Child != H->Size) && (H->EleHeap[Child] < H->EleHeap[Child+1]))
        {
            Child++;
        }

        if(temp >= H->EleHeap[Child]) 
            break;
        else        
            H->EleHeap[Parent] = H->EleHeap[Child];
        

    }

    H->EleHeap[Parent] = temp;

    return MaxItem;

}

/*----------- 建造最大堆 -----------*/
void PercDown( MaxHeap H, int p )
{ /* 下滤：将H中以H->EleHeap[p]为根的子堆调整为最大堆 */
    int Parent, Child;
    ElementType X;
 
    X = H->EleHeap[p]; /* 取出根结点存放的值 */
    for( Parent = p; Parent*2 <= H->Size; Parent = Child ) 
    {
        Child = Parent * 2;
        if( (Child!=H->Size) && (H->EleHeap[Child] < H->EleHeap[Child+1]) )
            Child++;  /* Child指向左右子结点的较大者 */
        if( X >= H->EleHeap[Child] ) 
            break; /* 找到了合适位置 */
        else  /* 下滤X */
            H->EleHeap[Parent] = H->EleHeap[Child];
    }

    H->EleHeap[Parent] = X;

}
 
void BuildHeap( MaxHeap H )
{ /* 调整H->EleHeap[]中的元素，使满足最大堆的有序性  */
  /* 这里假设所有H->Size个元素已经存在H->EleHeap[]中 */
 
    int i;
 
    /* 从最后一个结点的父节点开始，到根结点1 */
    for( i = H->Size/2; i > 0; i-- )
        PercDown( H, i );
}