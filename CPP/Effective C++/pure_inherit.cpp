
#include <bits/stdc++.h>

using namespace std;

class Shape {

public:
    virtual void draw() = 0;
    virtual void error(const string &msg);
    int objectID() const;
};

void Shape::draw()
{
    cout << "Shape::draw()";
}

void Shape::error(const string &msg)
{
    cout << msg;
} 

int Shape::objectID() const
{
    cout << "Shape::objectID()";
    return 0;

}

class Rectangle: public Shape {

public:
    void draw();
    

};


void Rectangle::draw()
{
    cout << "Rectangle::draw()";

}


int main()
{

    // Shape * ps = new Shape;
    Shape *p1 = new Rectangle;
    Rectangle *r1 = new Rectangle;
    p1->draw();
    p1->objectID();
    cout << "\n";

    p1->Shape::draw();

    return 0;
}