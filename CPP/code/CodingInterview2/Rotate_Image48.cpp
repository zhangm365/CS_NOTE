

// https://leetcode-cn.com/problems/rotate-image/

// 旋转图像: 即旋转二维矩阵

#include <bits/stdc++.h>


class Solution
{
    public:
        void rotate(std::vector<std::vector<int> > &matrix);

};

void Solution::rotate(std::vector<std::vector<int> > &matrix)
{
            
    int m = matrix.size(), n = matrix[0].size();

    // 1. 矩阵转置
    for( int i = 0; i < m; ++i)
    {
        for(int j = 0 ; j < i; ++j)
        {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }

    // 2. 水平镜像对称
    for( int i = 0; i < m; ++i)
    {
        for(int j = 0 ; j < n/2 ; ++j)
        {
           
            std::swap(matrix[i][j], matrix[i][n - j - 1]);               
            
        }

    }


}


int main()
{

    std::vector<std::vector<int> > matrix = { {5, 1, 9,11}, {2, 4, 8,10}, {13, 3, 6, 7}, {15,14,12,16}};
    Solution So;
    So.rotate(matrix);
    
    int m = matrix.size(), n = matrix[0].size();

    for( int i = 0; i < m; ++i)
    {
        for(int j = 0 ; j < n; ++j)
        {
            if(j != 0) printf(" ");
            printf("%d", matrix[i][j]);
            
        }
        printf("\n");
    }
    return 0;
}