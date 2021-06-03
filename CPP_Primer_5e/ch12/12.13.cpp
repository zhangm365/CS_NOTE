




#include <iostream>

#include <memory>

using namespace std;




int main()
{

    auto pi = new int();

    shared_ptr<int> sp1(pi);

    // 不可用内置指针初始化多个智能指针
    shared_ptr<int> sp2(pi);


    auto sp = make_shared<int>();

    auto p = sp.get();


    // delete p;
    /*
        double free or corruption (out)
        已放弃 (核心已转储)

    */

    return 0;

}


