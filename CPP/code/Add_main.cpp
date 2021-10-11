



#include <iostream>

extern "C"
{
    #include "Add.h"  
}
  


int main()
{

    int x = 2, y = 3;
    int res = add(x, y);

    printf("res = %d\n", res);

    return 0;


}