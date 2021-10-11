
/*
    @ 给定一个数组，每个元素代表一个分数。
    可以从数组的任意一个位置出发，每次跳跃到i+nums[i]的位置获取分数，如果超过数组边界，则结束游戏
    求取得最大分数的结果值。
    
    @ 思路
    从前往后遍历的暴力解法，时间复杂度是 O(n^2)，会超时

    优化算法：动态规划：从后遍历，O(n)


*/

#include <bits/stdc++.h>

using namespace std;


int main()
{

    int n;
    cin >> n;

    vector<int> vec(n, 0);

    for( int i = 0; i < n; ++i )
    {
        int val;
        cin >> val;
        vec[i] = val;

    }

    vector<int> dp(n, 0);   // 动态规划：dp[i] 代表以 i 位置开始的跳跃总分数
    int ret = 0;

    for( int i = n-1; i >= 0; --i )
    {

        if( i + vec[i] > n )
            dp[i] = vec[i];
        else
        {
            dp[i] = max(dp[i], vec[i] + dp[i+vec[i]]);
        }

        ret = max(ret, dp[i]);
    }
    
    cout << ret << endl;

    return 0;

}