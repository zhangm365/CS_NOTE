

// https://leetcode-cn.com/problems/find-the-difference/

// 找不同字符


#include <bits/stdc++.h>


class Solution
{

    public:
        char findTheDifference(const std::string &s, const std::string &t);
        char findTheDifference2(const std::string &s, const std::string &t);
        char findTheDifference3(const std::string &s, const std::string &t);
};


char Solution::findTheDifference(const std::string &s, const std::string &t)
{

    std::unordered_map<char, int> need;
    // 计算每个字符的出现次数
    for(char c : s) need[c]++;

    for(char c : t)
    {
        need[c]--;
        if(need[c] < 0)
            return c;
    }

    return ' ';
}

char Solution::findTheDifference2(const std::string &s, const std::string &t)
{

    if(s.empty() && t.empty() ) return ' ';
    int x = 0, y = 0;

    // 字符串s中所有字符之和
    for(char c : s)  
        x += (c - 'a');

    // 字符串t中所有字符之和
    for(char c : t)  
        y += (c - 'a');   
        
    return y - x + 'a';
        
}

char Solution::findTheDifference3(const std::string &s, const std::string &t)
{

    int ret = 0;
    for(char c:s)
        ret ^= c;
    //printf("%d\n", ret);
    for(char c:t)
        ret ^= c;
    //printf("%d\n", ret);
    return ret;
}

int main()
{

    std::string s("abcd");
    std::string t("abcde");
    Solution So;
    char ch = So.findTheDifference3(s, t);
    std::cout << ch << std::endl;

    return 0;
}