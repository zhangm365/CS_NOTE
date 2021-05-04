

#include <iostream>

#include <string>

#include <vector>

using namespace std;


int main()
{

    
    int val;
    vector<int> vec;

    while( cin >> val )
        vec.push_back(val);

    // 输出每对相邻整数的和
    for( vector<int>::size_type i = 0 ; i < vec.size()-1; ++i )
    {
        cout << vec[i] + vec[i+1] << endl;
    }

    // 依次输出首尾元素之和

    cout << "----------" << endl;
    
    // if the vector has odd size, element in the middle will add to itself.
    auto size = (vec.size() + 1) / 2;


    for( vector<int>::size_type i = 0; i != size; ++i )
    {
        
        cout << vec[i] + vec[vec.size()-i-1] << endl;
 
    }

    

    return 0;

}