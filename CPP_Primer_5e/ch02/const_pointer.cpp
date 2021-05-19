



#include <iostream>


using namespace std;


int main()
{

    int i = 42;

    int *const p1 = &i;
    // *p1 = 3; // true
    cout << "const pointer = " << *p1 << endl;
    
    int i2 = 10;
    const int *p2 = &i2;
    
    //p1 = &i2;   // error: assignment of read-only variable ‘pi’
    
    const int i3 = 60;
    const int *const p3 = &i3; // p2是一个指向常量对象的常量指针 
    
    cout << "const const pointer = " << *p3 << endl;
    
    return 0;

}