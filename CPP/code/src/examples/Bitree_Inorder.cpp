

//二叉树前中后序3种遍历的非递归算法

typedef struct BTnode * BinTree;
typedef BinTree Position;

struct BTnode
{
    int Data;   //数据域
    BinTree Left;   //左指针
    BinTree Right;  //右指针

};


//二叉树的前序非递归遍历
void PreOrderTraversal(BinTree BT) 
{
    BinTree T = BT;
    Stack S = CreateStack(MaxSize);     //创建并初始化堆栈
    while(T || !IsEmpty(S))
    {
        while(T)
        {
            //第一次遇到节点就访问输出
            printf("%2d", T->Data);    //先打印根节点
            Push(S, T);    //压栈
            T = T->Left;    //向左走
        }

        if(!IsEmpty(S))
        {
            T = Pop(S);    //出栈
            T = T->Right;               
        }
    }
}


//二叉树的中序非递归遍历
void InOrderTraversal(BinTree BT) 
{
    BinTree T = BT;
    Stack S = CreateStack(MaxSize);
    while(T || !IsEmpty(S))
    {
        while(T)
        {//一路向左将节点压入堆栈        
            Push(S, T);    //压栈
            T = T->Left;    //向左走
        }

        if(!IsEmpty(S))
        {
            T = Pop(S);    //出栈
            printf("%2d", T->Data);    //先打印根节点
            T = T->Right;               
        }
    }
}


//二叉树的后序非递归遍历
void PostOrderTraversal(BinTree BT) 
{
    BinTree T = BT;
    Stack S = CreateStack(MaxSize);
    BinTree r = NULL;   //节点访问标记指针
    while(T || !IsEmpty(S))
    {
        while(T)   //走到最左边
        {
            Push(S, T);
            T = T->Left;
        }
        if(!IsEmpty(S))
        {
            GetTop(S, T);   //取栈顶节点，但不出栈
            if(T->Right == NULL || T->Right == r)   //当前节点的右孩子为空或者已被访问过
            {
                printf("%2d", T->Data);
                r = Pop(S);     //已访问
            }
            else
            {
                T = T->Right;
            }
            
        }
        
    }
}