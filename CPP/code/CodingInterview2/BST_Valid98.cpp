


// https://leetcode-cn.com/problems/validate-binary-search-tree/

// 验证二叉搜索树的有效性：是否为BST

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode( int x ) : val(x), left(nullptr), right(nullptr){}
};



class Solution {
public:
    bool isValidBST(TreeNode* root);

    // 辅助函数: 对左右子树做限定 {增加函数参数列表，在参数中携带额外信息，将这种约束传递给子树的所有节点，这也是二叉树算法的一个小技巧吧}
    bool BST_Validate(TreeNode *root, TreeNode *min, TreeNode *max);

};


bool Solution::isValidBST(TreeNode *root)
{

    if( !root ) return true;

    return BST_Validate(root, nullptr, nullptr);

}


bool Solution::BST_Validate(TreeNode *root, TreeNode *min, TreeNode *max)
{

    if( !root ) return true;

    //root->val 大于等于左子树的结点值 && 小于等于右子树的结点值
    // max-val >= root->val >= min->val

    if( min && root->val <= min->val ) return false;
    if( max && root->val >= max->val ) return false;

    // 左子树的结点值均小于root值， 右子树的结点值均大于root值
    return ( BST_Validate( root->left, min, root ) && BST_Validate( root->right, root, max ) );
    

}