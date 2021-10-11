
typedef struct BTnode * BinTree;

struct BTnode
{
    int Data;
    struct BTnode* Left;
    struct BTnode* Right;
};


//二叉树的层次遍历
void LevelOrderTraversal(BinTree BT)
{
    if(!BT) return;

    BinTree T = BT;
    Queue Q = CreateQueue(MaxSize);   //创建队列
    AddQ(Q, T);    //将根节点入队
    
    while(!IsEmpty(Q))
    {
        T = DeleteQ(Q);
        printf("%d", T->Data);
        
        if(T->Left)     //左孩子入队
            AddQ(Q, T->Left);
        if(T->Right)    //右孩子入队
            AddQ(Q, T->Right);
        
    }


}