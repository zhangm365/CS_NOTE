



#include <iostream>
#include <string>

using namespace std;


const string& shorterString( const string &s1, const string &s2 )
{

    return ( ( s1.size() < s2.size() ) ? s1 : s2 );

}


int main()
{


    string s1("hello world");
    string s2("hello");
    auto s = shorterString(s1, s2);
    cout << s << endl;

    return 0;

}