

// https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/

// 在排序数组中查找元素的第一个和最后一个位置:区间搜索

#include <bits/stdc++.h>


class Solution
{
    public:
        // 主函数
        std::vector<int> searchRange(std::vector<int>& nums, int target);
        // 二分查找有序区间中的元素位置
        int binarySearch(std::vector<int>& nums, int target, bool flag);

};


std::vector<int> Solution::searchRange(std::vector<int>& nums, int target)
{

    std::vector<int> ret = {-1, -1};
    if(nums.empty())
        return ret;
    
    bool flag = false;

    // 搜索左边界
    int left_index = binarySearch(nums, target, flag);
    ret[0] = left_index;

    // 搜索右边界
    flag = true;
    int right_index = binarySearch(nums, target, flag);
    ret[1] = right_index;

    return ret;

}


int Solution::binarySearch(std::vector<int>& nums, int target, bool flag)
{

    //std::vector<int> ret;

    // 判断边界条件
    if(nums.empty()) 
    {
        return -1;

    }

    // 初始化条件
    int left = 0, right = nums.size() - 1;
    int mid = 0;
    // 循环判断条件
    while(left <= right)
    {

        mid = left + (right - left) / 2;
        if(nums[mid] < target)
            left = mid + 1;
        else if(nums[mid] > target)
            right = mid - 1;
        else if( !flag  && nums[mid] == target )     // flag == false, 是查找左边界
            right = mid - 1;
        else if( flag && nums[mid] == target )      // flag == true, 是查找右边界
            left = mid + 1;

        
    }

    
    if(!flag)   // 左边界溢出检查
    {
        if(left >= nums.size() || nums[left] != target)
        {
            return -1;
        }            
        else
        {
            return left;
        } 
    }
    else    // 右边界溢出检查
    {
        if( right < 0 || nums[right] != target)
            return -1;
        else
        {
            return right;
        }
        
    }
        
    return -1;

}


int main()
{

    std::vector<int> nums = {2, 3, 5, 5, 6, 6, 8};
    int target = 6;
    Solution So;
    std::vector<int> ret = So.searchRange(nums, target);

    for(int i = 0; i < ret.size(); ++i)
    {
        if(i != 0) printf(" ");
        printf("%d", ret[i]);
    }
        
    printf("\n");

    return 0;
}