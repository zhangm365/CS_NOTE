
// https://leetcode-cn.com/problems/min-cost-climbing-stairs/

// 使用最小成本爬楼梯

#include <bits/stdc++.h>


class Solution
{
    public:

        int minCostClimbingStairs(std::vector<int>& cost) 
        {
            int n = cost.size();

            std::vector<int> dp(n+1);
            //  初始状态
            dp[0] = 0; 
            dp[1] = std::min(cost[0], cost[1]);

            for(int i = 2; i < n; ++i)
            {
                // 状态转移方程
                dp[i] = std::min(dp[i-1] + cost[i], dp[i-2] + cost[i-1]);
                //printf("i = %d, dp[%d] = %d\n", i, i, dp[i]);

            }

            return dp[n-1];
        }
};


int main()
{

    std::vector<int> cost = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};

    Solution So;
    
    int ret = So.minCostClimbingStairs(cost);

    printf("%d\n", ret);


    return 0;

}