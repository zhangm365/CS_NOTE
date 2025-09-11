



// assert用法

#define NDEBUG  // disable the assert, it is before the Header File  

#include <bits/stdc++.h> 


int main() 
{ 
    int x = 7; 

    /*  Some big code in between and let's say x  
    is accidentally changed to 9  */
    x = 9; 

    // Programmer assumes x to be 7 in rest of the code 
    assert(x==7); 

    /* Rest of the code */
     std::cout << "x = " << x << std::endl;

    return 0; 

} 