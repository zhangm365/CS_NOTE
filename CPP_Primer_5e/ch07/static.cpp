


#include<iostream> 
using namespace std; 

class Apple 
{ 
public: 
    static int i; 

    Apple() 
    { 
        // Do nothing 
    }; 
}; 

 int Apple::i = 2;

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
    // int * const cp1 = &j;

    cout << *p << " " << *cp << endl;
    // prints value of i 
    cout << obj1.i<<" "<<obj2.i; 

} 