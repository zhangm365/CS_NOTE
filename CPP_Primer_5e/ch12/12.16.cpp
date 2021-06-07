


#include <iostream>

#include <string>

#include <memory>

using namespace std;



int main()
{


    unique_ptr<string> p1(new string("hello world"));

    // unique_ptr<string> p2(p1);  //error: unique_ptr( const unique_ptr& ) = delete;

    unique_ptr<string> p3;

    // p3 = p1;    // error : unique_ptr& operator= ( const unique_ptr& ) = delete;

    
    return 0;

}


