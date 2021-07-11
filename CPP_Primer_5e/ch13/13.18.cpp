

#include <iostream>

#include <string>

using namespace std;

class Employee
{

    public:
        Employee() : _id(auto_increment++) {};
        Employee( const string &name )
        {
            _id = auto_increment++;
            _name = name;
        }

        int id() const { return _id; }
        string name() const { return _name; }

    private:
        string _name;
        int _id;
        static int auto_increment;


};

int Employee::auto_increment = 0;



int main()
{

    Employee a, b;
    Employee c("hello");

    cout << a.id() << " " << b.id() << endl;
    
    cout << c.id() << " " << c.name() << endl;
    
    return 0;

}