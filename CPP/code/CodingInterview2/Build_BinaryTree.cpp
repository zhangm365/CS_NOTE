

//https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/
//输入某二叉树的前序和中序遍历，然后重建该二叉树。

#include <bits/stdc++.h>

using namespace std;

//二叉树的结点表示
struct TreeNode
{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL){}

};

class Solution {
    public:
        //哈希映射
        map<int, int> mp_order;
        
        TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) ;
        TreeNode* buildTree(vector<int>& preorder, int l1, int r1, vector<int>& inorder, int l2, int r2);

};


TreeNode* Solution::buildTree(vector<int> &preorder, vector<int> &inorder)
{
    
    int len = preorder.size();
    if(!len) return NULL;
    
    //将中序序列进行哈希映射
    for(int i = 0; i < len; ++i)
        mp_order[inorder[i]] = i;

    TreeNode* Root = buildTree(preorder, 0, len-1, inorder, 0, len-1);

    return Root;

}

TreeNode* Solution::buildTree(vector<int>& preorder, int l1, int r1, vector<int>& inorder, int l2, int r2)
{
    
    int len = preorder.size();

    if(!len) return NULL;
    
        
    TreeNode* Root = new TreeNode(preorder[l1]);
    //查找出根节点在中序序列中的位置
    int index = mp_order[preorder[l1]];

    int llen = index - l2;  //左子树长度
    int rlen = r2 - index;  //右子树长度

    //递归左子树
    if(llen)
        Root->left = buildTree(preorder, l1+1, l1+llen, inorder, l2, l2+llen-1);
    else
        Root->left = NULL;

    //递归右子树
    if(rlen)
        Root->right = buildTree(preorder, r1-rlen+1, r1, inorder, r2-rlen+1, r2);
    else
        Root->right = NULL;


    return Root;

}


void Inorder(TreeNode *BT)
{
    if(BT)
    {
        Inorder(BT->left);
        printf("%d ", BT->val);
        Inorder(BT->right);
    
    }

}


int main()
{

    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    
    Solution So;
    TreeNode *Root = So.buildTree(preorder, inorder);

    Inorder(Root);

    return 0;
}