
// https://leetcode-cn.com/problems/daily-temperatures/

// 每日温度



#include <bits/stdc++.h>


class Solution
{
    public:
        std::vector<int> dailyTemperatures(std::vector<int> &T);
    
    private:
        std::stack<int> st;

};

std::vector<int> Solution::dailyTemperatures(std::vector<int>& T)
{

    if( T.empty() ) return {};
    int n = T.size();

    std::vector<int> res(n);


    for ( int i = n - 1; i >= 0 ; i-- )
    {
        
        while( !st.empty() && T[st.top()] <= T[i] )
        {
            st.pop();

        }
        
        res[i] = st.empty() ? 0 : (st.top() - i);

        
        // 栈存储元素的索引
        st.push(i); 

    }
    
    return res;


}