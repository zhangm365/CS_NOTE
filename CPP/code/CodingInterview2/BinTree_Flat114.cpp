

// https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/

// 将二叉树拉成单链表


#include <bits/stdc++.h>


//Definition for a binary tree node.

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

};

class Solution
{

    public:
        void flatten(TreeNode *root);

};


void Solution::flatten(TreeNode *root)
{

    if( !root ) return;

    //
    flatten(root->left);
    flatten(root->right);

    // 后序遍历
    // 1.左右子树已经被拉平
    TreeNode *left = root->left;
    TreeNode *right = root->right;

    // 2.左子树作为右子树
    root->left = nullptr;
    root->right = left;

    // 3.将原先的右子树接到当前右子树的末端
    TreeNode *p = root;

    while(p->right)
    {
        p = p->right;
    }

    p->right = right;

}