#define _GNU_SOURCE 1
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/epoll.h>

#define BUFFER_SIZE 1024
int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}

// add entries to interest list for epoll instance refered to by epfd
void addfd(int epfd, int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLRDHUP;

    if( -1 == epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) )
    {
        perror("addfd epoll_ctl");
        return;
    }
    setnonblocking(fd);

}


int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );

    int sockfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( sockfd >= 0 );

    struct sockaddr_in server_address;
    bzero( &server_address, sizeof( server_address ) );
    server_address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &server_address.sin_addr );
    server_address.sin_port = htons( port );

    
    if ( connect( sockfd, ( struct sockaddr* )&server_address, sizeof( server_address ) ) < 0 )
    {
        printf( "connection failed\n" );
        close( sockfd );
        return 1;
    }

    int epfd = epoll_create1(0);
    assert( epfd != -1 );

    struct epoll_event ev_arr[2];
    addfd(epfd, STDIN_FILENO);
    
    addfd(epfd, sockfd);

    char read_buf[BUFFER_SIZE];
    int pipefd[2];
    int ret = pipe( pipefd );
    assert( ret != -1 );


    int nfds;

    for(;;)
    {
        nfds = epoll_wait(epfd, ev_arr, 2, -1);
        if( nfds == -1 ) 
        {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }
        
        sleep(1);
        //printf("nfds = %d\n", nfds);
        
        for( int i = 0 ; i < nfds; ++i )
        {   
            

            if( ev_arr[i].events & EPOLLRDHUP )
            {
                printf( "server close the connection\n" );
                return -1;
            }
            else if( (ev_arr[i].events & EPOLLIN) )   // read
            {
                //printf("111\n");
                memset( read_buf, '\0', BUFFER_SIZE );
                recv( ev_arr[i].data.fd, read_buf, BUFFER_SIZE-1, 0 );
                printf( "%s\n", read_buf );
            }

            if(  ev_arr[i].events & EPOLLIN )
            {
                //printf("222\n");
                ret = splice( 0, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE );
                ret = splice( pipefd[0], NULL, sockfd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE );
            }
        }
    }
    
    close( sockfd );
    return 0;
}
