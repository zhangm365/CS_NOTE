



// virtual函数的动态绑定


#include <bits/stdc++.h>

// 虚函数是动态绑定，但是默认参数是静态绑定。默认参数的使用需要看指针或引用本身的类型，与实际指向或引用的对象类型无关！
class Employer
{

    public:
        virtual void raiseSalary( int x  = 0 )
        {
            std::cout << "Employer : " << x << std::endl;
        }

};


class Manager : public Employer
{

    public:
        virtual void raiseSalary( int x = 100 )
        {
            std::cout << "Manager : " << x << std::endl;

        }

};

class Employee : public Employer
{

    public:
        virtual void raiseSalary( int x = 200 )
        {

            std::cout << "Employee : " << x << std::endl;

        }

};


void globalRaiseSalary(Employer *emp[], int n)
{

    for( int i = 0; i < n; ++i )
        emp[i]->raiseSalary();  //Polymorphic call : according to the actual object, not  
    // according to the type of pointer or reference


}

int main()
{

    // 虚函数的调用取决于指向或引用的对象类型，而不是指针或引用自身的类型
    Employer *emp[] = {new Employee(), new Manager()};
    globalRaiseSalary(emp, 2);
    

    return 0;

}