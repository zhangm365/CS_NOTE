


//二叉搜索树的查找，插入和删除
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct BTNode *BinTree;
typedef BinTree Position;
struct BTNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); 
void InorderTraversal( BinTree BT ); 

BinTree BST_Insert( BinTree BST, ElementType X );
BinTree BST_Delete( BinTree BST, ElementType X );
Position BST_Search( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) 
    {
        scanf("%d", &X);
        BST = BST_Insert(BST, X);
    }

    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);

    for( i=0; i<N; i++ ) 
    {
        scanf("%d", &X);
        Tmp = BST_Search(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else 
        {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }

    }

    scanf("%d", &N);
    for( i=0; i<N; i++ ) 
    {
        scanf("%d", &X);
        BST = BST_Delete(BST, X);
    }

    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}

void PreorderTraversal(BinTree BST)
{//前序遍历
    if(BST)
    {
        printf("%d ", BST->Data);
        PreorderTraversal(BST->Left);
        PreorderTraversal(BST->Right);
    }

}


void InorderTraversal(BinTree BST)
{//中序遍历
    if(BST)
    {
        
        InorderTraversal(BST->Left);
        printf("%d ", BST->Data);
        InorderTraversal(BST->Right);
    }

}
//BST的查找 
BinTree BST_Search(BinTree BST, ElementType x)
{
    if(!BST) return NULL;

    if(x > BST->Data)   //大于到右边查找
        return BST_Search(BST->Right, x);
    else if(x < BST->Data)     //小于到左边查找
        return BST_Search(BST->Left, x);
    else    //找到了x == BST->Data
        return BST;
    
}


//BST的插入
BinTree BST_Insert(BinTree BST, ElementType x)
{
    if(!BST)    //二叉树为空
    {
        BST = (BinTree)malloc(sizeof(struct BTNode));
        BST->Data = x;
        BST->Left = BST->Right = NULL;
    }
    else
    {
        if(x > BST->Data)   //递归插入右子树
        {
            BST->Right = BST_Insert(BST->Right, x);
        }
        else if(x < BST->Data)
        {
            BST->Left = BST_Insert(BST->Left, x);
        }
    }
    
    return BST;

}

//查找BST中的值最小节点:二叉树中最左边的叶子节点
BinTree FindMin(BinTree BST)
{
    if(!BST) 
        return NULL;
    if(!BST->Left)
    {//找到最左叶节点
        return BST;
    }
    else
    {
        return FindMin(BST->Left);
    }
    
}

//查找BST中的值最大节点, 最右边的节点
BinTree FindMax(BinTree BST)
{
    if(!BST) 
        return NULL;
    if(!BST->Right)
    {//找到最左叶节点
        return BST;
    }
    else
    {
        return FindMax(BST->Right);
    }
    
}
//二叉树的删除
BinTree BST_Delete(BinTree BST, ElementType x)
{
    Position Tmp;

    if(!BST)    //二叉树为空
    {
        printf("%d is No Found\n", x);
    }
    else
    {
        if(x > BST->Data)   //递归从右子树中删除
        {
            BST->Right = BST_Delete(BST->Right, x);
        }
        else if(x < BST->Data)
        {
            BST->Left = BST_Delete(BST->Left, x);
        }
        else    //找到要删除的节点
        {
            if(BST->Left && BST->Right)    //被删除结点有左右子结点
            {//将要删除的结点有左右子树的情况转化为只有一个结点或无子节点的情况（用另一结点代替:右子树的最小元素或左子树的最大元素）

                Tmp = FindMin(BST->Right);  //先找到右子树的最小结点填充被删除的结点                   
                                
                BST->Data = Tmp->Data;
                //在删除结点的右子树中删除最小元素
                BST->Right = BST_Delete(BST->Right, BST->Data); 

                //
                // {//或者找左子树的最大结点来填充
                    
                //     Tmp = FindMax(BST->Left);
                //     BST->Data = Tmp->Data;
                //     BST->Left = BST_Delete(BST->Left, BST->Data); 
                // }                                    
            }
            else
            {
                Tmp = BST;
                if(!BST->Left)  //有右孩子或无子结点
                    BST = BST->Right;
                else if (!BST->Right)   //有左孩子或无子结点
                    BST = BST->Left;
               
                free(Tmp);
            }            
        
        }
        
    }
    
    return BST;
    
}