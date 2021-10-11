

// 三数之和:排序+双指针

// https://leetcode-cn.com/problems/3sum/

#include <bits/stdc++.h>

class Solution
{

    public:
        std::vector<std::vector<int> > threeSum(std::vector<int> &nums);
        // 将3sum问题转化为求解2sum问题
        std::vector<std::vector<int> > twoSum(std::vector<int> &nums, int start, int target);
};




std::vector<std::vector<int> > Solution::threeSum(std::vector<int> &nums)
{

    if( nums.empty() ) return {};

    // step1 : 将数组升序排列
    sort( nums.begin(), nums.end() );

    if(nums[0] > 0) return {};
    
    int n = nums.size();

    std::vector<std::vector<int> > res;

    for( int i = 0; i < n; ++i )
    {

        if( nums[i] > 0 ) break;
        // 总target = 0
        int target = 0 - nums[i];

        //返回两个数之和
        std::vector<std::vector<int> > tuples = twoSum( nums, i+1, target );
        
        
        //printf("tuples = %d\n", tuples.size());
        for(std::vector<int> &tuple : tuples )
        {
            
            tuple.push_back(nums[i]);
            res.push_back(tuple);
            
        }

        // 跳过相邻的重复元素
        while( i < n - 1 && nums[i] == nums[i+1] ) i++; 

    }

    
    return res;


} 


// 求2sum问题：给定target, 找到所有和为target的元素对
std::vector<std::vector<int> > Solution::twoSum(std::vector<int> &nums, int start, int target)
{

    //printf("target = %d\n", target);
    if( nums.empty() || start >= nums.size() ) return {};

    std::vector<std::vector<int> > res;

    //sort(nums.begin(), nums.end());
    
    // nums区间内的元素已经有序，使用双指针来求解和为target的元素对
    int low = start, high = nums.size() - 1;

    while( low < high )
    {
        
        int left = nums[low], right = nums[high];

        int sum = left + right;

        if( sum < target )
        {
            // 跳过重复元素
            while( low < high && nums[low] == left ) low++;

        }
        else if( sum > target )
        {

            while( low < high && nums[high] == right ) high--;

        }
        else if( sum == target )  
        {
            
            //printf("target = %d, left = %d, right = %d\n", target, left, right );
   
            res.push_back({left, right});
            
            // 跳过重复元素
            while( low < high && nums[low] == left ) low++;
            while( low < high && nums[high] == right ) high--;

        }
        
    }
    
    return res;

}


int main()
{

    std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
    Solution So;
    std::vector<std::vector<int> >  res = So.threeSum(nums);
    for( int i = 0; i < res.size(); ++i )
    {

        for( int j = 0; j < res[0].size(); ++j )
        {
            printf("%d ", res[i][j]);
        }

        printf("\n");

    }


    return 0;

}