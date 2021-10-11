


//全排列 https://leetcode-cn.com/problems/permutations/

#include <bits/stdc++.h>

class Solution
{
    public:
        //全局变量存储最后全部序列
        std::vector<std::vector<int> > res;

        /* 主函数，输入一组不重复的数字，返回它们的全排列 */
        void permute(std::vector<int> &nums) ;
        void backtrack(std::vector<int> &nums, std::vector<int> &track);

};

void Solution::permute(std::vector<int> &nums)
{
    // 记录「路径」
    std::vector<int> track ;
    //遍历决策树
    backtrack(nums, track);
    return ;
}


// 路径：记录在 track 中
// 选择列表：nums 中不存在于 track 的那些元素
// 结束条件：nums 中的元素全都在 track 中出现
void Solution::backtrack(std::vector<int> &nums, std::vector<int> &track) 
{
    // 触发结束条件
    if (track.size() == nums.size()) 
    {
        res.push_back(track);
        return;
    }

    for (int i = 0; i < nums.size(); i++)
    {
        // 排除不合法的选择
        std::vector<int>::iterator ite = find(track.begin(), track.end(), nums[i]);

        if (ite != track.end())
            continue;

        // 做选择
        track.push_back(nums[i]);
        // 进入下一层决策树
        backtrack(nums, track);
        // 取消选择
        track.pop_back();

    }

}


int main()
{
    int n, x;   
    printf("Please input the value of n:");
    scanf("%d", &n);
    std::vector<int> nums;
    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        nums.push_back(x);
    }
    
    //std::vector<std::vector<int> > res;
    Solution So;
    So.permute(nums);

    //printf("row = %d, col = %d\n", res.size(), res[0].size());
    for(int i = 0; i < So.res.size(); ++i)
    {
        for(int j = 0; j < So.res[0].size(); ++j)
        {
            if(j != 0) printf(" ");
            printf("%d", So.res[i][j]);
        }
            
        printf("\n");
    }


    return 0;
}