



// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/

// 买卖股票的最佳时机: 仅允许进行一次交易, 来计算所获得的最大利润

#include <bits/stdc++.h>


class Solution
{
    public:
        int maxProfit(std::vector<int> &prices);
        int maxProfit2(std::vector<int> &prices);
};


// 全局DP数组求解
int Solution::maxProfit(std::vector<int> &prices)
{

    if(prices.empty()) return 0;

    int n = prices.size();

    int dp[n][2];

    for(int i = 0; i < n; ++i)
    {

        // base case 
        if( -1 == (i-1) )
        {
            dp[i][0] = 0;
            dp[i][1] = -prices[i];
            continue;

        }

        // 状态转移方程
        // 没有股票         // 无操作    // 将第i-1天的卖出       
        dp[i][0] = std::max(dp[i-1][0], dp[i-1][1] + prices[i]);
        // 有股票           // 无操作    // 在第i-1天的买入 
        dp[i][1] = std::max(dp[i-1][1], -prices[i]);

    }


    return dp[n-1][0];
}


// 新状态只有相邻的前一个状态有关，故用变量记录相邻状态更新答案
int Solution::maxProfit2(std::vector<int> &prices)
{

    if(prices.empty()) return 0;

    int n = prices.size();

    // base case
    int dp_i_0 = 0, dp_i_1 = INT_MIN;
    
 
    for(int i = 0; i < n; ++i)
    {
       
        // 没有股票 
        dp_i_0= std::max(dp_i_0, dp_i_1 + prices[i]);
        // 有股票
        dp_i_1 = std::max(dp_i_1, -prices[i]);

    }


    return dp_i_0;
    
}
