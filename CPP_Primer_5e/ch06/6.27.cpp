


#include <iostream>

#include <initializer_list> // 标准库类型, 函数实参类型相同, 但是实参数量未知

using namespace std;



int variable_sum( initializer_list<int> li )
{

    int sum = 0 ;
    // for( auto beg = li.begin(); beg != li.end(); ++beg )
    // {   
        
    //     sum += *beg;

    // }

    for( auto &val : li )
        sum += val;

    return sum;   

}


int main()
{

    initializer_list<int> l1;
    initializer_list<int> l2 = l1;
    initializer_list<int> l3(l1);
    cout << l1.size() << " " << l2.size() << " " << l3.size() << endl;

    
    int ret = variable_sum( { 2, 4, 5, 7, 8 } );
    cout << "initializer_list: ";
    cout << ret << endl;
    return 0;

}