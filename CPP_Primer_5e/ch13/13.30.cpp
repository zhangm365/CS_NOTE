
#include <iostream>
#include <string>


using namespace std;

class HasPtr
{

    public:

        HasPtr( const string &s = string() ) : ps(new string(s)), i(0) {}

        // 拷贝构造函数 
        HasPtr( const HasPtr &rhs ) : ps(new string(*rhs.ps)), i( rhs.i) {}
        
        // 拷贝并交换
        HasPtr &operator=( HasPtr ths )
        {
            
            swap(*this, ths);
            return *this;
        
        }

        void print()
        {
            cout << *ps << endl;
        }

        ~HasPtr()
        {
            delete ps;
        }


    private:
        string *ps;
        int i;

        friend void swap( HasPtr &, HasPtr & );
};

inline void swap( HasPtr &lhs, HasPtr &rhs )
{

    cout << "swap(HasPtr &, HasPtr &)\n";
    swap( lhs.ps, rhs.ps ); // 交换指针
    swap( lhs.i, rhs.i );

}

int main()
{

    HasPtr h1;
    HasPtr h2(h1);
    HasPtr h3("zhang");

    h3 = h3;

    h3.print();
    return 0;

}
