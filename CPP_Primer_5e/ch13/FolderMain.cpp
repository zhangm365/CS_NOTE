

#include "Folder.h"
#include <vector>


using namespace std;

int main()
{

    string s1("content1");
    string s2("content2");
    string s3("content3");

    string s4("content4");
    string s5("content5");
    string s6("content6");

    // all new messages, no copies yet
	Message m1(s1);
	Message m2(s2);
	Message m3(s3);
	Message m4(s4);
	Message m5(s5);
	Message m6(s6);

    Folder f1;
	Folder f2;

	m1.save(f1); m3.save(f1); m5.save(f1);
	m1.save(f2);
	m2.save(f2); m4.save(f2); m6.save(f2);
	
	m1.debug_print();
	f2.debug_print();
    
    return 0;

}