




# include <bits/stdc++.h>

#define enum_to_string(x) #x

class Person
{

    public:
        typedef enum
        {
            BOY = 0,
            GIRL
        }SexType;


        Person(char *n, int i, SexType sex)
        {
            name = new char(strlen(n) + 1);
            strcpy(name, n);
            age = i;
            this->sex = sex;

        }

        int get_age() const
        {
            return this->age;

        }

        Person& add_age( int x )    // add_age( Person* const this, int x )
        {
            age += x;
            return *this;
        }


        ~Person()
        {
            delete [] name;
        }


    private:
        char *name;
        int age;
        SexType sex;


};




int main()
{

    char my_name[] = "zhangm";
    Person p1( my_name, 20, Person::BOY );
    printf("age = %d\n", p1.get_age());

    printf("add_age = %d\n", p1.add_age(3).get_age());


    return 0;

}