

// 数字的排列组合

#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    vector<string> printNumbers(int n) {
        
        if( n <= 0 ) return {};

        this->num = n;
        start = num - 1;

        vector<string> res;

        helper("", res, 0);

        for( const auto&str : res )
            cout << str << endl;
        return res;

    }

    void helper(string prefix, vector<string>& res, int level)
    {
        if( num == level )  // 加入到结果链表
        {
            string tmp = prefix.substr(start);
            if( tmp != "0" )
                res.emplace_back(tmp);
            
            if ( num - start == nine ) start--;

            return;

        }

        for( const auto& c : sp )
        {
            if ( '9' == c ) nine++;
            helper(prefix+c, res, level+1);
        }

        nine--;

    }

private:
    string sp = "0123456789";
    int num;    
    int start;  // 控制字符串左边边界, 即删除高位0
    int nine;   // 记录数字9的个数
};


int main()
{

    Solution so;
    int n = 2;
    so.printNumbers(n);

    //output: 00 01 02 03 ... 99
    return 0;
}