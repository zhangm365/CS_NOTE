

#include <iostream>

using namespace std;

class Base
{

    public:
        virtual void fun()
        {
            cout << "virtual Base::fun" << "\n";
            
        }
};

class D1 : public Base
{


    public:
        void fun(int)
        {
            cout << "no-virtual D1::fun(int)" << "\n";
            
        }

        virtual void f2()
        {
            cout << "virtual D1::f2()" << "\n";
        }
};


class D2 : public D1
{
    public:
        void fun()
        {
            cout << "D2::fun()" << "\n";
            
        }

        void fun(char)
        {
            cout << "D2::fun(char)" << "\n";
            
        }

        void fun2()
        {
            cout << "D2::fun2()" << "\n";
        }
};



int main()
{


    Base bobj;
    D1 d1obj;
    D2 d2obj;

    Base *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;

    bp1->fun(); // Base::fun()
    bp2->fun(); // Base::fun()
    bp3->fun(); // D2::fun()

    // d1obj.fun(); // error

    d2obj.fun();    // D2::fun()
    return 0;

}



