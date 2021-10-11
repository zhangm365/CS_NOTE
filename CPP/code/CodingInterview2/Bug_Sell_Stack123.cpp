

// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/

// 买卖股票的最佳时机，最多可以完成两次交易

#include <bits/stdc++.h>


class Solution
{

    public:
        int maxProfit(std::vector<int>& prices);
        int maxProfit2(std::vector<int>& prices);

};


int Solution::maxProfit(std::vector<int>& prices)
{
    

    int n = prices.size();
    // 因为最大交易次数是2次，所以需对交易次数k进行穷举
    int max_k = 2;
    
    // n为第i天, max_k为交易次数, 2：股票卖出或买入状态
    int dp[n][max_k+1][2];
    memset(dp, 0, 2*n*(max_k+1)*sizeof(int));

    for( int i = 0; i < n; ++i )
    {
        //穷举交易次数K的取值
        for(int k = max_k; k >= 1; k--)
        {
            // base case
            if( -1 == (i-1) )
            {
                // i = 0
                dp[i][k][0] = 0;
                dp[i][k][1] = -prices[i];
                continue;

            }

            dp[i][0][0] = 0;
            dp[i][0][1] = -prices[i];

            //状态转移方程
            dp[i][k][0] = std::max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
            dp[i][k][1] = std::max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]);

            printf("dp[%d][%d][0] = %d,  dp[%d][%d][1] = %d\n", i, k, dp[i][k][0], i, k, dp[i][k][1]);

        }
        
    }

    return dp[n-1][max_k][0];
    
}


int Solution::maxProfit2(std::vector<int>& prices)
{

    if(prices.empty()) return 0;

    int n = prices.size();

    // 全部列举出来： k = 1 or k = 2

    //dp[i][1][0] = std::max(dp[i-1][1][0], dp[i-1][1][1] + prices[i]);
    //dp[i][1][1] = std::max(dp[i-1][1][1], dp[i-1][0][0] - prices[i]);
    //dp[i][2][0] = std::max(dp[i-1][2][0], dp[i-1][2][1] + prices[i]);
    //dp[i][2][1] = std::max(dp[i-1][2][1], dp[i-1][1][0] - prices[i]);


    int dp_i_1_0 = 0, dp_i_1_1 = INT_MIN;
    int dp_i_2_0 = 0, dp_i_2_1 = INT_MIN;


    for(int i = 0 ; i < n; ++i)
    {

        dp_i_1_0 = std::max(dp_i_1_0, dp_i_1_1 + prices[i]);
        dp_i_1_1 = std::max(dp_i_1_1, -prices[i]);
        dp_i_2_0 = std::max(dp_i_2_0, dp_i_2_1 + prices[i]);
        dp_i_2_1 = std::max(dp_i_2_1, dp_i_1_0 - prices[i]);

    }
 
    return dp_i_2_0;


}

int main()
{

    std::vector<int> prices = {3,3,5,0,0,3,1,4};
    Solution So;
    int ret = So.maxProfit(prices);
    printf("maxProfit = %d\n", ret);

    return 0;

}