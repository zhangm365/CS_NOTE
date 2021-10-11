



#include <bits/stdc++.h>


class Base
{

    public:
        inline virtual void foo()
        {
            std::cout << "Base::foo()" << std::endl;
        }

        virtual ~Base()
        {
            std::cout << "~Base()" << std::endl;
        }

};

class Derived : public Base
{

    public:

        void foo() override
        {
            std::cout << "Derived::foo()" << std::endl;
        }

        ~Derived()
        {
            std::cout << "~Derived()" << std::endl;
        }

};



int main()
{

    Base b;
    b.foo();

    Base *ptr = new Derived();
    ptr->foo();

    //
    delete ptr;
    ptr = nullptr;

    return 0;

}