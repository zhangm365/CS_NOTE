


#include <iostream>

#include <string>

#include <vector>


using namespace std;


int main()
{

    
    vector<string> vec;

    string str;

    while( cin >> str )
    {
        for( auto &c : str ) c = toupper(c); // 转为大写
        vec.push_back(str);
    }

    for( auto str : vec )
        cout << str << endl;

    return 0;

}