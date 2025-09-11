

#include <bits/stdc++.h>

class Base
{
    public:
        Base(){};

        virtual void ChangeAttributes() = 0 ;

        // The "virtual constructor"
        static Base* Create(int id);

        // The "virtual copy constructor"
        virtual Base* Clone() = 0;

       // Ensures to invoke actual object destructor 
       virtual ~Base()
       {

           std::cout << "Base : destructor" << std::endl;

       };


};


class Derived1 : public Base
{

    public:
        Derived1(){

            std::cout << "Derived1 default constructor" << std::endl;
        };

        Derived1(const Derived1 &rhs)
        {

            std::cout << "Derived1 constructed by deep copy" << std::endl;

        };

        virtual void ChangeAttributes()
        {
            std::cout << "Derived1: Attribute" << std::endl;

        }

        // 
        Base* Clone()
        {

            return new Derived1(*this);

        }

        ~Derived1()
        {
            std::cout << "Derived1 : destructor" << std::endl;
        }

};


class Derived2 : public Base
{

    public:
        Derived2(){

            std::cout << "Derived2 default constructor" << std::endl;
        };


        Derived2(const Derived2 &rhs)
        {

            std::cout << "Derived2 constructed by deep copy" << std::endl;

        };

        virtual void ChangeAttributes()
        {
            std::cout << "Derived2: Attribute" << std::endl;

        }

        // 
        Base* Clone()
        {

            return new Derived2(*this);

        }

        ~Derived2()
        {
            std::cout << "Derived2 : destructor" << std::endl;
        }


};

class Derived3 : public Base
{

    public:
        Derived3(){

            std::cout << "Derived3 default constructor" << std::endl;
        };

        Derived3(const Derived3 &rhs)
        {

            std::cout << "Derived3 constructed by deep copy" << std::endl;

        };

        virtual void ChangeAttributes()
        {
            std::cout << "Derived3: Attribute" << std::endl;

        }

        // 
        Base* Clone()
        {

            return new Derived3(*this);

        }

        ~Derived3()
        {
            std::cout << "Derived3 : destructor" << std::endl;
        }


};


Base* Base::Create(int id)
{

    if( 1 == id)
        return new Derived1();
    else if( 2 == id )
        return new Derived2();
    else
        return new Derived3();

}


class User
{

    public:
        User() : pBase(nullptr) {

            int input;

            std::cout << "Enter ID(1, 2, or 3):" << std::endl;
            std::cin >> input;

            while( input != 1 && input != 2 && input != 3 )
            {
                std::cout << "Enter ID(1, 2, or 3 only)" << std::endl;
                std::cin >> input; 
            }

            // create object by the "Virtual Constructor"
            pBase = Base::Create(input);

        }

        

        void Action()
        {
            // 复制当前对象
            Base *pB = pBase->Clone();
            pB->ChangeAttributes();
            delete pB;

        }

        
        ~User()
        {
            delete pBase;
            pBase = nullptr;
        }

    private:
        Base *pBase;

};

 
int main()
{

    User *pU = new User();
    pU->Action();

    delete pU;

    return 0;

}