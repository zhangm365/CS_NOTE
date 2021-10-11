

// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/submissions/
// 股票交易含有冷冻期


#include <bits/stdc++.h>


class Solution {
    public:
        int maxProfit(std::vector<int>& prices);
        int maxProfit2(std::vector<int>& prices);

};


// 根据状态转移方程：使用全局DP数组求解
int Solution::maxProfit(std::vector<int>& prices) 
{

    if(prices.empty()) return 0;

    int n = prices.size();

    int dp[n][2];
    memset(dp, 0, 2*n*sizeof(int));
    
    for(int i = 0; i < n; ++i)
    {

        // 1.base case
        if( -1 == (i-1) )
        {
            dp[i][0] = 0;
            dp[i][1] = -prices[i];
            //printf("---dp[%d][0] = %d, dp[%d][1] = %d---\n", i, dp[i][0], i, dp[i][1]);
            continue;

        }
        
        // 2.状态转移方程

        // 无股票
        dp[i][0] = std::max( dp[i-1][0], dp[i-1][1] + prices[i]);

        //有股票, 含有交易冷冻期, 分类讨论下
        if(i-2 == -1) //i = 1, dp[i-1][0] = 0; 
        {
            dp[i][1] = std::max( dp[i-1][1], -prices[i]); 
        }
        else
        {
            dp[i][1] = std::max( dp[i-1][1], dp[i-2][0] - prices[i]);
        }
        
        //printf("dp[%d][0] = %d, dp[%d][1] = %d\n", i, dp[i][0], i, dp[i][1]);

    }

    return dp[n-1][0];

}

// 不用整个DP数组, 新状态只与相邻的状态有关，故用变量存储相邻的状态来更新答案，将空间复杂度降为O(1)

int Solution::maxProfit2(std::vector<int>& prices) 
{

    if(prices.empty()) return 0;

    int n = prices.size();
   
    // base case
    int dp_i_0 = 0, dp_i_1 = INT_MIN;
    
    int dp_pre_0 = 0;   //dp[i-2][0]

    for(int i = 0; i < n; ++i)
    {
       
        // 2.状态转移方程
        int tmp = dp_i_0;   // 记录前一次状态
        // 无股票
        dp_i_0 = std::max( dp_i_0, dp_i_1 + prices[i]);

        //有股票, 含有交易冷冻期
        dp_i_1 = std::max( dp_i_1, dp_pre_0 - prices[i]);

        dp_pre_0 = tmp;

        //printf("dp[%d][0] = %d, dp[%d][1] = %d\n", i, dp[i][0], i, dp[i][1]);

    }

    return dp_i_0;

}


int main()
{

    std::vector<int> prices = {1,2,3,0,2};
    Solution So;
    int ret = So.maxProfit2(prices);

    printf("ret = %d\n", ret);


    return 0;

}

