

// 
// https://leetcode-cn.com/problems/house-robber-ii/
// 打家劫舍

// 由于是环形数组的限制，所以在选择过程中，有且仅有以下三种情况：
//  1. 都不选着首尾两个元素；
//  2. 只选第一个元素，那么就不能选择最后一个元素；
//  3. 选择最后一个元素，那么就不能选第一个元素；
// 由于数组中元素均为非负整数，所以第一种情况可选择的元素最少，故可排除；因此可在第二种和第三种情况中求解最大值


#include <bits/stdc++.h>

class Solution
{

    public:
        int rob(std::vector<int>& nums);

    private:
        int robRange(std::vector<int>& nums, int start, int end);

};


int Solution::rob(std::vector<int>& nums)
{

    if(nums.empty()) return 0;
    
    int n = nums.size();
    if(1 == n) return nums[0];

    //求闭区间范围[0, n-2]和[1, n-1]的最大值    
    return std::max(robRange(nums, 0, n-2), robRange(nums, 1, n-1));


}

int Solution::robRange(std::vector<int>& nums, int start, int end)
{

    if(end >= nums.size()) return 0;

    int dp_i = 0;   //dp[i]
    int dp_pre_i = 0;   //dp[i-2]

    for( int i = start ; i <= end; ++i)
    {

        int tmp = dp_i;

        dp_i = std::max(dp_i, dp_pre_i + nums[i]);

        dp_pre_i = tmp;

    }

    return dp_i;

}