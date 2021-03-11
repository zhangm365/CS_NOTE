# 1. 二叉树的层次遍历的另一种解法

题解：按层打印每一层节点



```c++

/*
class TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};*/

class TreePrinter {
public:
    vector<vector<int> > printTree(TreeNode* root) {
        // write code here
        if( !root ) return {};
        
        queue<TreeNode*> Q;
        TreeNode* p = root;
        Q.emplace(p);
        TreeNode* last = p;    // 每一层的最后一个节点
        TreeNode* nLast = nullptr;    //下一层的最后一个节点
        
        vector<int> sub;
        vector<vector<int> > res;
        
        while( !Q.empty() )
        {
            p = Q.front();
            Q.pop();
            sub.emplace_back(p->val);
            if(p->left)
            {
                Q.emplace(p->left);
                nLast = p->left;
            }
            if(p->right)
            {
                Q.emplace(p->right);
                nLast = p->right;
            }
            
            // 遍历到当前层的最后一个节点，则处理下一层
            if( last == p )
            {
                res.emplace_back(sub);
                sub.clear();
                last = nLast;
            }
            
        }
               
        return res;
         
    }
};
```

