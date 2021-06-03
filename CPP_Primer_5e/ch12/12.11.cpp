

#include <iostream>

#include <memory>

using namespace std;


void process(shared_ptr<int> sp)
{
    cout << "inside the process function : " << sp.use_count() << endl;
}

int main()
{


    shared_ptr<int> p(new int(42));

    /*
        inside the process function : 1
        free(): double free detected in tcache 2
        已放弃 (核心已转储)
  
    */
    process(shared_ptr<int>(p.get()));


    return 0;

}
