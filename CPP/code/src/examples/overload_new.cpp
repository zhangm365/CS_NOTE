
/*
    重载 operator new/delete 操作符
*/
#include <bits/stdc++.h>

using namespace std;


class Foo
{
    public:
        Foo() { cout << "default ctor.this = " << this << " id = " << id << endl; }
        Foo( int i ):id(i) { cout << "default ctor.this = " << this << " id = " << id << endl; }
        virtual ~Foo() { cout << "dtor.this = " << this << " id = " << id << endl; }

        static void* operator new(size_t size);
        static void operator delete(void* pd, size_t size);
        static void* operator new[](size_t size);
        static void operator delete[](void* pd, size_t size);

    private:
        int id;

};

void* Foo::operator new(size_t size)
{
    Foo *p = (Foo*)malloc(size);
    cout << "operator new," << " size = " << size << endl;
    return p;

}


void Foo::operator delete(void* pd, size_t size)
{
    cout << "operator delete" << endl;
    free(pd);
}

void* Foo::operator new[](size_t size)
{
    Foo *p = (Foo*)malloc(size);
    cout << "operator new[]," << " size = " << size << endl;
    return p;
}


void Foo::operator delete[](void* pd, size_t size)
{
    cout << "operator delete[]" << endl;
    free(pd);
}


int main()
{


    Foo *fo = new Foo(6);
    cout << "---------------\n";
    delete fo;
    
    cout << "+++++++++++++array new overload+++++++++++++" << endl;
    Foo *fa = new Foo[3];

    cout << "---------------\n";

    delete [] fa;

    cout << sizeof(Foo) << endl;
    return 0;

}