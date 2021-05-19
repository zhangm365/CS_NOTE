


#include "Chapter6.h"
#include <iostream>

using namespace std;


int main()
{

    int n;
    while( cin >> n )
    {
        int ret = 1;
        try
        {
            n = myabs(n);
            ret = fact(n);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return -1;
        }

        printf("%d! = %d\n", n, ret);
    }

    return 0;

}