


// 并查集的相关算法: 图论中的动态连通性

#include <bits/stdc++.h>

class Union_Find
{

    public:
        // 构造函数, n为图中结点总数
        Union_Find( int n );
        
        // 连通两个结点
        void two_union( int p, int q );

        // 判断两个节点是否连通
        bool connected( int p, int q );

        // 查找node节点的父节点
        int par_find(int node);

        // 树中连通分量
        int con_count() const
        {
            return count;
        }

    private:
        // 记录连通分量
        int count;
        // 结点x的结点是 parent[x]
        std::vector<int> parent;

        // 记录每个树中含有的结点数, 称为"重量"
        std::vector<int> weight;

};

Union_Find::Union_Find( int n )
{
    // 连通分量为n
    this->count = n;

    // 父节点指针指向它自己
    parent.resize(n);
    weight.resize(n);

    for( int i = 0; i < n; ++i)
    {
        //i的结点是parent[i], 即都指向自己
        parent[i] = i;
        // 每个树中只包含自己
        weight[i] = 1;
    }
    
}


// 连通两个节点
void Union_Find::two_union( int p, int q )
{

    int pr = par_find(p);
    int qr = par_find(q);
    if (pr == qr) return ;

    // 合并成一棵树, 小树接到大树下面，以实现更加树结构的"平衡化"
    if( weight[pr] < weight[qr] )
    {
        parent[pr] = qr;
        weight[qr] += weight[pr]; 
    }    
    else
    {
        parent[qr] = pr;
        weight[pr] += weight[qr]; 
    }
    
    // 连通分量--
    count--;

}

// 判断两个节点是否连通
bool Union_Find::connected( int p, int q )
{

    int pr = par_find(p);
    int qr = par_find(q);

    return pr == qr;

}


// 返回某个节点的根节点
int Union_Find::par_find( int p )
{

    // 根节点的 parent[p] == p
    while( parent[p] != p )
    {
        //进行路径压缩
        parent[p] = parent[parent[p]];
        p = parent[p];

    }

    return p;

}