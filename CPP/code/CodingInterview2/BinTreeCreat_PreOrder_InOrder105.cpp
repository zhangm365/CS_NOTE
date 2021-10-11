

// https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
// 由前序和中序遍历重构二叉树


#include <bits/stdc++.h>

 
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution 
{
    // 前序遍历框架
    public:
        TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder);

    //辅助函数
    TreeNode* build(std::vector<int>& preorder, int l1, int r1, std::vector<int>& inorder, int l2, int r2);
};


TreeNode* Solution::buildTree( std::vector<int>& preorder, std::vector<int>& inorder )
{

    if( preorder.empty() || inorder.empty() ) return nullptr;

    return build( preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1 );

}

TreeNode* Solution::build( std::vector<int>& preorder, int l1, int r1, std::vector<int>& inorder, int l2, int r2 )
{

    if(l1 > r1 || l2 > r2) return nullptr;

    // step1:根节点信息处理
    // 1.建立根节点
    TreeNode *root = new TreeNode(preorder[l1]);

    // 2. 在中序遍历中找到根节点，将区间分为左右两部分
    int index = 0;

    for( int i = l2 ; i <= r2; ++i )
    {
        if( preorder[l1] == inorder[i])
        {// 找到了
            index = i;
            break;
        }
    
    }

    //左边长度
    int leftSize = index - l2;

    // step2:递归处理左右子树
    root->left = build( preorder, l1+1, l1+leftSize, inorder, l2, index-1 );
    root->right = build( preorder, l1+leftSize+1, r1, inorder, index+1, r2 );

    return root;

}