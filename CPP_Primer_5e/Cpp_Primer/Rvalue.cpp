


#include <iostream>
#include <utility>


using namespace std;


int main()
{

    int a = 10;

    int& l = a;

    const int& cl = a;

    int &&rr = a * 10;

    int b = 6;
    //int &&rr1 = a; // error 
    int &&rr1 = std::move(a);
    //int &&rr2 = rr; //error 

    int &tmp = rr;
    return 0;
}