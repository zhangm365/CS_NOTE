

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>


#define MAX_LEN 1024

void error_handling( char *message )
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(EXIT_FAILURE);

}

int main( int argc, char *argv[] )
{


    int socket_fd;

    if( argc != 3 )
    {
        printf( "Usage : %s <ip | port>\n", argv[0] );
        exit(EXIT_FAILURE);
    }
    // 1. socket
    socket_fd = socket( PF_INET, SOCK_STREAM, 0 );

    if( -1 == socket_fd )
    {
        error_handling("socket() error");
    }

    // 2. connect

    struct sockaddr_in clnt_addr;
    memset( &clnt_addr, 0, sizeof(clnt_addr) );

    clnt_addr.sin_family  = AF_INET;
    clnt_addr.sin_addr.s_addr = inet_addr(argv[1]);
    clnt_addr.sin_port = htons( atoi(argv[2]) );


    // socklen_t clnt_addr_size;

    int conn_fd = connect( socket_fd, (struct sockaddr *)&clnt_addr, sizeof(clnt_addr) );
    
    if( conn_fd == -1 ) // 成功返回 0, 失败返回 -1
    {
        error_handling("connect() error");
    }
    
    printf( "the client has connected the server %d successfully\n", socket_fd );

    char recv_msg[MAX_LEN];
    
    
    int ret = read( socket_fd, recv_msg, sizeof(recv_msg) );
    
    if( ret == -1 )
    {
        error_handling("read() error");
    }

    recv_msg[ret] = '\0';

    printf( "the client receive the %d bytes from server : %s\n", ret, recv_msg );

    char send_msg[] = "hello server";

    ret = write( socket_fd, send_msg, sizeof(send_msg) );
    if( ret == -1 )
    {
        error_handling("write() error");
    }
    
    printf("the client has send %d bytes\n", ret);
    close( socket_fd );

    return 0;

}