

#include <iostream>

#include <string>

#include <vector>


using namespace std;


int main()
{
    
    vector<int> nums(11, 0);
    for( int score; cin >> score;  )
    {

        if ( score <= 100 )
            ++*(nums.begin() + (score / 10));

    }
        

    for ( auto val : nums )
        cout << val << " ";
    
    cout << endl;

    return 0;

}