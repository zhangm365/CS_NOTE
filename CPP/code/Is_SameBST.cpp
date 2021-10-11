/*

给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，
一棵给定的二叉搜索树却可以由多种不同的插入序列得到。
 例如，按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，
都得到一样的结果。
 问题：对于输入的各种插入序列，你需要判断它们是否能
生成一样的二叉搜索树。


例子：如何判别序列3 2 4 1是否 与树T(3 1 2 4)一致？
方法：在树T中按顺序搜索序列3 2 4 1中的每个数
 如果每次搜索所经过的结点在前面均出现过，则一致
 否则（某次搜索中遇到前面未出现的结点），则不一致
*/


//由给定的几个序列判断是否为同一棵二叉搜索树
//思路:1.根据给定的输入序列建立BST树, 然后依据树T判断后面的N个序列是否和T是同一颗二叉树


#include <iostream>
using namespace std;

typedef struct BTnode *BinTree;

typedef int ElementType;

struct BTnode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
    int flag;   //标记位, 标记该节点是否被访问过
};


//建立搜索树
BinTree CreateBST(BinTree BT, ElementType x);

//判断序列是否和BST为同一颗搜索树
int Judge(BinTree BT, int n);

//重置BT中的flag为0
void ResetT(BinTree BT);

//释放生成的搜索树BT
void FreeTree(BinTree BT);
void InorderTraversal(BinTree BST)
{//中序遍历
    if(BST)
    {
        
        InorderTraversal(BST->Left);
        printf("%d ", BST->Data);
        InorderTraversal(BST->Right);
    }

}

int main()
{
    //1.处理输入数据, 建立二叉搜索树
    BinTree BT = NULL;
    int N, M, i;   //N为初始给定序列的节点数
    scanf("%d%d", &N, &M);  //M：待比较序列的个数
    
    int v;
    while(N)
    {
    
        //建立二叉搜索树
        for(i = 0; i < N; ++i)
        {
            scanf("%d", &v);
            BT = CreateBST(BT, v);  
        }
        // printf("Inorder:");
        // InorderTraversal(BT);
        // printf("\n");

        //2.判断后续输入的序列是否和BT为同一颗二叉树
        while(M--)
        {
            if(Judge(BT, N)) 
                printf("Yes\n");
            else 
                printf("No\n");

            ResetT(BT);    //重置BT中的flag=0

        }

        
        FreeTree(BT);
        BT = NULL;
        scanf("%d%d", &N, &M);

    }


    return 0;
}


//建立搜索树T
BinTree CreateBST(BinTree BT, ElementType x)
{
    if(!BT)
    {
        BT = (BinTree)malloc(sizeof(struct BTnode));
        BT->Data = x;
        BT->Right = BT->Left = NULL;
        BT->flag = 0;
    }
    else 
    {
        if(x < BT->Data) 
            BT->Left = CreateBST(BT->Left, x);
        else if(x > BT->Data)
            BT->Right = CreateBST(BT->Right, x);
    }
 
    return BT;
}


int check ( BinTree BT, ElementType x )
{//判断搜索树的一个节点是否被访问过
    if ( BT->flag ) 
    {
        if ( x < BT->Data ) return check(BT->Left, x);
        else if ( x > BT->Data ) return check(BT->Right, x);
        else return 0;
    }
    else 
    {//当前节点第一次访问
        if ( x == BT->Data ) 
        {
            BT->flag = 1;
            return 1;
        }
        else 
            return 0;
    }

}

//判断是否一致
int Judge(BinTree BT, int n)
{
    int i, V, flag = 0;     /* flag: 0代表目前还一致， 1代表已经不一致*/
    scanf("%d", &V);
    if ( V != BT->Data ) flag = 1;  //首先和根节点比较
    else BT->flag = 1;

    for (i = 1; i < n; i++) 
    {
        scanf("%d", &V);
        if ( (!flag) && (!check(BT, V)) ) 
            flag = 1;
    }

    if (flag) return 0;
    else return 1;

}


void ResetT(BinTree BT)     //清除树BT中各个节点的flag标记
{
    if(BT)
    {
        ResetT(BT->Left);
        ResetT(BT->Right);
        BT->flag = 0;
    }

}

void FreeTree(BinTree BT)     //释放树BT中各个节点的空间
{
    if(BT)
    {
        FreeTree(BT->Left);
        FreeTree(BT->Right);
        free(BT);
    }
}