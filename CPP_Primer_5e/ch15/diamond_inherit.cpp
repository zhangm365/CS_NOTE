


#include <iostream>

using namespace std;


struct Base
{
    int val;
};


struct D1 : public Base
{
    int d1;
};


struct D2 : public Base
{
    int d2;
};


struct D : public D1, public D2
{
    int d;
};



int main()
{

    D1 dobj1;
    D dobj;
    dobj.D1::val = 2;   // 必须指定 a 的属于那个类
    dobj.d1 = 3;
    cout << dobj.d1 << " " << dobj1.d1 << "\n";


    return 0;

}