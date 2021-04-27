

#include <iostream>

#include <string>


using namespace std;



int main()
{



    // read two strings and report whether the strings are equal
    // If not, report which of the two is larger.


    string str1, str2;
    while (cin >> str1 >> str2)
    {
        if (str1 == str2)
            cout << "The two strings are equal." << endl;
        else
            cout << "The larger string is " << ((str1 > str2) ? str1 : str2);
    }



    #if 0
    string s1, s2;
    cin >> s1 >> s2;

    if( s1 == s2 ) cout << "s1 == s2" << endl;
    else if( s1 > s2 )
    {
        cout << "the bigger string is " << s1 << endl;
    }
    else
    {
        cout << "the bigger string is " << s2 << endl;
    }

    cout << "---------" << endl;

    if( s1.size() == s2.size() )
    {
        cout << "s1.size() == s2.size()" << endl;
    }
    else if( s1.size() > s2.size() )
    {
        cout << "s1.size() > s2.size() " << s1 << endl;
    }
    else
    {
        cout << "s1.size() < s2.size() " << s2 << endl;
    }
    
    #endif

    return 0;

}