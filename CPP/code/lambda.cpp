

#include <bits/stdc++.h>

using namespace std;


int main()
{

    int id = 0;

    /*
    auto f = [id](){

        cout << "id = " << id << endl;
        ++id;   // error: increment of read-only variable 'id'
        
    };
    */

    auto f = [&id]( int param ) mutable {

        cout << "id = " << id << endl;
        ++id;   // error: increment of read-only variable 'id'
        ++param;
        cout << "param = " << param << endl;
    };

    id = 42;
    f(3);
    f(3);
    f(3);

    cout << "After lambda id = " << id << endl;

    return 0;

}