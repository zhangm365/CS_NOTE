

#ifndef _PERSON_H_
#define _PERSON_H_

#include <iostream>
#include <string>

class Person;

std::istream &read( std::istream &, Person &);
std::ostream &print( std::ostream &, const Person & );


class Person
{

    friend std::istream &read( std::istream &, Person & );
    friend std::ostream &print( std::ostream &, const Person & );

    public:

        Person() = default;
        Person( const std::string &n, const std::string &ad ) : name(n), address(ad) {}
        Person( std::istream &is ) { return read( is, *this); }


        std::string getName () const { return name; }
        std::string getAddress () const { return address; }

    private:
        std::string name;
        std::string address;

};


std::istream &read( std::istream &is, Person &item )
{
    is >> item.name >> item.address;
    return is;
}

std::ostream &print( std::ostream &os, const Person &item )
{
    os << item.name << " " << item.address;
    return os;
    
}

#endif

