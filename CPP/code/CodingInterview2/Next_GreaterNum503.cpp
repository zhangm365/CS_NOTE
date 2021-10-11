


// https://leetcode-cn.com/problems/next-greater-element-ii/

#include <bits/stdc++.h>


class Solution
{

    public:
        std::vector<int> nextGreaterElements( std::vector<int> &nums );
    
    private:
        std::stack<int> st;

};

std::vector<int> Solution::nextGreaterElements( std::vector<int> &nums )
{

    if(nums.empty()) return {};
    int n = nums.size();

    std::vector<int> res(n);

    // 假设数组翻倍
    for ( int i = 2 * n - 1; i >= 0; i-- )
    {

        while( !st.empty() && st.top() <= nums[i % n])
            st.pop();

        res[i % n] = st.empty() ? -1 : st.top();

        st.push(nums[i%n]); 


    }

    return res;

}