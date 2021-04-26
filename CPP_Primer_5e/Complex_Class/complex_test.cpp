

#include "complex.h"

#include <bits/stdc++.h>

int main()
{

    complex c1(2, -1);
    complex c2(3, 1);
    //c1 += c2;
    //c1 -= c2;
    c1 *= c2;
    std::cout << c1 << std::endl;
    //std::cout << c1+5 << std::endl;
    return 0;
}