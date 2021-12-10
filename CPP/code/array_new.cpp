

#include <iostream>

using namespace std;

class A
{
    public:
        
        A() : id(0) { cout << "Dctor " << this << " id = " << id << endl; }
        A(int i) : id(i) { cout << "Ctor " << this << " id = " << id << endl; }
        ~A() { cout << this << " id = " << id << endl; }
    private:
        int id;
    
};



int main()
{

    A *ptr = new A[3];    // 必须要有默认构造函数，否则会报错：no matching function for call to 'A::A()'
    A *tmp = ptr;

    for( int i = 0; i < 3; ++i )
        new(tmp++)A(i);    // call placement new
    
    delete [] ptr;    // array delete, 删除次序与构造次序相反

    return 0;

}