


#include <iostream>
#include <string>

using namespace std;


inline bool isShorter( const string &s1, const string &s2 )
{

    return s1.size() < s2.size();

}



int main()
{


    string s1("zhang");
    string s2("hello");

    // cout << __func__ << " " << __LINE__ << endl;
    
    cout << isShorter(s1, s2) << endl; 

    return 0;

}