



//零钱兑换

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount);
    
};

int Solution::coinChange(vector<int>& coins, int amount)
{

    if(amount < 0)
        return -1;
    if(amount == 0)
        return 0;
    
    //数组大小为amount+1, 初始值为amount+1
    vector<int> dp(amount + 1, amount + 1);
    //base case
    dp[0] = 0;
    for( int i = 0 ; i < dp.size(); ++i)
    {
        for(auto coin : coins)
        {
            if(i - coin < 0) continue;
            dp[i] = min(dp[i], 1 + dp[i-coin]);
        }

    }
    

    return (dp[amount] == amount + 1) ? -1 : dp[amount];

}


int main()
{


    Solution So;
    int n;
    scanf("%d", &n);
    vector<int> coins = {1, 2, 5};

    printf("%d\n", So.coinChange(coins, n));


    return 0;

}