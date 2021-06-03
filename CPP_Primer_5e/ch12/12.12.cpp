


#include <iostream>

#include <memory>

using namespace std;


void process(shared_ptr<int> sp)
{
    cout << "inside the process function : " << sp.use_count() << endl;
}

int main()
{

    auto p = new int();
    
    
    auto sp = make_shared<int>();

    process(shared_ptr<int>(sp));

    // process(new int()); // error : convert the "int *" to "shared_ptr<int>"
    
    // process(p);

    process(shared_ptr<int>(p));

    return 0;

}


