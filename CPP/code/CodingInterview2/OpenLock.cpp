


// 打开密码锁

// https://leetcode-cn.com/problems/open-the-lock/

#include <bits/stdc++.h>


class Solution
{
    public:

        /* 主函数: 求解解锁的最少旋转次数 */
        int openLock(std::vector<std::string>& deadends, std::string target);

        // 向上拨动一次
        std::string PlusOne(std::string s, int j);

        // 向下拨动一次
        std::string MinusOne(std::string s, int j);

};


int Solution::openLock(std::vector<std::string>& deadends, std::string target)
{
    
    // 哈希表存储死亡密码, 方便快速查找
    //std::unordered_set<std::string> DeadSet( deadends.begin(), deadends.end() );        // init by range

    // 记录已经访问的密码
    std::unordered_set<std::string> visited( deadends.begin(), deadends.end() );

    // 从起点开始进行广度优先搜索
    int step = 0;
    // BFS 核心数据结构: 队列
    std::queue<std::string> Q;
    Q.push("0000");    //锁的初始数字

    //visited.insert("0000");

    while(!Q.empty())
    {

        int sz = Q.size();
        for(int i = 0; i < sz; ++i)
        {                                                        
            // 队头元素出队
            std::string cur = Q.front();
            Q.pop();
            
            /* 判断是否到达终点 */
            // 1. 是否遇到死亡密码
            if( visited.find(cur) != visited.end() )
                continue;

            // 2. 找到了密码
            if(cur == target)
                return step;

            visited.insert(cur); // 标记被访问

            // 将当前节点的相邻节点入队
            for( int i = 0 ; i < 4 ; ++i )
            {

                // 向上拨动一次
                std::string up = PlusOne(cur, i);
                // 还没有被访问过, 则加入队列中和已访问集合中
                if(visited.find(up) == visited.end())
                {
                    Q.push(up);
                    //visited.insert(up); // 标记被访问
                }

                // 向下拨动一次
                std::string down = MinusOne(cur, i);
                // 
                if(visited.find(down) == visited.end())
                {
                    Q.push(down);
                    //visited.insert(down);
                }

            }             

        }

        // 更新步数
        step++;

    }

    // 最后没找到
    return -1;

}


// 向上拨动一次
std::string Solution::PlusOne(std::string s, int j)
{
    if(!s.empty())
    {
    
        std::string tmp(s);

        if(tmp[j] == '9')
            tmp[j] = '0';
        else
            tmp[j] += 1;


        return tmp;
    
    }

    return s;

}


// 向下拨动一次
std::string Solution::MinusOne(std::string s, int j)
{

    if(!s.empty())
    {
        std::string tmp(s);
        if(tmp[j] == '0')
            tmp[j] = '9';
        else
            tmp[j] -= 1;

        return tmp;

    }

    return s;

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