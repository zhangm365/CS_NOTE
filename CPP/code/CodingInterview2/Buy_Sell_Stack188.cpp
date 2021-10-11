
// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stocj-iv/submissions/


// k为任意整数 anyInteger

#include <bits/stdc++.h>

class Solution {
    public:
        int maxProfit(int x, std::vector<int>& prices) {

            if(prices.empty() || x <= 0) return 0;
            
            int n = prices.size();

            int dp[n][x+1][2];
            memset(dp, 0, 2*n*(x+1)*sizeof(int));

            for(int i = 0 ; i < n; ++i)
            {
                for(int k = x; k >= 1; k--)
                {
                    if((i-1) == -1)
                    {
                        //base case
                        dp[i][k][0] = 0;
                        dp[i][k][1] = -prices[i];
                        continue;

                    }

                    dp[i][0][0] = 0;
                    dp[i][0][1] = -prices[i];

                    dp[i][k][0] = std::max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
                    dp[i][k][1] = std::max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]);
                    printf("dp[%d][%d][0] = %d,  dp[%d][%d][1] = %d\n", i, k, dp[i][k][0], i, k, dp[i][k][1]);

                }
                

            }

            return dp[n-1][x][0];

        }

};


int main()
{

    std::vector<int> prices = {3,2,6,5,0,3};
    int k = 2;
    Solution So;
    int ret = So.maxProfit(2, prices);
    printf("ret = %d\n", ret);

    return 0;

}