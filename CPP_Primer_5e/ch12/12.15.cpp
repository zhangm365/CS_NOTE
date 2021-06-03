


#include <iostream>

#include <string>

#include <memory>


using namespace std;

struct connection
{

    string ip;
    int port;

    connection( string ip_, int port_ ) : ip(ip_), port(port_) {}

};


struct destination
{

    string ip;
    int port;
    destination( string ip_, int port_ ) : ip(ip_), port(port_) {}

};



connection connect( destination *pd )
{

    shared_ptr<connection> pConn( new connection(pd->ip, pd->port) );
    cout << "creating connect (" << pConn.use_count() << ")" << endl;
    return *pConn;

}


void disconnect( connection conn )
{
    cout << "disconnect the connect (" << conn.ip << " " << conn.port << ")" << endl;
}


void f(destination &pd)
{
    connection conn = connect(&pd);
    shared_ptr<connection> pF( &conn, [](connection *p){ disconnect(*p); }); 
    cout << "connecting now (" << pF.use_count() << ")" << endl;

}


int main()
{

    destination dst("192.168.91.3", 9999);

    f(dst);

    return 0;

}