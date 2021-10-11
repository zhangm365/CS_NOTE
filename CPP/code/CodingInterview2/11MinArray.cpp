

//查找旋转数组中的最小值

#include <bits/stdc++.h>

using namespace std;


class Solution 
{
    public:
        int minArray(vector<int>& numbers); 
        
        
};

int Solution::minArray(vector<int>& numbers)
{
            
    if(numbers.empty()) return -1;
    
    int left = 0, right = numbers.size()-1;
    int mid;
    while(left < right)
    {
        mid = (left + right)/2;
        if( numbers[mid] > numbers[right])
        {
            left = mid + 1;
        }
        else if( numbers[mid] < numbers[right] )
        {
            right = mid;
        }
        else
        {
            right--;
        }
        
    }
    
    return numbers[left];

}



int main()
{

    Solution So;
    vector<int> arr;
    printf("Please input the number of N: ");
    int n, x;
    while(scanf("%d", &n) == 1)
    {
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &x);
            arr.push_back(x);
        }

        x = So.minArray(arr);
        printf("the min number is %d\n", x);
        arr.clear();

    }
    
    return 0;

}