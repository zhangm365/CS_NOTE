

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/types.h>          
#include <sys/socket.h>

#define MAX_LEN 1024

void error_handling( char *message );

int main( int argc, char *argv[] )
{

    int serv_sock;
    struct sockaddr_in serv_addr;   // socket 专用地址
    
    if ( argc != 2 )
    {
        printf( "Usage : %s <port>\n", argv[0] );
        exit(EXIT_FAILURE);
    }

    // 1. socket
    serv_sock = socket( PF_INET, SOCK_STREAM, 0 );
    if ( serv_sock == -1 )
    {
        error_handling("socket() error");
    }
    

    // 2. bind

    memset( &serv_addr, 0, sizeof(serv_addr) );

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons( atoi(argv[1]) );
    
    int ret = bind( serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr) );
    
    if( -1 == ret )
    {
        error_handling("bind() error");
    }

    // 3. listen

    ret = listen( serv_sock, 5 );

    if( ret == -1 )
    {
        error_handling("listen() error");
    }

    // 4. accept

    int clnt_sock;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);

    clnt_sock = accept( serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size );

    if( clnt_sock == -1 )
    {
        error_handling("accept() error");
    }

    printf( "the client %d is coming\n", clnt_sock );

    char send_msg[] = "hello client, I am server";

    ret = write( clnt_sock, send_msg, sizeof(send_msg) );
    if( ret == -1 )
    {
        error_handling("write() error");

    }

    printf("the server has send %d bytes successfully\n", ret);

    char recv_msg[MAX_LEN];

    ret = read( clnt_sock, recv_msg, sizeof(recv_msg) );
    
    if( ret == -1 )
    {
        error_handling("read() error");

    }


    recv_msg[ret] = '\0';

    printf( "Message from client : %s\n", recv_msg );

    close(clnt_sock);
    close(serv_sock);

    return 0;

}


void error_handling( char *message )
{

    fputs( message, stderr );
    fputc( '\n', stderr );

    exit(EXIT_FAILURE);

}