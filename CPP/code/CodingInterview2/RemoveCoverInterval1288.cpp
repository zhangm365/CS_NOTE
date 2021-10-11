

// https://leetcode-cn.com/problems/remove-covered-intervals/

// 删除被覆盖区间


#include <bits/stdc++.h>


class Solution
{

    public:
        int removeCoveredIntervals(std::vector<std::vector<int>> &intervals);


};


int Solution::removeCoveredIntervals(std::vector<std::vector<int>> &intervals)
{

    if(intervals.empty()) return 0;

    int n = intervals.size();

    //1.排序: 按起点升序排序，若起点相同，则按终点降序排序
    // lambda表达式重载sort排序函数
    sort(intervals.begin(), intervals.end(), [](const std::vector<int> &u, const std::vector<int> &v)->bool {
            
            return ( u[0] < v[0] || (u[0] == v[0] && u[1] > v[1]) );
            
        });


    // 初始值：初始区间的起点和终点
    int left = intervals[0][0];
    int right = intervals[0][1];

    int res = 0;

    for(int i = 1; i < n; ++i)
    {
        std::vector<int> nums = intervals[i];
        // 情况1: 找到覆盖区间
        if( left <= nums[0] && right >= nums[1])
            res++;
        
        // 情况2: 找到相交区间则合并成一个大区间
        if( right >= nums[0] && right <= nums[1])
        {
            right = nums[1];
        }

        // 情况3：完全不相交, 则更新起点和终点
        if( right < nums[0] )
        {
            left = nums[0];
            right = nums[1];

        }


    }

    return n - res;

}



int main()
{

    std::vector<std::vector<int>> nums = { {1,4}, {3, 6}, {2, 8} };
    Solution So;

    printf("%d\n", So.removeCoveredIntervals(nums));

    return 0;

}