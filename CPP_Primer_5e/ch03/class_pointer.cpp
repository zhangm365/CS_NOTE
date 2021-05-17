


#include <iostream>


using namespace std;


class Test
{

    public:
        virtual void f1()
        {
            printf("virtual func\n");
        }

        void f2()
        {
            printf("func\n");
        }


};

int main()
{


    //Test *pc;
    
    // pc->f1();   // segment fault
    
    Test ca;
    ca.f1();    // true



    return 0;

}


