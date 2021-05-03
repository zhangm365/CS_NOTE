

#include<bits/stdc++.h>

const int N = 1E9 + 7;

long numWays(int n, int k) {

    if ( n <= 1 ) return k;

    long *dp = new int[n];
    dp[0] = k;
    dp[1] = k*k;

    for (int i = 2; i < n; i++) 
    {
        dp[i] = (dp[i-1] * (k-1) + dp[i-2] * (k-1)) % N;
    }

    long ret = dp[n-1];

    delete [] dp;

    return ret;
  
}



int main()
{
    
    int n, k;
    scanf("%d%d", &n, &k);

    long ret = numWays(n, k);

    

    printf("ret = %ld\n", ret);
    
    return 0;


}
   


