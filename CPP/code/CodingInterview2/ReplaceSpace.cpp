


#include <bits/stdc++.h>

using namespace std;

class Solution
{
    public:
        string replaceSpace1(string str);
        string replaceSpace2(string str);

};

//方法1:在原字符串上操作：时间复杂度O(N)
string Solution::replaceSpace1(string str)
{

    if(str.empty()) //判断字符串是否为空
        return "";
           
    int old_len = str.size();   //字符串原来长度
    //printf("len = %d\n", old_len);
    int space_num = 0;

    for(auto i : str)
    {//统计字符串中空格的个数
        
        if(i == ' ') 
        {
            ++space_num;
        }

    }
    //printf("space_num = %d\n", space_num);
    //将空格替换后的长度
    int new_len = old_len + 2 * space_num;
    str.resize(new_len);    //重新修改str的长度
    //printf("new_len = %d, str.cap = %d\n", new_len, str.capacity());
    if(new_len > str.capacity())    return "";
    
    while(old_len >=0 && new_len > old_len)
    {
        //printf("%c %d\n",str[old_len], old_len);
        if(str[old_len] == ' ')
        {//如果是空格, 则进行替换
            str[new_len--] = '0';
            str[new_len--] = '2';
            str[new_len--] = '%';
            old_len--;
        }
        else
        {
            str[new_len--] = str[old_len--];
            
        }
        
    }

    return str;

}

//方法2:用新字符串保存结果字符串：时间和空间复杂度均为O(N)
string Solution::replaceSpace2(string str)
{

    if(str.empty()) //判断字符串是否为空
        return "";
           
    int old_len = str.size();   //字符串原来长度
    //printf("len = %d\n", old_len);
    
    string ret; //结果字符串
    
    for( auto i : str ) //遍历原始字符串
    {
        
        if(i == ' ')
        {//如果是空格, 则进行替换
            ret += "%20";
        }
        else
        {
            ret += i;
            
        }
        
    }

    return ret;

}


int main()
{
    Solution S;
    string str(" ");
    string ret;
    ret = S.replaceSpace2(str);
    cout << ret << endl;

    return 0;

}