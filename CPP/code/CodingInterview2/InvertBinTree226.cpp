

// 翻转二叉树
// https://leetcode-cn.com/problems/invert-binary-tree/


# include <bits/stdc++.h>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr){}


};



class Solution
{

    public:
        TreeNode* invertTree(TreeNode *root);
        

};


TreeNode* Solution::invertTree(TreeNode *root)
{// 前序遍历或后序遍历

    if( !root ) return nullptr;

    // 左子树或右子树不为空
    if( root->left || root->right ) 
    {

        TreeNode *tmp = root->left;
        root->left = root->right;
        root->right = tmp;

    }
    
    invertTree(root->left);
    invertTree(root->right);

    return root;

}