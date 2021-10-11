


// https://leetcode-cn.com/problems/reverse-string/
// 逆序字符串, 左右指针处理


#include <bits/stdc++.h>



class Solution
{
    public:
        void reverseString(std::vector<char>& str);

};

void Solution::reverseString(std::vector<char>& str)
{

    if(str.empty()) return;

    int i = 0, j = str.size() - 1;
    while(i < j)
    {
        char tmp = str[j];
        str[j] = str[i];
        str[i] = tmp;
        i++;
        j--;
        
    }

}

int main()
{
    
    std::string s = {"zhangmao"};
    std::vector<char> str( s.begin(), s.end());
    Solution So;
    So.reverseString(str);

    for( int i = 0 ; i < str.size(); ++i)
        printf("%c", str[i]);
    printf("\n");


    return 0;
}