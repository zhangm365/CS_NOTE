


#include <bits/stdc++.h>

using namespace std;


class MyString
{

    public:
        MyString(const char* str = nullptr)
        {
            cout << "------default ctor--------" << endl;
            if(str)
            {
                cout << "str is not nullptr" << endl;
                m_str = new char[1024];
                //char str[] = "hello world!";
                strcpy(m_str, str);
                m_str[strlen(str)] = '\0';
            }
            else
            {
                cout << "str is nullptr" << endl;
                m_str = new char[1];
                m_str[0] = '\0';

            }
            
        }

        MyString( const MyString& Cstr )    // 拷贝构造函数
        {
            cout << "------copy ctor-------" << endl;
            this->m_str = new char[strlen(Cstr.m_str) + 1];
            strcpy(this->m_str, Cstr.m_str);
            this->m_str[strlen(Cstr.m_str)] = '\0';
            
        }

        MyString& operator=( const MyString& ths )
        {

            cout << "-----assign ctor-------" << endl;
            if( this == & ths ) return *this;

            delete [] m_str;

            m_str = new char[strlen(ths.m_str) + 1];
            strcpy(m_str, ths.m_str);

            return *this;

        }


        void display()
        {
            cout << m_str << endl;
        }

        ~MyString()
        {
            delete [] m_str;
        }


    private:
        char* m_str;


};



int main()
{

    MyString str;
    str.display();

    MyString str1("hello world!");
    str1.display();
    
    MyString str2(str1);
    str2.display();

    MyString str3 = "zhang";

    str3 = str1;
    
    str3.display();


    return 0;
}