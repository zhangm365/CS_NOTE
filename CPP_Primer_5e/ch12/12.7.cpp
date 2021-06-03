

#include <iostream>

#include <vector>

#include <memory>


using namespace std;



shared_ptr<vector<int>> Func()
{

    
    return make_shared<vector<int>>();

}


void getVal( shared_ptr<vector<int>> vec )
{

    
    for ( int i = 0 ; cin >> i; )
    {
        vec->push_back(i);
    }


}



ostream& print( ostream &out, shared_ptr<vector<int>> vec )
{

    for ( const auto &val : *vec )
        out << val << " ";

    return out;
}


int main()
{

    shared_ptr<vector<int>> p = Func();
    getVal( p );

    print(cout, p) << endl;



    return 0;

}
