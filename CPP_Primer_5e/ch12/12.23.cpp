



#include <iostream>

#include <memory>

#include <cstring>

#include <string>

using namespace std;


int main()
{


    // char a[] = "hello";
    // char b[] = "world";

    // int n = strlen(a) + strlen(b);

    // char *ret = new char[n+1];

    // strcpy(ret, a);
    // strcat(ret, b);
    // ret[n] = '\0';

    // cout << ret << endl;
    // delete [] ret;

    string s1 = "hello";
    string s2 = "world";

    string ret = s1 + s2;

    cout << ret << endl;

    return 0;

}