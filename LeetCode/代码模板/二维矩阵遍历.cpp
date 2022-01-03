


/*  * 二维矩阵遍历
    * 将二维矩阵抽象成一个网状「图」结构，每个节点有上、下、左、右四个相邻节点。
    * visited 数组标记访问的节点
*/


void dfs( const vector<vector<int>> &grid, int i, int j, vector<bool> &visited )
{

    int m = grid.size();
    if( m <= 0 ) return;

    int n = grid[0].size();

    // 检查边界
    if( i < 0 || j < 0 || i >= m || j >= n )
        return ;

    if( visited[i][j] ) return;

    visited[i][j] = true;

    dfs( grid, i-1, j, visited );    // 上
    dfs( grid, i+1, j, visited );    // 下
    dfs( grid, i, y-1, visited );    // 左
    dfs( grid, i, j+1, visited );    // 右


}


/*
    进阶方法，使用一个方向数组遍历二维矩阵。
*/


// 方向数组：分别表示上下左右方向
vector<vector<int>> dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };


void dfs( const vector<vector<int>> &grid, int i, int j, vector<bool> &visited )
{

    int m = grid.size();
    if( m <= 0 ) return;

    int n = grid[0].size();

    // 检查边界
    if( i < 0 || j < 0 || i >= m || j >= n )
        return ;

    if( visited[i][j] ) return;

    visited[i][j] = true;


    // 递归遍历 上下左右节点
    for( const auto &d : dirs )
    {

        dfs( grid, i + d[0], j + d[1], visited );
    }
    


}
