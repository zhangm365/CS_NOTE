



#include <bits/stdc++.h>

using namespace std;

class A
{

    public:
        A( int x = 0 ) : val(x) {

            cout << "default ctor" << endl;
        }

        A(const A& a) {
            
            cout << "copy ctor" << endl;
            val = a.val;
        }

        A& operator=(const A& rhs)
        {
            
            cout << "assign ctor\n";

            if( this == &rhs ) return *this;
            this->val = rhs.val;

            return *this;

        }


        void print() { std::cout << val << std::endl;}

    private:
        int val;

};

int main()
{

    A a;
    A b(5);
    a = b;
    A c(a);
    
    a.print();
    b.print();
    c.print();

    return 0;
    
}
