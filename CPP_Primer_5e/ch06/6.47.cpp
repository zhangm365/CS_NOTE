


#include <iostream>

#include <vector>

using namespace std;


void printVec( vector<int> &vec )
{

    #ifndef NDEBUG
        cout << "In function : " << __func__ << "arr size is " << vec.size() << endl;
    #endif

    if( !vec.empty() )
    {

        auto tmp = vec.back();
        vec.pop_back();
        printVec(vec);

        cout << tmp << endl;

    }

}



int main()
{


    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    printVec(vec);

    return 0;

}