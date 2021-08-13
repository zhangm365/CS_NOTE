
#include <iostream>
#include <memory>

using namespace std;

unique_ptr<int> get_unique()
{
  
    unique_ptr<int> p( new int(10) );

    return p;                   // 1    move
    //return move( p );         // 2
}

int main()
{
    unique_ptr<int> p = get_unique();

    cout << *p << endl;
    return 0;
}