
// https://leetcode-cn.com/problems/convert-bst-to-greater-tree/

// BST转化为累加树


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
        TreeNode* convertBST(TreeNode *root);
    
    private:
        int sum;


};


TreeNode* Solution::convertBST(TreeNode *root)
{

    if( !root ) return nullptr;

    // 先遍历右子树
    convertBST(root->right);

    //累加右子树中所有>=当前结点值之和
    sum += root->val;

    // 更新为累加树的结点值
    root->val = sum;

    //左子树
    convertBST(root->left);

    return root;

}