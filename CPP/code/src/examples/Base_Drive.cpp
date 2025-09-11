


#include<bits/stdc++.h>
using namespace std;


class People
{
    public:
        People(string _name, int _age):name(_name),age(_age){
            cout << "People: constructor" << endl;
        }
        
        virtual void display() const {

            cout << "People:display()" << endl;
        }
        
        virtual ~People(){

            cout << "People: destructor" << endl;
        }
    private:
        string name;
        int age;
};


class Student : public People
{


    public:

        Student( string m_name, int m_age, double m_score):People(m_name, m_age), score(m_score){

            cout << "Student: constructor" << endl;

        }
        void display() const
        {
            
            cout << "score:" << score << endl; 
        }

        ~Student(){
            cout << "Student:destructor" << endl;
        }
    private:
        double score;
};


int main()
{

    People * p = new Student("zhang", 18, 99.90);

    // Student stu("zhang", 18, 99.90);
    // People &p = stu;

    p->display();
    delete p;

    return 0;


}