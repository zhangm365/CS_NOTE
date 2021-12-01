

#include "complex.h"

#include <bits/stdc++.h>

int main()
{

    complex c1(2, 2);
    complex c2(1, 1);
    //c1 += c2;
    //c1 -= c2;
    c1 /= c2;
    std::cout << c1 << std::endl;
    //std::cout << c1+5 << std::endl;
    return 0;
}