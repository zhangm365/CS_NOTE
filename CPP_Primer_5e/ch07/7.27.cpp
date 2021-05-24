


#include "Screen.h"

using namespace std;

int main()
{

    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#').display(cout);
    
    /*
        myScreen.move(4, 0);
        myScreen.set('#');
        myScreen.display(cout);
    */

    cout << "\n";

    myScreen.display(cout);
    cout << "\n";

    const Screen cMyScreen(3, 3, '6');
    
    cMyScreen.display(cout);
    cout << "\n"; 

    return 0;


}