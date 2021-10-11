
// 买卖股票的最佳时机(含手续费)：不限交易次数

// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/

#include <bits/stdc++.h>


class Solution
{
    public:
        int maxProfit(std::vector<int> &prices, int fee);
        int maxProfit2(std::vector<int> &prices, int fee);


};


// k为无穷大: 即不限交易次数
int Solution::maxProfit(std::vector<int> &prices, int fee)
{

    if(prices.empty()) return 0;

    int n = prices.size();

    int dp[n][2] ;

    memset(dp, 0, 2*n*sizeof(int));
    
    for( int i = 0; i < n; ++i )
    {

        if(-1 == (i-1))
        {   // base case

            dp[i][0] = 0;
            dp[i][1] = -prices[i]-fee;
            continue;

        }
        // 状态转移方程
        // 0.无股票
        dp[i][0] = std::max( dp[i-1][0], dp[i-1][1] + prices[i] );
        // 1.有股票
        dp[i][1] = std::max( dp[i-1][1], dp[i-1][0] - prices[i] - fee );


    }


    return dp[n-1][0];

}

int Solution::maxProfit2(std::vector<int>& prices, int fee) 
{

    if(prices.empty()) return 0;
    int n = prices.size();

    int dp_i_0 = 0, dp_i_1 = INT_MIN; 

    for(int i = 0 ; i < n; ++i)
    {
        // 
        int tmp = dp_i_0;
        dp_i_0 = std::max(dp_i_0, dp_i_1 + prices[i]);
        dp_i_1 = std::max(dp_i_1, tmp - prices[i] - fee);

    }
    
    return dp_i_0;
}


int main()
{

    std::vector<int> prices = {1, 3, 2, 8, 4, 9};
    int fee = 2;
    Solution So;
    int max_profit = So.maxProfit2(prices, fee);

    printf("max_profit = %d\n", max_profit);

    return 0;
}
