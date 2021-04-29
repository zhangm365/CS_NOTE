


#include <iostream>
#include <string>

using namespace std;


int main()
{

    string str( "hello world" );
    for( char c : str )
        c = 'X';
    
    cout << str << endl;

    decltype(str.size()) index = 0;
    while(index < str.size())
        str[index++] = 'X';
    cout << str << endl;

    
}