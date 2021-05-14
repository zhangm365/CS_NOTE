

#include <iostream>
#include <cstring>

using namespace std;


int main()
{


    // string s1 = "hello";
    // string s2 = "hallo";

    // if( s1 < s2 ) cout << "string s1 < string s2\n";
    // else if( s1 > s2 ) cout << "string s1 > string s2\n";
    // else cout << "s1 == s2\n"; 

    const char s1[] = "hello";
    const char s2[] = "hallo";

    if( strcmp(s1, s2) > 0 ) cout << "s1 > s2\n";
    else if( strcmp(s1, s2) < 0 ) cout << "s2 < s1" << endl;
    else cout << "s1 == s2" << endl; 

    return 0;

}
