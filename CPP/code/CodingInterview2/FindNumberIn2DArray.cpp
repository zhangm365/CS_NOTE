

// https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/
//在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

/*
    首先选取数组中右上角的元素和要查找的值做比较，如果数组右上角的值大于被查找的值，则从待查找区域剔除选取元素这一列元素，否则剔除它的这一行元素。
*/
#include <bits/stdc++.h>
using namespace std;



class Solution {
    public:
        bool findNumberIn2DArray(vector<vector<int> >& matrix, int target) ;
};

bool Solution::findNumberIn2DArray(vector<vector<int> >& matrix, int target)
{
    bool found = false;
    int row, col;
    
    row = matrix.size(); //行数
    //判断动态二维数组是否为空
    if(row == 0) return false;

    col = matrix[0].size();   //列数

    if(row > 0 && col > 0)
    {
        int y = col - 1;
        int x = 0;

        while(x < row && y >=0 )
        {
            if(matrix[x][y] == target)
            {
                found = true;
                break;
            }
            else if(matrix[x][y] > target)
                --y;
            else
                ++x;
        }

    }
    
    return found;
}

int main()
{

    Solution Mt;
    
    vector<vector<int> >  matrix = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};

    bool found = Mt.findNumberIn2DArray(matrix, 5);
    
    if(found)
        printf("true\n");
    else
        printf("false\n");

    return 0;
}