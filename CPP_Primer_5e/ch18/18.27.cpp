

#include <iostream>
#include <vector>
#include <string>


using namespace std;


struct Base1
{
    void print(int) const
    {
        cout << "Base1::print(int)" << "\n";
    }

protected:
    int ival;
    double dval;
    char cval;

private:
    int *id;    

};


struct Base2
{
    void print(double) const
    {
        cout << "Base2::print(double)" << "\n";
    }

protected:
    double fval;

private:
    double dval;

};

struct Derived : public Base1
{
    void print(std::string) const
    {
        cout << "Derived::print(string)" << "\n";
    }

protected:
    std::string str;
    double dval;

};


struct MI : public Derived, public Base2
{
    void print(std::vector<double>)
    {
        cout << "MI::print(vector<double>)" << "\n";
    }

    void foo(double cval)
    {
        int dval;
        
    }


protected:
    int *ival;
    std::vector<double> vec;

};


int main()
{
    MI mi;
    // mi.print(42);   // error: cannot convert ‘int’ to ‘std::vector<double>’



    return 0;

}