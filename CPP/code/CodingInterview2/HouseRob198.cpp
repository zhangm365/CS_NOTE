
// https://leetcode-cn.com/problems/house-robber/submissions/
// 打家劫舍


#include <bits/stdc++.h>

class Solution{

    public:
        int rob(std::vector<int> &nums ) ;
        int rob2(std::vector<int>& nums);

    private:
        int dp(std::vector<int> &nums , int start); 
        
};


int Solution::rob(std::vector<int> &nums ) 
{
    return dp(nums, 0);
}

// 递归解法: 返回 nums[start..] 能抢到的最大值
int Solution::dp(std::vector<int> &nums , int start) 
{
    if (start >= nums.size()) 
    {
        return 0;
    }
    
    int res = std::max(
            // 不抢，去下家
            dp(nums, start + 1), 
            // 抢，去下下家
            nums[start] + dp(nums, start + 2)
        );

    return res;

}


//新状态只与相邻状态有关
int Solution::rob2(std::vector<int> &nums) 
{
    
    if(nums.empty()) return 0;

    int dp_i = 0; //dp[i-1]
    int dp_pre_i = 0;   //dp[i-2]

    int n = nums.size();
    // dp[i] = std::max(dp[i-1], dp[i-2] + nums[i]);
    for(int i = 0; i < n; ++i)
    {
        //状态转移
        int tmp = dp_i;
        dp_i = std::max(dp_i, dp_pre_i + nums[i]); 
        dp_pre_i = tmp;

    }
    

    return dp_i;

}




int main()
{
    std::vector<int> nums = {1,3,1,5};
    Solution So;

    int ret = So.rob2(nums);
    printf("ret = %d\n", ret);

    return 0;
}