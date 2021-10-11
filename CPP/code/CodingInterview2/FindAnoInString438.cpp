
// https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/
// 找到字符串中所有字母异位词


#include <bits/stdc++.h>


class Solution
{
    public:
        std::vector<int> findAnagrams(std::string s, std::string t);
};


std::vector<int> Solution::findAnagrams(std::string s, std::string t)
{

    std::vector<int> ret;

    if( s.empty() || t.empty() ) return {};
    
    int left = 0, right = 0;

    std::unordered_map<char, int> need, windows;

    int valid = 0;

    for(char c : t) need[c]++;

    while ( right < s.size() )
    {
        // 窗口右移
        char c = s[right];
        right++;

        // 更新窗口内的一系列数据
         if( need.count(c) )
        {
            windows[c]++;

            if( need[c] == windows[c] )
                valid++;
        }

        // 判断是否缩小窗口
        while( (right - left) >= t.size() ) 
        {
            if( valid == need.size() )
            {
                ret.push_back(left);
            }

            char d = s[left];
            left++;

            if(need.count(d))
            {
                if( need[d] == windows[d] )
                    valid--;
                    
                windows[d]--;
            }
            
                
        }

    }
    
    return ret;

}



int main()
{

    std::vector<int> ret;
    Solution So;
    std::string s("baa");
    std::string t("aa");
    ret = So.findAnagrams(s, t);
    for( int i = 0; i < ret.size(); ++i )
    {
        if(i != 0 ) printf(" ");
        printf("%d", ret[i]);
    }

    printf("\n");


    return 0;

}