

// https://leetcode-cn.com/problems/maximum-binary-tree/

// 最大二叉树

#include <bits/stdc++.h>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(){}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){}

};


class Solution {
public:
    TreeNode* constructMaximumBinaryTree(std::vector<int>& nums);

    // 辅助函数
    TreeNode* buildTree(std::vector<int>& nums, int start, int end);
};

TreeNode* Solution::constructMaximumBinaryTree(std::vector<int>& nums)
{
    
    if(nums.empty()) return nullptr;

    return buildTree( nums, 0, nums.size()-1 );

}


TreeNode* Solution::buildTree(std::vector<int>& nums, int start, int end)
{

    if(start > end) return nullptr;

    int maxVal = INT_MIN;
    int mid = 0;

    // 找出区间中的最大值
    for( int i = start ; i <= end ; ++i )
    {

        if( maxVal < nums[i] )
        {
            maxVal = nums[i];
            mid = i;    //记录索引
        }

    }

    // 创建根节点
    TreeNode *root = new TreeNode(maxVal);
    
    // 递归左子树
    root->left = buildTree( nums, start, mid - 1 );
    // 递归右子树
    root->right = buildTree ( nums, mid+1, end );

    return root;

}