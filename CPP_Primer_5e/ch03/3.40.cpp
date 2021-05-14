

#include <iostream>

#include <cstring>

using namespace std;


int main()
{

    char s1[20] = "hello";
    const char s2[] = "world";

    char ret[100] = "zhang";
    
    strcat(s1, s2); // s1 后面追加s2
    strcpy(ret, s1);    // s1覆盖ret的内容

    cout << ret << endl;

    return 0;

}