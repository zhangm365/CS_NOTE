

#include <iostream>
#include <vector>

using namespace std;


int main()
{


    vector<int> nums;
    int val;
    while( cin >> val )
        nums.push_back(val);

    for( vector<int>::size_type i = 0 ; i < nums.size(); ++i )
    {
        cout << nums[i] << " " ;
    }

    cout << endl;

    return 0;

}