

// 二叉树的最小深度
// https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/


#include <bits/stdc++.h>


// 二叉树节点
struct TreeNode
{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode():val(0), left(nullptr), right(nullptr){}
    TreeNode(int x):val(x), left(nullptr), right(nullptr){}
    TreeNode(int x, TreeNode *left, TreeNode *right):val(x), left(left), right(right){}

};

class Solution
{

    public:
        /* 主函数:返回二叉树的最小深度 */
        int minDepth(TreeNode *BT);

};


// 广度优先遍历算法
int Solution::minDepth(TreeNode *BT)
{

    if(BT == nullptr)  // 空树高度为0
        return 0;

    // 队列
    std::queue<TreeNode* > Q;

    // 根节点本来就是一层, 深度为1
    Q.push(BT);
    int depth = 1;

    while(!Q.empty())
    {
        int sz = Q.size();

        // 将当前队列中的所有结点向四周扩散
        for(int i = 0 ; i < sz; ++i)
        {
            //返回队首节点
            TreeNode *Node = Q.front();
            // 出队
            Q.pop();

            // 重点： 判断是否到达终点
            if(Node->left == nullptr && Node->right == nullptr)    // 到达叶子节点
                return depth;
            if(Node->left)  // 左右孩子依次入队
                Q.push(Node->left);
            if(Node->right)
                Q.push(Node->right);


        }
        // 重点: 更新步数
        depth++;

    }

    return depth;

}

