

// https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node/

// 填充每个节点的下一个右侧节点指针

# include <bits/stdc++.h>


// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
public:
    Node* connect(Node* root);

    // 连接两个相邻节点（相同节点或不同节点）间的指针
    void connectTwoNode(Node* node1, Node* node2);

};


Node* Solution::connect(Node* root)
{

    if( !root ) return nullptr;
    root->next = nullptr;

    connectTwoNode(root->left, root->right);
    return root;
}


// 定义为两个相邻节点的连接问题
void Solution::connectTwoNode(Node *node1, Node *node2)
{

    if( !node1 || !node2 ) return ;

    // 前序遍历
    node1->next = node2;

    // 连接相同父节点的指针
    connectTwoNode( node1->left, node1->right );
    connectTwoNode( node2->left, node2->right );

    // 连接跨越父节点的两个结点之间的指针
    connectTwoNode( node1->right, node2->left );
    

}