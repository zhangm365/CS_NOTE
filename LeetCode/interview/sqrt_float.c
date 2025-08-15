
// 求一个浮点数的平方根：二分法

#include <stdio.h>


float func( float x )
{


    float e = 0.0001;
    float left = 0, right = x > 1 ? x : 1;

    float mid = ( left + right ) / 2;

    while( mid*mid - x > e || mid*mid - x < -e )
    {
        //printf("%.lf\n", mid);
        if( mid*mid - x > e )
        {
            right = mid;
        }
        else if( mid*mid - x < -e )
        {
            left = mid;
        }
        

        mid = ( left + right ) / 2;

    }

    return mid;

}


int main()
{

    float x;

    while (scanf("%f", &x) == 1)
    {
        
        printf("%f\n", func(x));
    }
    

    return 0;

}