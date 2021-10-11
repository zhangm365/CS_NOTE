

//斐波那契数列..从下到上计算
#include <bits/stdc++.h>


typedef long long ll;
const int M = 1E9 + 7;

class Solution {
    public:
        ll fib(int n) 
        {
            ll ret = 0;
            if(n == 0)  ret = 0;
            if(n == 1)  ret = 1;

            ll x0 = 0, x1 = 1;
            for(int i = 2; i <= n; ++i)
            {

                ret = (x0 + x1) % M;                    
                x0 = x1;
                x1 = ret;
            }
        

            return ret ;
        }        

};



int main()
{
    Solution So;
    int n;
    ll ret;
    printf("Please input the value of n:"); 
    while(scanf("%d", &n) == 1)
    {
        
        ret = So.fib(n);
        printf("ret = %d\n", ret);
        char c;
        scanf("%c", &c);
        if(c == 'q')
            break;

    }
    
    return 0;

}