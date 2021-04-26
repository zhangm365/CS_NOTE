




#include <iostream>

#include <string>

using namespace std;




int main()
{


    string s;
     while( cin >> s )    // 遇到空白停止读入。空白[空格, 换行符, 制表符等]
    //while( getline(cin, s) )    // 读取一行, 直到遇到换行符(换行符也读进来)
    {
        cout << s.size() << endl;
        cout << s << endl;  // 逐个输出单词
    }
        


    return 0;

}