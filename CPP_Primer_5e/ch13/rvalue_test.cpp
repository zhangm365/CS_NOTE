

#include <iostream>
#include <vector>

using namespace std;


int main()
{

    int a = 1;
    int &r = a;
  
    decltype(r) x  = a;

    int &&rr1 = 29;
    // int &&rr2 = rr1; error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’

    decltype(rr1) y = 1;
    
    int &&rr3 = std::move(a);
    cout << rr3 << endl;

    int &r1 = rr1;  // ok

    vector<int> vec(20);

    int &r2 = vec[0];

    return 0;

}