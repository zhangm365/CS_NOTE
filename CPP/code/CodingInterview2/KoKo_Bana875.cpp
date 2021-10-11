


// https://leetcode-cn.com/problems/koko-eating-bananas/


#include <bits/stdc++.h>

class Solution
{
    public:
        int minEatingSpeed(std::vector<int>& piles, int H);

        // 辅助函数: 判断以速率speed是否可以完成
        bool CanFinish(std::vector<int> &piles, int speed, int H);

        // 
        int Div_Mod(int n, int H);

        // 获取arr中的最大元素
        //int getMax(std::vector<int> &arr);

};


int Solution::minEatingSpeed(std::vector<int> &piles, int H)
{

    if( piles.empty() || H <= 0 ) return 0;
    
    std::sort( piles.begin(), piles.end() );

    
    int max = piles[piles.size()-1];
    int left = 1, right = max + 1;

    // 二分查找 最小速率
    while ( left < right )
    {
        int mid = left + (right - left)/2;
        if( CanFinish(piles, mid, H) )
            right = mid;
        else 
            left = mid + 1;
    }
    
    return left;

}


bool Solution::CanFinish( std::vector<int> &piles, int speed, int H )
{

    long long time = 0;

    for (auto &p : piles)
    {
        time += Div_Mod( p, speed );
    }

    return time <= H;

}

int Solution::Div_Mod( int n, int speed )
{

    return (n / speed) + ((n % speed) ? 1 : 0);

}

// int Solution::getMax(std::vector<int> &arr)
// {
//     if(arr.empty()) return 0;
//     int max = arr[0];
//     for (int i = 1; i < arr.size(); ++i )
//     {
//         if( max < arr[i] )
//             max = arr[i];
//     }

//     return max;
// }