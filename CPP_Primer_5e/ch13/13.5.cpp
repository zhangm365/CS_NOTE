

#include <bits/stdc++.h>

using namespace std;


class HasPtr
{

    public:
        HasPtr( const string &s = string() ) : ps( new string(s) ), i(0) { cout << "default ctor\n"; }

        // copy constructor
        HasPtr( const HasPtr &rhs ) : ps( new string(*rhs.ps) ), i(rhs.i) { cout << "copy ctor\n"; }

        HasPtr& operator=( const HasPtr &rhs )
        {
            cout << "assignment ctor\n";
            if( this == &rhs )
            {
                return *this;
            } 

            delete ps;

            ps = new string(*rhs.ps);
            i = rhs.i;

            return *this;

        }

        void print()
        {
            cout << *ps << endl;
        }

        ~HasPtr()
        { 
            cout << "~ ctor\n";
            delete ps;
        }

    private:
        string *ps;
        int i;


};



int main()
{

    HasPtr h1("hello");
    h1.print();
    HasPtr h2;
    
    h2 = h1;
    HasPtr h3 = h2;

    h3 = h1;
    h3.print();
    
    HasPtr *p = new HasPtr("world");

    delete p;
    
    return 0;

}