


#include <iostream>

#include <vector>


using namespace std;



vector<int>* Func()
{

    return new vector<int>{};

}


void getVal( vector<int> *vec )
{

    
    for ( int i = 0 ; cin >> i; )
    {
        vec->push_back(i);
    }


}



ostream& print( ostream &out, vector<int> *vec )
{

    for ( const auto &val : *vec )
        out << val << " ";

    return out;
}

int main()
{

    vector<int> *p = Func();
    getVal( p );

    print(cout, p) << endl;

    delete p;
    
    p = nullptr;

    return 0;

}
