

//测试引用
#include <bits/stdc++.h>




class Solution
{
    // static class variable
    public:
        static int i;

        // 静态成员函数
        static void printMsg() 
        {
            printf("Welcome to Apple!\n");
        }


        Solution()
        {
                //do nothing
        };

};


// void demo()
// {
//     // static variable
//     static int val = 0; 
//     printf("val = %d\n", val);
//     val++;

// }


// initial the static variable
int Solution::i = 2;

int main()
{

    /* double a = 4, b = 5;
    // double & r1 = a;
    // double & r2 = r1; // r2也引用 a
    // r2 = 10;
    // cout << a << endl; // 输出 10
    // r1 = b; // r1并没有引用b, 只是用b的值赋值到r1
    // cout << a << endl; //输出 5

    //const int num = 0;

    //int * const ptr = &num;    //invalid conversion from 'const int*' to 'int*'
    // for(int i = 0; i < 5; ++i)
    //     demo();
    */

    Solution s1;
    s1.i = 2;
    Solution s2;    // error
    s2.i = 3; 

    printf("%d %d\n", s1.i, s2.i);
    Solution::printMsg();
    s1.printMsg();
    s2.printMsg();
    return 0;

}
