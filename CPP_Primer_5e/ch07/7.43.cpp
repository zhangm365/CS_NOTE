



#include <iostream>
#include <vector>

using namespace std;


class NoDefault
{

    public:
        // NoDefault(){};
        NoDefault( int val ) {}
    
};



class C
{
    public:
        C() : nd(0) {}

    
    private:
        NoDefault nd;

};



int main()
{

    C c;

    vector<C> vec(10);
    vector<NoDefault> v2(10);
    return 0;

}