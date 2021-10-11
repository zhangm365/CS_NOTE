


// https://leetcode-cn.com/problems/permutation-in-string/
// 字符串的排列： 滑动窗口

#include <bits/stdc++.h>


class Solution
{
    public:
        bool checkInclusion(const std::string &s1, const std::string &s2);

};



bool Solution::checkInclusion(const std::string &s1, const std::string &s2)
{

    // 均为空, 返回true
    if( s1.empty() && s2.empty() ) return true;
    // 有一个为空, 返回false
    if( s1.empty() || s2.empty() ) return false;

    std::unordered_map<char, int> need, windows;

    for(char c : s1) need[c]++;

    int left = 0, right = 0;

    int valid = 0;

    while(right < s2.size())
    {
        // 增大窗口
        char c = s2[right];
        right++;

        if(need.count(c))
        {
            windows[c]++;

            if( windows[c] == need[c] )
            {
                valid++;                
            }
                
        }

        // 缩小窗口
        while( (right - left) >= s1.size() )
        {
            if(valid == need.size())
                return true;
            
            char d = s2[left];
            left++;

            // 更新窗口内的一系列数据
            if(need.count(d))
            {
                if(windows[d] == need[d])
                {
                    valid--;
                }
                windows[d]--;
            }
        }        
        
        
    }
    
    return false;

}




int main()
{

    std::string s1("abc");
    std::string s2("eidbcaoo");

    Solution So;
    bool ret = So.checkInclusion(s1, s2);

    printf("ret = %d\n", ret);

    return 0;
}