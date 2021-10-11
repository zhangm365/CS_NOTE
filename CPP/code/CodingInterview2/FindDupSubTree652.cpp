

//https://leetcode-cn.com/problems/find-duplicate-subtrees/

// 寻找重复的子树
// 1. 以我为根节点的二叉树长什么样;
// 2. 以其他节点为根的二叉树长啥样

#include <bits/stdc++.h>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(){}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){}

};


class Solution
{

    public:
        std::vector<TreeNode*> findDuplicateSubtrees(TreeNode *root);

        // 辅助函数: 用拼接字符串的方式将二叉树结构序列化
        std::string traverse(TreeNode *root);

    private:
        std::unordered_map<std::string, int> demo;      //记录每个子树结构字符串序列和它出现的次数
        std::vector<TreeNode*> res;     //记录重复子树的根节点信息

};


std::vector<TreeNode*> Solution::findDuplicateSubtrees(TreeNode *root)
{

    if( !root ) return {};

    traverse(root);

    return res;

}

// 将二叉树结构字符串序列化，然后查找出重复的结点
std::string Solution::traverse(TreeNode *root)
{
    
    if(!root) return "#";

    std::string subtree;   

    std::string left = traverse(root->left);
    std::string right = traverse(root->right);

    /* 后序遍历的位置 */

    //将二叉树结构->字符串序列化 :左右根
    char ch_root = root->val + '0';
    subtree = left + "," + right + "," + ch_root;

    //printf("str = %s\n", subtree.c_str());

    // 方法1
    if( demo.count(subtree) )   //在第二次遇到相同的元素，count()方法就返回1
    {   
        //记录次数
        demo[subtree]++;

        //将二叉树结构的字符串序列加入集合中
        // std::pair<std::string, int> tmptree(subtree, demo[subtree]);
        // demo.insert(tmptree);

    }
    
    if ( demo[subtree] == 1 )   //[]: 若当前元素不存在时，会自动插入一个访问元素，并返回一个mapped_type值
    {   
        //没有重复，则加入目标列表中
        res.push_back(root);
        
    }

    
    
    /* 方法2
    
    //std::pair<std::unordered_map<std::string, int>::iterator, bool> ret = demo.emplace(subtree, 0);
    auto ret = demo.emplace(subtree, 0);
    
    //printf("%d %d\n", ret.second, demo[subtree]);
    
    if(!ret.second) // 没有插入成功
    {
        demo[subtree]++;
        if(demo[subtree] == 1)
            res.push_back(root);

    }

    */

    return subtree;

}