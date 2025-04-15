

#include <bits/stdc++.h>

using namespace std;

/*
    @ 
    
    查找一个最小的整数，需要满足以下条件：
    1. 这个数，它至少有4个因子，这些因子必须都是素数。
    2. 同时要满足任何两个因子相差都不小于x
    

*/

#define MAX_SIZE 50000+10

// 素数表
int prime[MAX_SIZE];

//四个因数除去1和自己以外，找到两个满足题意的最小质数就ok了
int func(int x)
{
    
    int i, j;
    for(i = 1 + x; i < MAX_SIZE; i++)
    {
        if(prime[i] == 0)
        {
            break;
        }
    }

    for(j = i + x; j < MAX_SIZE; j++)
    {
        if(prime[j] == 0)
            break;
    }
    // printf("%d %d\n", i, j);
    return i * j;
}

int main()
{
    int n;
    cin >> n;

    //素数表：筛素数
    memset(prime, 0, sizeof(prime));
    prime[0] = 1;   // 1：非素数， 0：素数
    prime[2] = 0;

    for(int i = 2; i < MAX_SIZE; i++)
    {
        if(prime[i] == 1) continue;
        for(int j = 2; j * i < MAX_SIZE; j++)
        {
            prime[j*i] = 1;
        }
    }

    for(int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        cout<< func(k) << endl;
    }

    return 0;

}