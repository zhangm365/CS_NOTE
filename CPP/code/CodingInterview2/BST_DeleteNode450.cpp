

// https://leetcode-cn.com/problems/delete-node-in-a-bst/

// 删除BST中的一个节点

/*
    BST删除结点有3种情况：

    1.当要删除的结点是孩子节点时，这种情况最简单处理，即直接return nullptr；

    2.要删除的结点只有一个孩子(左孩子或右孩子)，那么就是直接让孩子节点替代当前节点；

    3.要删除的结点有左右孩子，那么为了保证BST的结构特性，有以下两种处理方式：

        找到左子树中的最大值来替代当前节点；
        找到右子树中的最小值来替代当前节点；


    我们采取右子树中的最小值来替代当前节点来操作，这种方式比较简单，因为右子树中的最小节点一定是最左边节点，所以只需一路向左遍历即可。

*/

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode( int x ) : val(x), left(nullptr), right(nullptr){}
};



class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int val);

    // 辅助函数: 查找右子树中最小的结点
    TreeNode* getMinNode(TreeNode *root);
    // 查找左子树中的最大节点
    TreeNode* getMaxNode(TreeNode *root);

};


TreeNode* Solution::deleteNode(TreeNode* root, int val)
{

    if( !root ) return nullptr;

    if( root->val == val )  //找到啦
    {

        // 情况1和2: 
        if(!root->left) return root->right;
        if(!root->right) return root->left;

        // 情况3: 左右孩子节点皆不为空，则用右子树中的最小节点值来替换当前节点值
        TreeNode* minNode = getMinNode(root->right);
        root->val = minNode->val;

        root->right = deleteNode(root->right, minNode->val);

    }
    else if( root->val > val )
    {

        root->left = deleteNode(root->left, val);

    }
    else if( root->val < val )
    {
        root->right = deleteNode(root->right, val);
    }
    
    return root;

}

// 查找右子树中的最小节点(最左节点)
TreeNode* Solution::getMinNode(TreeNode *root)
{

    if(!root) return nullptr;
    while(root && root->left)
        root = root->left;
    
    return root;

}

// 查找左子树中的最大节点（最右边节点）
TreeNode* Solution::getMaxNode(TreeNode *root)
{

    if(!root) return nullptr;
    while(root && root->right)
        root = root->right;
    
    return root;

}