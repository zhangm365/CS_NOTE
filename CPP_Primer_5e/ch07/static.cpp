


#include<iostream> 
using namespace std; 

class Apple 
{ 
    public: 
        Apple() 
        { 
            // Do nothing 
        }; 
    
        static int i;   // 声明


}; 

int Apple::i;

int main() 
{ 
    Apple obj1; 
    Apple obj2; 
    obj1.i = 2; 
    obj2.i = 3; 

    int i = 0;

    const int *p = &i;

    // int * const cp = p; // error: invalid conversion from ‘const int*’ to ‘int*’ [-fpermissive]

    const int * const cp = p;
    
    const int j = 2;
    p = &j;
    // int * const cp1 = &j; // error

    cout << *p << " " << *cp << endl;
    // prints value of i 
    cout << obj1.i << " " << obj2.i << endl; 
    
    return 0;


} 