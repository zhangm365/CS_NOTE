

# include <iostream>

using namespace std;



int fact( int n )
{

    if( n < 0 )
    {
        throw runtime_error ("Input val can't a negative number");    
    }

    int ret = 1;
    while( n > 1 )
    {
        ret *= n;
        n--;
    }
        
    return ret;


}


int main()
{


    int val;

    while( cin >> val )
    {
        int ret = 0;
        try
        {
            ret = fact(val);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return -1;
        }
        
        
        printf("%d! = %d\n", val, ret);
    }


    return 0;

}