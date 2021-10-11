


//https://leetcode-cn.com/problems/surrounded-regions/submissions/


#include <bits/stdc++.h>

class Solution
{

    public:
        // 构造函数, n为图中结点总数
        Solution(){}
        Solution( int n );
        
        // 连通两个结点
        void two_union( int p, int q );

        // 判断两个节点是否连通
        bool connected( int p, int q );

        // 查找node节点的父节点
        int par_find(int node);
        
        void solve(std::vector<std::vector<char>>& board);


    private:
        // 记录连通分量
        int count;
        // 结点x的结点是 parent[x]
        std::vector<int> parent;

        // 记录每个树中含有的结点数, 称为"重量"
        std::vector<int> weight;

};


Solution::Solution( int n )
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
void Solution::two_union( int p, int q )
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
bool Solution::connected( int p, int q )
{

    int pr = par_find(p);
    int qr = par_find(q);

    return pr == qr;

}


// 返回某个节点的根节点
int Solution::par_find( int p )
{

    // 根节点的 parent[p] == p
    while( parent[p] != p )
    {
        //进行路径压缩, 树的高度不超过3
        parent[p] = parent[parent[p]];
        p = parent[p];

    }

    return p;

}


void Solution::solve(std::vector<std::vector<char>>& board) 
{

    if ( board.empty() ) return;

    int m = board.size();
    int n = board[0].size();

    // 给虚拟节点dummy留一个位置
    Solution So(m*n + 1);


    int dummy = m*n;

    // 首列与末列的'O'与虚拟节点dummy相连
    for ( int i = 0; i < m; ++i)
    {
        for( int j = 0; j < n; ++j)
        {
            if(board[i][0] == 'O')
                So.two_union( dummy, i*n );
            if(board[i][n-1] == 'O')
                So.two_union( dummy, (i*n) + n-1 );
        }
    }

    // 首行与末行
    for ( int i = 0; i < m; ++i)
    {
        for( int j = 0; j < n; ++j)
        {
            if(board[0][j] == 'O')
                So.two_union(dummy, j);
            if(board[m-1][j] == 'O')
                So.two_union(dummy, (n*(m-1)) + j );
        }
    }

    // 方向数组d是上下左右搜索的常用方法    //右    //下    //上     //左
    std::vector<std::vector<int> > d = { {1,0}, {0,1}, {0, -1}, {-1, 0} };

    for (int i = 1; i < m - 1; i++)
    { 
        for (int j = 1; j < n - 1; j++) 
        {
            if (board[i][j] == 'O')
            {
                // 判断此 O 是否与上下左右的 O 连通
                for (int k = 0; k < 4; k++) 
                {
                    int x = i + d[k][0];
                    int y = j + d[k][1];
                    // 上下或垂直方向出现相连
                    if (board[x][y] == 'O')
                        So.two_union(x * n + y, i * n + j); //相邻的两个节点连通
                }
            }
        }
    } 


    // 所有不和dummy连通的都被替换"X"
    for ( int i = 0; i < m-1; ++i )
    {
        for( int j = 0; j < n-1; ++j )
        {
            if( !So.connected(dummy, i*n+j) )
                board[i][j] = 'X';

        }
    
    }

        
}