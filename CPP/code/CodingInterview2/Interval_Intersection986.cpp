

//区间交集问题

// https://leetcode-cn.com/problems/interval-list-intersections/

// 解决区间问题一般先排序

#include <bits/stdc++.h>


class Solution
{

    public:
        std::vector<std::vector<int> > intervalIntersection(std::vector<std::vector<int> > &A, std::vector<std::vector<int> > &B);


};


std::vector<std::vector<int> > Solution::intervalIntersection(std::vector<std::vector<int> > &A, std::vector<std::vector<int> > &B)
{

    // 给定的区间已经有序，设置两个索引指针在A和B中游走，求解交集问题

    if( A.empty() || B.empty() ) return {};

    int m = A.size(), n = B.size();

    std::vector<std::vector<int> > res;
    int i = 0, j = 0;   // 双指针

    while(i < m && j < n)
    {

        int a1 = A[i][0], a2 = A[i][1];

        int b1 = B[j][0], b2 = B[j][1];

        // 两个区间存在交集
        if( a2 >= b1 && b2 >= a1 )
        {
            //计算出交集，加入res中
            std::vector<int> tmp = { std::max(a1, b1), std::min(a2, b2) };
            res.push_back(tmp);

        }

        // 指针前进
        if(b2 < a2) 
            j++;
        else
            i++; 

    }

    return res;

}
