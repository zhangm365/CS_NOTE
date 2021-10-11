

// https://leetcode-cn.com/problems/house-robber-iii/
// 这次房子是二叉树结构

#include <bits/stdc++.h>


// 二叉树结构
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
        int rob(TreeNode *root);
        int rob2(TreeNode* root);
        std::vector<int> dp(TreeNode* root);

    private:
        std::map<TreeNode*, int> memo;

};


int Solution::rob(TreeNode *root)
{

    if(root == nullptr) return 0;

    // 此处定义会超时
    //std::map<TreeNode*, int> memo;

    // 利用备忘录消除重叠子问题
    std::map<TreeNode*, int>::iterator it = memo.find(root);
    if(it != memo.end())   //查找:找到了，则直接返回当前值，无需重复计算
        return it->second;

    //抢, 去下下家：根节点和四个孙子节点
    int do_it =  root->val + ( (root->left == nullptr) ? 0 : rob(root->left->left) + rob(root->left->right) )
                + ( (root->right == nullptr) ? 0 : rob(root->right->left) + rob(root->right->right) );

    //不抢，去下家：两个儿子节点
    int no_do = rob(root->left) + rob(root->right);

    int res = std::max(do_it, no_do);
    //插入map中
    memo.insert( std::pair<TreeNode*, int> (root, res) );

    return res; 

}


// 每个节点定义偷或不偷两种状态, ret[2]: 0:不偷, 1:偷
int Solution::rob2(TreeNode *root)
{

    if(root == nullptr) return 0;
    std::vector<int> ret(2);
    ret = dp(root);

    return std::max(ret[0], ret[1]);

}

std::vector<int> Solution::dp(TreeNode* root)
{

    if(nullptr == root) return {0, 0};

    std::vector<int> left(2), right(2);
    std::vector<int> ans(2);

    left = dp(root->left);
    right = dp(root->right);

    // ans[0]:不抢root
    ans[0] = std::max(left[0], left[1]) + std::max(right[0], right[1]);
    // 抢root
    ans[1] = root->val + left[0] + right[0];

    return ans;  

}