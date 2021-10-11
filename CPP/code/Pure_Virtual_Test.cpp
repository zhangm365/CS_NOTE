

// 纯虚函数的那些事

#include <bits/stdc++.h>


// abstract type
class A
{

    public:
        // pure virtual function
        virtual void foo() = 0;
        // brief: 抽象类中成员函数可以调用纯虚函数
        void fa(){ this->foo(); }

        A()
        {

        }

        virtual ~A()
        {

        }


};


class B : public A
{
    public:
        // 派生类必须实现基类所有的纯虚函数才可以创建对象(非抽象类)
        void foo(){ std::cout << "Derived class implement the Pure_Virtual of base class" << std::endl; }
        

};


class Base
{

    public:
        Base(){ std::cout << "Constructor : Base" << std::endl; }
        // virtual Destructor function
        virtual ~Base() { std::cout << "Destructor : Base" << std::endl; }


};


class Derived : public Base
{

    public:
        Derived() { std::cout << "Constructor : Derived" << std::endl; }
        ~Derived() { std::cout << "Destructor : Derived" << std::endl; }
};


int main()
{

    // A C1;    //error: 含有纯虚函数的抽象类不可以创建对象
    // C1 *ptr = new C1(); 

    //A *ptr;    // 可以创建抽象类指针
    B b;
    //b.foo();
    b.fa();

    A *pt = new B();
    pt->fa();
    A &pb = b;
    pb.fa();


    Base *ptr = new Derived();

    delete ptr;


    return 0;

}