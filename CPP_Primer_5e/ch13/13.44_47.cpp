

#include "mystring.h"

#include <iostream>

#include<vector>

using namespace std;



void foo( String str )
{

    cout << str.c_str() << "\n";

}


void bar( const String &str )
{
    cout << str.c_str() << "\n";
}

String baz()
{
    String ret("hello");
    return ret;
}


int main()
{

    char text[] = "world";

    String s0;
    cout << sizeof(String) << "\n";
    String s1("zhang");

    String s2(s0);
    String s3 = s1;

    String s4(text);

    s2 = s1;

    foo(s1);
    bar(s1);

    foo("hello string");

    bar("hello string");

    String s5 = baz();

    vector<String> strVec;
    strVec.push_back(s0);

    strVec.push_back(s1);

    strVec.push_back(s2);

    strVec.push_back(s3);
    strVec.push_back(s4);
    strVec.push_back(s5);

    strVec.push_back("good offer");

    for( const auto &str : strVec )
        cout << str.c_str() << "\n";
    
    cout << strVec.size() << " " << strVec.capacity() << endl;
    return 0;

}

