

#include <iostream>

#include <string>

#include <vector>


using namespace std;


int main()
{

    vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    //vector<int> vec(10);

    for( auto ite = vec.begin(); ite != vec.end(); ++ite )
        *ite *= 2;

    for( auto val : vec )
        cout << val << " ";
    
    cout << endl;

    return 0;

}