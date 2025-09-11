

// conversion function
#include <bits/stdc++.h>

class Fraction
{

    public:
        Fraction(double num, double den=1) : m(num), n(den) {}
        operator double() const 
        {
            return (double)( m / n );
        }


    private:
        double m, n;

};




int main()
{

    Fraction f(3, 2);

    // 转换函数, f(3,2)这个对象被转换成double对象
    double d = 4 + f;
    printf("d = %lf\n", d);

    return 0;
}