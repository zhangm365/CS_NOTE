
// https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/
// 二叉树的序列化和反序列化



#include <bits/stdc++.h>

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

};



#if 0
// 前序遍历+队列实现

class Codec 
{
    public:

        // Encodes a tree to a single std::string.
        std::string serialize(TreeNode* root); 
        
        // Decodes your encoded data to tree.
        TreeNode* deserialize(std::string data); 

        // 辅助函数: 根据二叉树结构序列化为字符串
        void serial_build(TreeNode*root, std::string &res);

        // 辅助函数: 根据给定的序列重建二叉树
        TreeNode* rebuild(std::queue<std::string> &que);
       

};


// 将二叉树结构序列化
std::string Codec::serialize(TreeNode* root)
{

    if(!root) return "";

    std::string res;
    serial_build(root, res);
    return res;

}


//前序遍历访问二叉树，并将其结构序列化成字符串
void Codec::serial_build(TreeNode* root, std::string &res)
{
    
    if( !root ) 
    {
        res += "#,";
        return;
    }

    /********* 前序遍历位置************/
    res.append(std::to_string(root->val));
    res.push_back(',');
    /************************/

    serial_build(root->left, res);
    serial_build(root->right, res);

    //std::cout << "res = " << res << std::endl;
    

}


// Decodes your encoded data to tree.
TreeNode* Codec::deserialize(std::string data) 
{

    if( data == "" ) return nullptr;
    //std::cout << data << std::endl;
    
    // 将字符串存入到队列中
    std::queue<std::string> q;
    std::string str;
    
    
    for(int i=0; i < data.size(); i++)
    {
        if(data[i] == ',')
        {
            q.push(str);    //当前字符串压入队列
            str.clear();
        }
        else
            str.push_back(data[i]);
    }

    return rebuild(q);

}


TreeNode* Codec::rebuild(std::queue<std::string> &que)
{

    TreeNode* root; 

    //std::cout << "before:" << str << std::endl;
    std::string str = que.front();

    if( str == "#") 
    {
        que.pop();
        return nullptr;
    }
    
    root = new TreeNode();
    root->val = stoi(que.front());

    que.pop();
    
    root->left = rebuild(que);
    root->right = rebuild(que);

    return root;  

}


// 后序遍历+堆实现

class Codec 
{
    public:

        // Encodes a tree to a single std::string.
        std::string serialize(TreeNode* root); 
        
        // Decodes your encoded data to tree.
        TreeNode* deserialize(std::string data); 


        void build_serial(TreeNode* root, std::string &res);
        // 辅助函数: 根据给定的序列重建二叉树
        TreeNode *rebuild(std::stack<std::string> &st);

        
};



std::string Codec::serialize(TreeNode* root)
{

    std::string res;
    build_serial(root, res);

    return res;

}

void Codec::build_serial(TreeNode* root, std::string &res)
{

    if( !root ) 
    {
        res += "#,";
        return ;
    }

    build_serial(root->left, res);
    
    build_serial(root->right, res);

    // 后序遍历
    res.append(std::to_string(root->val));
    res.push_back(',');


}



// Decodes your encoded data to tree.
TreeNode* Codec::deserialize(std::string data) 
{

    if( data == "" ) return nullptr;
    
    std::stack<std::string> st;    //堆数据结构

    std::string str;
    
    for(int i=0; i < data.size(); i++)
    {
        if(data[i]==',')
        {
            st.push(str);
            str.clear();
        }
        else
            str.push_back(data[i]);
    }

    return rebuild(st);

}


TreeNode* Codec::rebuild(std::stack<std::string> &st)
{
       
    std::string str = st.top();
    if( str == "#") 
    {
        st.pop();
        return nullptr;
    }
    
    TreeNode* root;
    root = new TreeNode();
    root->val = stoi(st.top());

    st.pop();

    // 右子树 
    root->right = rebuild(st);
    // 左子树
    root->left = rebuild(st);
    
    
    return root;  

}
#endif


//层次遍历
class Codec 
{
    public:

        // Encodes a tree to a single std::string.
        std::string serialize(TreeNode* root); 
        
        // Decodes your encoded data to tree.
        TreeNode* deserialize(std::string data); 

        void build_serial(TreeNode* root, std::string &res);
        // 辅助函数: 根据给定的序列重建二叉树
        TreeNode *rebuild(std::vector<std::string> &v_Data);
       

};



std::string Codec::serialize(TreeNode* root)
{

    std::string res;
    build_serial(root, res);
    
    return res;

}

void Codec::build_serial(TreeNode* root, std::string &res)
{

    if( !root ) 
    {
        res = "";
        return ;
    }
 
    // *******层序遍历***********//

    //根节点入队
    std::queue<TreeNode*> que;
    que.push(root);
    
    while( !que.empty() )
    {

        TreeNode* cur = que.front();
        que.pop();

        if(cur == nullptr)
        {
            res.push_back('#');
            res.push_back(',');
            continue;
        }

        res.append(std::to_string(cur->val));
        res.push_back(',');

        que.push(cur->left);
        que.push(cur->right);
        
    }

}



// Decodes your encoded data to tree.
TreeNode* Codec::deserialize(std::string data) 
{

    if( data == "" ) return nullptr;
    //std::cout << data << std::endl;
    std::vector<std::string> newData;
    std::string str;
    
    for(int i = 0; i < data.size(); i++)
    {
        if(data[i] == ',')
        {
            newData.push_back(str);
            str.clear();
        }
        else
            str.push_back(data[i]);
    }

    return rebuild(newData);

}


TreeNode* Codec::rebuild(std::vector<std::string> &v_Data)
{
       
    if( v_Data.empty() ) 
    {
        return nullptr;
    }
  
    //根节点
    TreeNode* root = new TreeNode(stoi(v_Data[0]));

    // 队列：存储父节点
    std::queue<TreeNode*> que;
    que.push(root);
    
    
    int i = 1 ; // i为索引

    while( i < v_Data.size() )
    {

        TreeNode* parent = que.front();
        que.pop();

        // 左孩子
        std::string left = v_Data[i++];
        if(left != "#")
        {
            parent->left = new TreeNode(stoi(left));
            que.push(parent->left);
        }
        else
        {
            parent->left = nullptr;
        }
        
        // 右孩子
        std::string right = v_Data[i++];
        if( right != "#" )
        {
            parent->right = new TreeNode(stoi(right));
            que.push(parent->right);

        }
        else
        {
            parent->right = nullptr;

        }       
        
    }
    

    
    return root;  

}