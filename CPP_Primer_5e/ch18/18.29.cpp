

/*
    虚继承
*/



#include <iostream>

using namespace std;

class Class 
{
    public:
        Class() { cout << "Class() default ctor\n"; }
        ~Class() { cout << "~Class dtor\n"; }

};

class Base : public Class
{
    public:
        Base() { cout << "Base() default ctor\n"; }
        ~Base() { cout << "~Base() dtor\n"; }
};

class D1 : virtual public Base
{
    public:
        D1() { cout << "D1() default ctor\n"; }
        ~D1() { cout << "~D1() dtor\n"; }
};


class D2 : virtual public Base
{
    public:
        D2() { cout << "D2() default ctor\n"; }
        ~D2() { cout << "~D2() dtor\n"; }
};


class MI : public D1, public D2
{
    public:
        MI() { cout << "MI() default ctor\n"; }
        ~MI() { cout << "~MI() dtor\n"; }
};

class Final : public MI, public Class
{
    public:
        Final() { cout << "Final() default ctor\n"; }
        ~Final() { cout << "~Final() dtor\n"; }
};


int main()
{

    Final fobj;
    
    Base *pb;
    Class *pc;
    MI *pmi;
    D2 *pd2;

    // pb = new Class; // error: invalid conversion from ‘Class*’ to ‘Base*’ [-fpermissive]
    // pc = new Final; // error: ‘Class’ is an ambiguous base of ‘Final’
    // pmi = pb; // error: invalid conversion from ‘Base*’ to ‘MI*’ [-fpermissive]
    pd2 = pmi; 


    return 0;

}