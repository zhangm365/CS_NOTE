

#include <iostream>

using namespace std;



int main()
{

    // 使用转义字符输出控制符：\115:M, \12:\n
    cout << "\62" << "\115\12";

    cout << "\62" << "\t\115\x0A";
    

    return 0;

}