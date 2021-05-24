


#include <iostream>
#include <fstream>

#include <vector>

using namespace std;


int main()
{

    vector<int> vec = { 1, 2, 3, 4, 5, 6 };

    const int sz = vec.size();

    // int *r = &sz;

    // cout << sz << endl;

    ifstream file("hello world"); // ok

    // ifstream file = "hello world";  // error : conversion from ‘const char [12]’ to non-scalar type ‘std::ifstream’ {aka ‘std::basic_ifstream<char>’} requested

    return 0;

}




