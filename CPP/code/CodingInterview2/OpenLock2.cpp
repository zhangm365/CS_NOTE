

#include <bits/stdc++.h>

class Solution
{
    public:
        int openLock(std::vector<std::string>& deadends, std::string target);

         // 向上拨动一次
        std::string PlusOne(std::string s, int j);

        // 向下拨动一次
        std::string MinusOne(std::string s, int j);

};


int Solution::openLock(std::vector<std::string>& deadends, std::string target)
{
    // 死亡密码集合
    std::unordered_set<std::string> DeadSet( deadends.begin(), deadends.end() );
    // 标记已访问密码
    std::unordered_set<std::string> visited;

    visited.insert("0000");

    // 使用集合, 快速判断密码是否存在 
    std::unordered_set<std::string> q1;
    std::unordered_set<std::string> q2;

    q1.insert("0000");
    q2.insert(target);

    int step = 0;

    while( !q1.empty() && !q2.empty() )
    {

        std::unordered_set<std::string> tmp;    //临时集合

        for( std::unordered_set<std::string>::iterator cur = q1.begin(); cur != q1.end(); ++cur )
        {
            // 判断是否到达终点
            if(DeadSet.find(*cur) != DeadSet.end())
            {
                continue;
            }

            if (q2.find(*cur) != q2.end())
            {
                return step;
            }
            
            visited.insert(*cur);

            for(int i = 0 ; i < 4; ++i)
            {
                
                std::string up = PlusOne(*cur, i);
                if( visited.find(up) == visited.end())
                {
                    tmp.insert(up);
                }

                std::string down = MinusOne(*cur, i);
                if( visited.find(down) == visited.end() )
                {
                    tmp.insert(down);
                }

            }

        }

        step++;
        q1 = q2;
        q2 = tmp;


    }

    return -1;

}


std::string Solution::PlusOne(std::string s, int j)
{
    std::string tmp(s);
    if(tmp[j] == '9')
        tmp[j] = '0';
    else
    {
        tmp[j] += 1;
    }
    
    return tmp;

}

std::string Solution::MinusOne(std::string s, int j)
{
    std::string tmp(s);
    if(tmp[j] == '0')
        tmp[j] = '9';
    else
    {
        tmp[j] -= 1;
    }
    
    return tmp;

}

int main()
{

    std::vector<std::string> deadends = {"0201","0101","0102","1212","2002"};
    std::string target  = "0202";
    Solution So;
    int ret = So.openLock(deadends, target);
    printf("ret = %d\n", ret);

    return 0;
}