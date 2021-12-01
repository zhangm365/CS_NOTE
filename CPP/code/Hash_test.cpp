

#include<bits/stdc++.h>

using namespace std;


int main()
{

    void *p = (void *)(new int(100));


    cout << hash<int>()(123) << endl;    // 123
    cout << hash<long>()(123L) << endl;    // 123
    cout << hash<char>()('A') << endl;    // 65
    cout << hash<string>()(string("hello")) << endl;    // 2762169579135187400
    cout << hash<const char*>()("world") << endl;    // 4214954
    cout << hash<double>()(3.141592653) << endl;    // 14104971651001058672

    cout << hash<void*>()(p) << endl;    // 7477072
    
    return 0;
}