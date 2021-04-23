



#include <iostream>


using namespace std;


int main()
{

    int i = 42;

    int *const pi = &i;
    cout << "const pointer = " << *pi << endl;

    int i2 = 10;

    //pi = &i2;   // error: assignment of read-only variable ‘pi’
    
    const int i3 = 60;
    const int *const p2 = &i3; // p2是一个指向常量对象的常量指针 
    
    cout << "const const pointer = " << *p2 << endl;
    
    return 0;

}