
#include <bits/stdc++.h>

using namespace std;

class Widget{

public:
    Widget( const char *str )
    {
        if( !str )
        {
            
            text = new char[1];
            text[0] = '\0';
        }
        else
        {
            
            int len = strlen(str);
            
            text = new char[len + 1];
            strcpy(text, str);
            text[len] = '\0';
            
            
        }
    }

    Widget( const Widget &rhs )
    {

        int len = strlen(rhs.text);
        text = new char[len+1];
        strcpy(text, rhs.text);
        text[len] = '\0';

    }

    void swap( Widget &rhs )
    {
        char *tmp = rhs.text;
        rhs.text = this->text;
        this->text = tmp;
    }

    
    Widget& operator=( const Widget &rhs )
    {
        
        Widget wt(rhs);
        swap(wt);

        return *this;
    }

    ~Widget()
    {
        delete text;
    }

    void getText() const{

        cout << text << "\n";
    }

private:
    char *text;

};


int main()
{


    Widget w1("hello");
    Widget w2("world");

    w1 = w2;

    w1.getText();

    w2.getText();

    return 0;

}