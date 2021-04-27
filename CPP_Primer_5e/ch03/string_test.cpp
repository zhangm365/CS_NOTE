




#include <iostream>

#include <string>

using namespace std;




int main()
{


    string s;
    // while( cin >> s )    // 遇到空白停止读入。空白[空格, 换行符, 制表符等]
    // while( getline(cin, s) )    // 读取一行, 直到遇到换行符(换行符也读进来)
    // {
    //     cout << s.size() << endl;
    //     cout << s << endl;  // 逐个输出单词
    // }

    // s.append('a');    // error: no matching function for call to ‘std::__cxx11::basic_string<char>::append(char)’
    s.append(1,'a');

    // string s1 = "hello" + "b";  // error: invalid operands of types ‘const char [6]’ and ‘const char [2]’ to binary ‘operator+’
    /*|     string s1 = "hello" + "b";
      |                 ~~~~~~~ ^ ~~~
      |                 |         |
      |                 |         const char [2]
      |                 const char [6]
    */

    string s1 = "hello", s2 = "world";

    string s3 = "zhang" + 'a';  // s3 is a empty string;

    // cout << s3.size() << " " << s3 << endl;


    return 0;

}