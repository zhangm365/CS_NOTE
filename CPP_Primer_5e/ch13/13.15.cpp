
#include <iostream>

using namespace std;


class numbered 
{
    public:
        numbered() {
            cout << "default ctor\n";
            mysn = unique++;
        }

        numbered( const numbered &rhs )
        {
            cout << "copy ctor\n";
            mysn = unique++;
        }

        ~numbered() = default;
    
    int mysn;
    static int unique;
};

int numbered::unique = 10;

void f(numbered s) {
    std::cout << s.mysn << std::endl;
}

void rf(const numbered &s ) {
    std::cout << s.mysn << std::endl;
}


int main()
{
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);

    return 0;
}