
// https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/

// 无重复字符的最长子串

#include <bits/stdc++.h>


class Solution
{
    public:
        int lengthOfLongestSubstring(std::string &s);
};


int Solution::lengthOfLongestSubstring(std::string &s)
{

    int ret = 0;
    if(s.empty()) return ret;

    std::unordered_map<char, int> windows;


    int left = 0, right = 0;
    

    while( right < s.size() )
    {

        // 窗口右移
        char c = s[right];
        right++;

        // 窗口内数据更新
        windows[c]++;

        // 判断是否缩小窗口
        while(windows[c] > 1)
        {
            char d = s[left];
            left++;
            // 窗口内数据更新
            windows[d]--;

        }

        // 收缩窗口后, 保证窗口内没有重复字符, 然后更新答案：去最大值
        if( (right - left) > ret )
            ret = right - left;

    }
    
    return ret;

}


int main()
{

    std::string s("abcdaabdef");
    Solution So;
    int ret = So.lengthOfLongestSubstring(s);
    std::cout << ret << std::endl;

    return 0;

}