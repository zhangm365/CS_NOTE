


// 合并区间
// https://leetcode-cn.com/problems/merge-intervals/

# include<bits/stdc++.h>

class Solution
{

    public:
        std::vector<std::vector<int> > merge(std::vector<std::vector<int> > &intervals);


};



std::vector<std::vector<int> > Solution::merge(std::vector<std::vector<int> > &intervals)
{


    if(intervals.empty()) return {{0}, {0}};

    // 结果区间集合
    std::vector<std::vector<int> > res;

    // 1.排序：按起点升序排序
    sort(intervals.begin(), intervals.end(), [](std::vector<int> &u, std::vector<int> &v)->bool {

            return ( u[0] < v[0] );
    
    });

    int n = intervals.size();

    // 插入第一个区间
    res.push_back(intervals[0]);

    for(int i = 1; i < n; ++i)
    {

        std::vector<int> cur = intervals[i];
        
        // 访问res中的最后一个区间
        std::vector<int> &last = res[res.size()-1];

        //printf("before: %d\n", last[1]);
        // 存在相交区间
        if( cur[0] <= last[1] )
        {
            // 更新相交区间的最大end
            last[1] = std::max(last[1], cur[1]);
            //printf("after: %d\n", last[1]);

        }
        else    // 处理下一个待合并区间
        {
            res.push_back(cur);
        }
        
    }


    return res;

}



int main()
{

    std::vector<std::vector<int> > intervals = { {1, 3}, {2, 6}, {8, 10}, {15, 18} };

    Solution So;

    std::vector<std::vector<int> > res = So.merge(intervals);

    for(int i = 0 ; i < res.size(); ++i)
    {
        printf("[");
        for(int j = 0; j < res[0].size(); ++j)
        {
            if(j != 0)  printf(",");
            printf("%d", res[i][j]); 
        }
        printf("] ");    

    }

    return 0;
}