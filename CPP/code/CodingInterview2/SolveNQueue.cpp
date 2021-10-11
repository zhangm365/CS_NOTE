
// 回溯法: N皇后问题 https://leetcode-cn.com/problems/n-queens/

/* 
    决策树的每一层表示棋盘上的每一行；
    每个节点可以做出的选择是，在该行的任意一列放置一个皇后
*/

#include <bits/stdc++.h>

class Solution
{
    public:
        std::vector<std::vector<std::string> > res; 

        // 主函数, 记录所有的合法位置
        std::vector<std::vector<std::string> > solveNQueens(int n);
        // 遍历决策树
        void backtrack(std::vector<std::string>& board, int row);
        // 判断位置是否合法
        bool isValid(std::vector<std::string>& board, int row, int col);

};

/* 输入棋盘边长 n，返回所有合法的放置 */
std::vector<std::vector<std::string>> Solution::solveNQueens(int n) 
{
    // '.' 表示空，'Q' 表示皇后，初始化空棋盘。
    std::vector<std::string> board(n, std::string(n, '.'));
    backtrack(board, 0);
    return res;

}

// 路径：board 中小于 row 的那些行都已经成功放置了皇后
// 选择列表：第 row 行的所有列都是放置皇后的选择
// 结束条件：row 超过 board 的最后一行
void Solution::backtrack(std::vector<std::string>& board, int row) 
{
    // 触发结束条件
    if (row == board.size()) 
    {
        res.push_back(board);
        return;
    }

    int n = board[row].size();

    for (int col = 0; col < n; col++) 
    {
        // 排除不合法选择
        if (!isValid(board, row, col)) 
            continue;
        // 做选择
        board[row][col] = 'Q';
        // 进入下一行决策
        backtrack(board, row + 1);
        // 撤销选择
        board[row][col] = '.';
    }

}

/* 是否可以在 board[row][col] 放置皇后？ */
bool Solution::isValid(std::vector<std::string>& board, int row, int col) 
{

    int n = board.size();
    // 检查列是否有皇后互相冲突
    for (int i = 0; i < n; i++) 
    {
        if (board[i][col] == 'Q')
            return false;
    }

    // 检查右上方是否有皇后互相冲突
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) 
    {
        if (board[i][j] == 'Q')
            return false;
    }

    // 检查左上方是否有皇后互相冲突
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) 
    {
        if (board[i][j] == 'Q')
            return false;
    }

    return true;

}



int main()
{

    int n;
    printf("Please input the value of N:");

    scanf("%d", &n);
    while(n < 4)
    {
        printf("The value of N is not less than 4!\n Please input the valid value of N:");
        scanf("%d", &n);

    }

    std::vector<std::vector<std::string> > res;
    Solution So;
    res = So.solveNQueens(n);
    
    //printf("%d\n", res.size());
    // 输出数据
    for(std::vector<std::vector<std::string>>::iterator ite = res.begin(); ite != res.end(); ++ite)
    {

        for(std::vector<std::string>::iterator ite1 = (*ite).begin(); ite1 != (*ite).end(); ++ite1)
            std::cout << *ite1 << std::endl;
    
        printf("\n");

    }

    return 0;

}