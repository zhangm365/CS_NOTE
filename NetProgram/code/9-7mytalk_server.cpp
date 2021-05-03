#define _GNU_SOURCE 1
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <poll.h>
#include <sys/epoll.h>

#define USER_LIMIT 5
#define BUFFER_SIZE 1024
#define FD_LIMIT 65535

struct client_data
{
    struct sockaddr_in address;
    char* write_buf;
    char buf[ BUFFER_SIZE ];
};

#define MAX_EVENTS 10


int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}


// add entries to interest list for epoll instance refered to by epfd
void addfd(int epfd, int listenfd)
{
    struct epoll_event ev;
    ev.data.fd = listenfd;
    ev.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
    if( -1 == epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) )
    {
        perror("addfd epoll_ctl");
        return;
    }
    setnonblocking(listenfd);

}


int main( int argc, char* argv[] )
{
    if( argc <= 1 )
    {
        printf( "usage: %s port_number\n", basename( argv[0] ) );
        return 1;
    }
    //const char* ip = argv[1];
    int port = atoi( argv[1] );
    
    // step1 : socket
    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( listenfd >= 0 );


    // step2 : bind the socket
    int ret = 0;
    struct sockaddr_in serAddr;
    bzero( &serAddr, sizeof( serAddr ) );
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //inet_pton( AF_INET, ip, &address.sin_addr ); // convert ip address to network byte 
    serAddr.sin_port = htons( port );

    // 设置复用
    int flag = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    


    ret = bind( listenfd, ( struct sockaddr* )&serAddr, sizeof( serAddr ) );
    assert( ret != -1 );

    // step3: listen the connect
    ret = listen( listenfd, 5 );
    assert( ret != -1 );

    
    client_data* users = new client_data[BUFFER_SIZE];
    

    struct epoll_event epoll_events[MAX_EVENTS];

    int epfd = epoll_create1(0);
    assert( epfd != -1 );

    addfd(epfd, listenfd);

    int nfds;

    for(;;)
    {
        nfds = epoll_wait(epfd, epoll_events, MAX_EVENTS, -1);
        if( nfds == -1 ) 
        {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }
        
        //printf("nfds = %d\n", nfds);

        for( int i = 0; i < nfds; ++i )
        {
            //printf("epoll_events[%d].data.fd = %d, epoll_events[%d].events = %d\n", i, epoll_events[i].data.fd, i, epoll_events[i].events);
            if( ( epoll_events[i].data.fd == listenfd ) && (epoll_events[i].events & EPOLLIN) )
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );
                int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
                if ( connfd < 0 )
                {
                    printf( "errno is: %d\n", errno );
                    continue;
                }
                
        
                users[connfd].address = client_address;
                addfd(epfd, connfd);
                
                printf( "comes a new user, the confd = %d, the ip address is = %s\n", connfd, inet_ntoa(client_address.sin_addr) );
            
            }
            else if( epoll_events[i].events & EPOLLERR )
            {
                
                printf( "get an error from %d\n", epoll_events[i].data.fd );
                char errors[ 100 ];
                memset( errors, '\0', 100 );
                socklen_t length = sizeof( errors );
                if( getsockopt( epoll_events[i].data.fd, SOL_SOCKET, SO_ERROR, &errors, &length ) < 0 )
                {
                    printf( "get socket option failed\n" );
                }
                continue;

            }
            else if( epoll_events[i].events & EPOLLRDHUP )
            {
                struct epoll_event ev;
                ev.data.fd = epoll_events[i].data.fd;
                ev.events = EPOLLRDHUP;
                if( -1 == epoll_ctl(epfd, EPOLL_CTL_DEL, epoll_events[i].data.fd, &ev) )
                {
                    perror("epoll_ctl");
                    continue;
                }
                close( epoll_events[i].data.fd );
                
                printf( "a client %d left\n",  epoll_events[i].data.fd);

            }
            else if( epoll_events[i].events & EPOLLIN )
            {
                int connfd = epoll_events[i].data.fd;
                
                memset( users[connfd].buf, '\0', BUFFER_SIZE );
                ret = recv( connfd, users[connfd].buf, BUFFER_SIZE-1, 0 );
                printf( "get %d bytes of client data %s from %d\n", ret, users[connfd].buf, connfd );
                if( ret < 0 )
                {
                    if( errno == EAGAIN || ( errno == EWOULDBLOCK ) ) continue;

                    struct epoll_event ev;
                    ev.data.fd = epoll_events[i].data.fd;
                    ev.events = EPOLLRDHUP;
                    if( -1 == epoll_ctl(epfd, EPOLL_CTL_DEL, epoll_events[i].data.fd, &ev) )
                    {
                        perror("epoll_ctl");
                        continue;
                    }

                    close( connfd );
                }
                else if( ret == 0 ) //检测连接关闭, recv读回来0个数据
                {
                    struct epoll_event ev;
                    ev.data.fd = epoll_events[i].data.fd;
                    ev.events = EPOLLRDHUP;
                    if( -1 == epoll_ctl(epfd, EPOLL_CTL_DEL, epoll_events[i].data.fd, &ev) )
                    {
                        perror("epoll_ctl");
                        continue;
                    }
                    close( epoll_events[i].data.fd );
                    
                    printf( "a client %d left\n",  epoll_events[i].data.fd);
                }
                else
                {
                    
                    for( int j = 0; j < nfds; ++j )
                    {
                        if( epoll_events[j].data.fd == connfd )
                        {    
                            continue;
                        }
                        
                        //epoll_events[j].events |= ~EPOLLIN;   // 不让其他用户接受到消息
                        epoll_events[j].events |= EPOLLOUT;
                        users[connfd].write_buf = users[connfd].buf;
                    }
                }
            }
            else if( epoll_events[i].events & EPOLLOUT )
            {
                int connfd = epoll_events[i].data.fd;
                if( ! users[connfd].write_buf )
                {
                    continue;
                }
                ret = send( connfd, users[connfd].write_buf, strlen( users[connfd].write_buf ), 0 );
                users[connfd].write_buf = NULL;
                epoll_events[i].events |= ~EPOLLOUT;
                epoll_events[i].events |= EPOLLIN;
            }
        }

    }
    
    
    delete [] users;
    close( listenfd );
    return 0;
}
