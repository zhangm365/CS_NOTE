

#include <iostream>

#include <string>

using namespace std;



class Shape
{

    public:
        typedef pair<double, double>  Coordinate;

        Shape() = default;
        Shape( const string &n ) : name(n) {}

        virtual double area() const = 0;
        virutal double perimeter() const = 0;

        virtual ~Shape() {}

    private:
        string name;
};


class Rectangle : public Shape
{
    public:

        Rectangle() = default;

        Rectangle( 
                    const string &str, 
                    Coordinate &_a, 
                    Coordinate &_b, 
                    Coordinate &_c, 
                    Coordinate &_d      
                ) : Shape(str), a(_a), b(_b), c(_c), d(_d) {}
    
        virtual ~Rectangle() = default;

    protected:
        Coordinate a;
        Coordinate b;
        Coordinate c;
        Coordinate d;

};

class Square : public Rectangle
{
    public:

        Square() = default;
        Square(
                const string &str, 
                Coordinate &_a, 
                Coordinate &_b, 
                Coordinate &_c, 
                Coordinate &_d      
                ) : Rectangle( str, _a, _b, _c, _d ) {}

        virtual ~Square() = default;

};


int main()
{
    
    return 0;
    
}