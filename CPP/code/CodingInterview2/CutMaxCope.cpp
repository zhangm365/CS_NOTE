

// 剪绳子https://leetcode-cn.com/problems/jian-sheng-zi-lcof/

//动态规划

#include <bits/stdc++.h>


using namespace std;

class Solution
{
    public:
        int cuttingRope(int length);


};

int Solution::cuttingRope(int length)
{

    if(length < 2)
        return 0;
    if(length == 2)
        return 1;
    if(length == 3)
        return 2;

    int *products = new int[length+1];

    products[0] = 0;
    products[1] = 1;
    products[2] = 2;
    products[3] = 3;

    int max = 0;
    for(int i = 4; i <= length; ++i)
    {
        max = 0;
        for(int j = 1; j <= i/2; ++j)
        {
            int ret = products[j]*products[i-j];
            if(ret > max)
                max = ret;
        }

        products[i] = max;
    
    }

    max = products[length];

    delete [] products;
    
    return max;

}




int main()
{

    Solution So;
    int n;
    while(scanf("%d", &n))
    {
        printf("%d\n", So.cuttingRope(n));
    }


    return 0;

}