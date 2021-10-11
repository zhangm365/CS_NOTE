

// 给定一个已按照升序排列 的有序数组，找到两个数使得它们相加之和等于目标数。
// https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/

// 数组有序，就用双指针技巧, 左右快慢指针

#include <bits/stdc++.h>

class Solution
{
    public:
        std::vector<int> twoSum(std::vector<int>& nums, int target);
};


std::vector<int> Solution::twoSum(std::vector<int>& nums, int target)
{
    std::vector<int> tmp = {0, 0};
    if(nums.empty() || nums[0] > target) return tmp;
    
    int i = 0, j = nums.size() - 1;

    while(i < j)
    {
        int sum = nums[i] + nums[j];

        // 找到了
        if(target == sum)
        {
            tmp[0] = i + 1;
            tmp[1] = j + 1;
            return tmp;
        }        
        else if(sum > target)
            j--;
        else if(sum < target)
            i++;
    }


    return tmp;

}


int main()
{

    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    std::vector<int> ret;

    Solution So;
    ret = So.twoSum(nums, target);

    for(int i = 0; i < ret.size(); i++)
    {
        if(i != 0)  printf(" ");
        printf("%d", ret[i]);
    }
    printf("\n");

    return 0;
}