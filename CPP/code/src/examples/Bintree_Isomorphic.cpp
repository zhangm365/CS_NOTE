

//判断两颗二叉树的是否为同构问题
/*
输入格式：

下标 8
0    A 1 2
1    B 3 4
2    C 5 -
3    D - -
4    E 6 -
5    G 7 -
6    F - -
7    H - -

*/


#include <iostream>

using namespace std;
#define Null -1

const int MaxSize = 20;

typedef char ElementType ;
typedef int Tree;

//结构数组表示二叉树
struct TreeNode
{
    ElementType data;    //数据域
    Tree left;
    Tree right;

}T1[MaxSize], T2[MaxSize];



//建立二叉树
Tree BuildTree(struct TreeNode T[]);

//二叉树同构问题
bool Bintree_Isomorphic(Tree R1, Tree R2);

int main()
{
    Tree B1, B2;
    //step1：建立二叉树
    B1 = BuildTree(T1);
    B2 = BuildTree(T2);

    //step2: 判断同构
    if(Bintree_Isomorphic(B1, B2))
        printf("Yes!\n");
    else
        printf("No!\n");


    return 0;
}

//建立二叉树
Tree BuildTree(struct TreeNode T[])
{
    int n;
    char cl, cr;
    int i;
    int check[MaxSize] = {0};
    Tree root = Null;
    scanf("%d", &n);
    getchar();  //吸收掉回车键
    for(i = 0; i < n; ++i)
    {

        scanf("%c %c %c", &T[i].data, &cl, &cr);
        getchar();  //继续吸收
        if(cl != '-')
        {
            //printf("cl = %c\n", cl);
            T[i].left = cl - '0';
            //printf("l = %d->%d\n", i, T[i].left);
            check[T[i].left] = 1;   //有节点指向
        }
        else
        {
            T[i].left = Null;    //左孩子为空
        }

        if(cr != '-')
        {
            //printf("cr = %c\n", cr);
            T[i].right = cr - '0';
            //printf("r = %d->%d\n", i, T[i].right);
            check[T[i].right] = 1;
        }
        else
        {
            T[i].right = Null;    //右孩子为空
        }
        
    }

    //查找根节点，哪一个下标对应的值没有标记为1，则为根节点
    for(i = 0; i < n; ++i)
    {
        if(!check[i])
        {
            root = i;
            break;
        }
        
    }

    return root;

}

//判断是否为同构
bool Bintree_Isomorphic(Tree R1, Tree R2)
{
    if(R1 == Null && R2 == Null)
    {//都为空
        return 1;
    }
    //其中一个为空
    if((R1==Null && R2!=Null) || (R1!=Null && R2==Null))
        return 0;
    //根不同
    if(T1[R1].data != T2[R2].data)
        return 0;
    //都没有左子树，判断右子树
    if(T1[R1].left == Null && T2[R2].left == Null)
        return Bintree_Isomorphic(T1[R1].right, T2[R2].right);
    
    //no need to swap the left and the right
    if ( ((T1[R1].left!=Null)&&(T2[R2].left!=Null))&&
    ((T1[T1[R1].left].data)==(T2[T2[R2].left].data)) )
        return ( Bintree_Isomorphic(T1[R1].left, T2[R2].left) &&
                Bintree_Isomorphic(T1[R1].right, T2[R2].right) );
    else /* need to swap the left and the right */
        return ( Bintree_Isomorphic(T1[R1].left, T2[R2].right) &&
                Bintree_Isomorphic(T1[R1].right, T2[R2].left) );
                
}