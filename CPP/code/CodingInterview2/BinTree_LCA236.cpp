



// https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/
// 二叉树的最近公共祖先

#include <bits/stdc++.h>


struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

};

/*************base case****************
    * 二叉树为空，则返回null；
    * 当递归过程中root等于p或q的任何一个节点，则立即返回当前节点，否则再递归下去会返回null
    * 
****/



/************递归情况********************
// 1. 若p和q都在二叉树中，则函数返回他们的最近公共祖先节点, 即当前递归过程中的root是最近祖先节点;
// 2. 若p和q都不在二叉树中, 则返回null;
// 3. 若p或q只有一个在二叉树中, 则返回p或q自身节点;

  其实case 2 和 3 可以和二为一

****/

class Solution
{
    public:

        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);

};



TreeNode* Solution::lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{

    // base case
    // 1
    if( !root ) return nullptr;
    // 2
    if( root == q || root == p) return root;

    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);

    // ***后序遍历的位置***//
    // case 1: 
    if( left != nullptr && right != nullptr ) 
        return root;
    
    /* 解法1
    // case 2:
    if( left == nullptr && right == nullptr )
        return nullptr;
    // case 3:
    return left == nullptr ? right : left;
    */

   /********解法2*********/

    return left ? left : right;


    
}