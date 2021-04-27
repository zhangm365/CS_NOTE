

#include<iostream>

#include <string>


using namespace std;



int main()
{

    string s1, s2;

    while( cin >> s1 )
        s2 += (s2.empty() ? "" : " ") + s1;
    
    cout << s2 << endl;


    return 0;

}