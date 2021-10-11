

// 构造函数的重载：多个构造函数

#include <bits/stdc++.h>


class Complex
{
    public:
        Complex(double r = 0, double i = 0) : real(r), image(i){}
        //Complex() : real(0), image(0){}
        void getValue() const {std::cout << real << " " << image << std::endl;}
    private:
        double real, image;


};



int main()
{
    Complex c1(1, 1);
    Complex c2;
    c1.getValue();
    c2.getValue();
    return 0;
}