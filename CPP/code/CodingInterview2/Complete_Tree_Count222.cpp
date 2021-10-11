

// https://leetcode-cn.com/problems/count-complete-tree-nodes/
// 完美二叉树的结点个数


#include <bits/stdc++.h>


/**
 * Definition for a binary tree node. 
 * */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution 
{
    public:
        int countNodes(TreeNode* root) 
        {
            
            TreeNode *pl = root, *pr = root;
            int lh = 0, rh = 0;

            //左子树高度
            while(pl)
            {
                pl = pl->left;
                lh++;
            }

            // 右子树高度
            while(pr)
            {
                pr = pr->right;
                rh++;
            }

            // 左右子树高度相同，则为满二叉树，结点个数为2^h-1;
            if( lh == rh )
            {
                return pow(2, rh) - 1;
            }

            // 否则用普通二叉树的计算节点个数方法返回：后序遍历的递归方法
            return 1 + countNodes(root->left) + countNodes(root->right);

        }

};