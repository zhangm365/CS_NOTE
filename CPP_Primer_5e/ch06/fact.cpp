

#include <iostream>

#include "Chapter6.h"


int fact( int n )
{

    if( n < 0 ) 
    {
        throw std::runtime_error("Input value can't a negative number!");
    }

    int ret = 1;
    while( n > 1 )
    {
        ret *= n;
        n--;
    }

    return ret;

}

