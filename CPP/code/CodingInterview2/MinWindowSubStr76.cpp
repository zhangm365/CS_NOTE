

// https://leetcode-cn.com/problems/minimum-window-substring/

/// 最小覆盖子串

#include <bits/stdc++.h>


class Solution
{
    public:
        std::string minWindow(const std::string& s, const std::string& t);

};


std::string Solution::minWindow(const std::string& s, const std::string& t)
{

    if(s.empty() || t.empty()) return "";

    std::unordered_map<char, int> need, windows;
    for(char c : t) need[c]++;

    int left = 0, right = 0;

    // 记录滑动窗口中满足need条件的字符个数
    int valid = 0;

    // 最小覆盖子串的范围区间
    int start = 0, len = INT_MAX;

    while (right < s.size())
    {

        // 窗口向右滑动
        char c = s[right];
        right++;

        // 窗口内数据更新: 判断元素是否存在
        if(need.count(c) > 0)
        {

            windows[c]++;
            if(windows[c] == need[c])
                valid++;

        }

        // 当窗口满足条件后, 判断窗口是否左移缩小
        while(valid == need.size())
        {
            // 更新最小覆盖子串
            if(right - left < len)
            {
                start = left;
                len = right - left;    // 子串长度
            
            }

            char d = s[left];
            // 左移窗口
            left++;
            // 进行窗口内数据的更新
            if(need.count(d))
            {
                if(windows[d] == need[d])
                    valid--;
                windows[d]--;
            }

        }
    }
    
    return len == INT_MAX ? "" : s.substr(start, len);


}




int main()
{

    //std::unordered_map<char, int> need;
    std::string s("ADOBECODEBANC");
    std::string t("ABC");

    Solution So;
    std::string ret = So.minWindow(s, t);
    for(char c : ret) 
    {
        printf("%c", c);
    }
    printf("\n");
    
    return 0;

}