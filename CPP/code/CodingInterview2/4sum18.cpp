


// 4数之和

// https://leetcode-cn.com/problems/4sum/


#include <bits/stdc++.h>

class Solution
{

    public:

        std::vector<std::vector<int> > fourSum(std::vector<int> &nums, int target);
        // 将4sum问题转化为3sum问题
        std::vector<std::vector<int> > threeSum(std::vector<int> &nums, int start, int target);
        // 将3sum问题转化为求解2sum问题
        std::vector<std::vector<int> > twoSum(std::vector<int> &nums, int start, int target);
    
    private:
        std::vector<std::vector<int> > res;
};


// 给定target, 求解4sum问题

std::vector<std::vector<int> > Solution::fourSum(std::vector<int> &nums, int target)
{

    if( nums.empty() ) return {};

    sort( nums.begin(), nums.end() );

    int n = nums.size();
    std::vector<std::vector<int> > triples;

    for(int i = 0 ; i < n; ++i)
    {

        triples = threeSum( nums, i+1, target - nums[i] );
        
        for( std::vector<int> &triple : triples )
        {
            triple.push_back(nums[i]);
            res.push_back(triple);
        }

        while( i < n-1 && nums[i+1] == nums[i] ) i++;

    }

    return res;

}


// 3sum问题
std::vector<std::vector<int> > Solution::threeSum(std::vector<int> &nums, int start, int target)
{

    if( nums.empty() || start >= nums.size() ) return {};

    // step1 : 将数组升序排列
    // sort( nums.begin(), nums.end() );

    int n = nums.size();

    std::vector<std::vector<int> > res;
    std::vector<std::vector<int> > tuples;
    
    for( int i = start; i < n; ++i )
    {
        
        //返回两个数之和
        tuples = twoSum( nums, i+1, target - nums[i] );
                
        //printf("tuples = %d\n", tuples.size());

        // 将每次结果存入结果数组中
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

    // 双指针遍历
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

    std::vector<int> nums = {1, 0, -1, 0, -2, 2};
    Solution So;
    std::vector<std::vector<int> >  res = So.fourSum(nums, 0);
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