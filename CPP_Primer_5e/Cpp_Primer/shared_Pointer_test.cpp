


#include <iostream>

#include <memory>



using namespace std;


int main()
{

    int a = 6;
    std::shared_ptr<int> ptra = std::make_shared<int>(a);

    std::shared_ptr<int> pa1;    // 空的智能指针
    if( !pa1 )
    {
        cout << "the shared_pointer is empty!" << endl;
    }
    // std::shared_ptr<int> pa2 = ptra;

    cout << "The shared_pointer ptra's num is: " << ptra.use_count() << endl;   // 1

    //cout << "The shared_pointer p1's num is: " << pa1.use_count() << endl;


    int b = 100;
    int *pb = &b;

    // std::shared_ptr<int> ptrb = pb; // error

    std::shared_ptr<int> ptrb = std::make_shared<int>(b);

    auto ptrb2(ptrb);
    
    ptra = ptrb;    // increase the ptrb count, decrease the ptra count

    pb = ptrb.get();

    cout << "The shared_pointer ptra's num is: " << ptra.use_count() << endl; // 3
    cout << "The shared_pointer ptrb's num is: " << ptrb.use_count() << endl;   // 3

    std::weak_ptr<int> wp(ptra);    // 弱引用: 仅观测绑定的引用数，不增加计数
    
    if( !wp.expired() )
    {
        std::shared_ptr<int> ptra2 = wp.lock();
        *ptra = 100;
        cout << "the num is " << ptra.use_count() << endl;
        
    }
    
    cout << "weak pointer is " << wp.use_count() << endl; // 3
    return 0;

}