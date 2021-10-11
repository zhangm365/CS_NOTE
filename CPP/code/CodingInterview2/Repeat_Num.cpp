

//查找一个数组中的重复数字。数组大小为n, 数组中元素均在0~n-1之间

#include <bits/stdc++.h>

using namespace std;


//方法1: 建立一个标记访问数组，则判断相同元素值的标记数组是否被访问过
class RepeatNum
{
    public:
        int FindRepeatNum(vector<int> &arr);
};


int RepeatNum::FindRepeatNum(vector<int> &arr)
{

    bool flag[arr.size()];    //空间复杂度O(n)
    memset(flag, false, arr.size());

    for(int i = 0; i < arr.size(); i++)
    {
        if(flag[arr[i]])
            return arr[i];
        else
            flag[arr[i]] = true;    //标记arr[i]已访问
    }

    return -1;

}


//方法2：如果将数组排序后，那么元素arr[i]将存在下标i的位置。所以，当数组中含有重复元素时，有些下标会出现多个元素，有些位置就没有元素。


class RepeatNum2
{
    public:
        int FindRepeatNum(vector<int> &arr);
};

int RepeatNum2::FindRepeatNum(vector<int> &arr)
{

    for(int i = 0; i < arr.size(); i++)
    {
        int temp;
        while(i != arr[i])
        {
            
            if(arr[i] == arr[arr[i]])
            {
                return arr[i];
            }

            //swap
            temp = arr[i];
            arr[i] = arr[temp];
            arr[temp] = temp;
        }

    }

    return -1;
}


int main()
{

    RepeatNum2 CArr;
    vector<int> arr;
    int x;
    while(cin >> x)
    {
        arr.push_back(x);
        if(cin.get() == '\n')
            break;
    }
    //arr.reserve(20);
    cout << arr.capacity() << " " << arr.size() << endl;
    x = CArr.FindRepeatNum(arr);
    cout << "The RepeatNum is : " << x << endl;

    return 0;
    
}