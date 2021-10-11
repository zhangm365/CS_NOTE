
// https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/

#include <bits/stdc++.h>


class Solution {
public:
    int shipWithinDays(std::vector<int>& weights, int D);

    // 
    bool CanFinish(std::vector<int>& weights, int total, int D);

    // 最大值
    int getMax(std::vector<int> &weights);
    // 求和
    long long getSum(std::vector<int> &weights);

};


int Solution::shipWithinDays(std::vector<int> &weights, int D)
{
    if (weights.empty()) return 0;

    // left:载重的可能最小值。 right: 载重的可能最大值
    int left = getMax(weights), right = getSum(weights) + 1;

    // 二分搜索
    while( left < right)
    {
        int mid = left + (right-left)/2;
        if( CanFinish(weights, mid, D) )
            right = mid;
        else
            left = mid + 1;
    }

    return left;


}


bool Solution::CanFinish( std::vector<int>& weights, int total, int D )
{

    // 容量为total的是否可以在D天内完成装卸
    if (weights.empty()) return 0;
    int day = 0; 
    int i = 0;
    for (; day < D; day++ )
    {
        int maxCap = total;
        while( (maxCap -= weights[i]) >= 0 )
        {
            i++;
            if ( i == weights.size() )
                return true;
        }    
    }

    return false;
}

int Solution::getMax(std::vector<int> &weights)
{

    if (weights.empty()) return 0;
    int max = weights[0];
    for ( auto &w : weights )
        if(max < w)
            max = w;

    return max;

}

long long Solution::getSum(std::vector<int> &weights)
{

    if (weights.empty()) return 0;
    long long sum = 0;
    for ( auto &w : weights )
        sum += w;

    return sum;

}