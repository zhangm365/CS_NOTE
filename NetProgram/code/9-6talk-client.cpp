
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/types.h>          
#include <sys/socket.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/epoll.h>

#define BUFFER_SIZE 1024

int setnoblocking( int fd )
{

    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;

    fcntl( fd, F_SETFL, new_option );
    return old_option;

}

void addfd( int epollfd, int fd )
{

    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLRDHUP;

    if (epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &ev ) < 0)
    {

        perror("epoll_ctl");
        return;

    }

    // setnoblocking(fd);

}


int main( int argc, char *argv[] )
{

    int socket_fd;

    if( argc < 3 )
    {
        printf( "Usage: <%s | ip | port>\n", argv[0] );
        exit( EXIT_FAILURE );
    }


    socket_fd = socket( PF_INET, SOCK_STREAM, 0 );

    if( socket_fd < 0 )
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;

    memset( &server_addr, 0, sizeof(server_addr) );

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr( argv[1] );
    server_addr.sin_port = htons( atoi(argv[2]) );
    
    socklen_t len = sizeof(server_addr);

    if( connect( socket_fd, (struct sockaddr*)&server_addr, len ) < 0 )
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }


    // epoll

    int epoll_fd = epoll_create1(0);

    if( epoll_fd < 0 ) 
    {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }
    
    struct epoll_event ev_arr[2];
    
    // 注册标准输入上的可读事件
    addfd( epoll_fd, 0 );

    
    addfd( epoll_fd, socket_fd );

    // 创建管道
    int pipefd[2];
    int ret = pipe( pipefd );
    assert(ret != -1);

    char read_buf[BUFFER_SIZE];

    while(1)
    {

        int nums = epoll_wait( epoll_fd, ev_arr, 2, -1 );

        if( nums < 0 )
        {
            perror("epoll_wait");
            break;
        }
        
        for( int i = 0; i < nums; ++i )
        {

            
            if( ev_arr[i].data.fd == socket_fd && (ev_arr[i].events & EPOLLRDHUP) )
            {
                printf("server close the connection\n");
                exit( EXIT_FAILURE );
            }
            else if( ev_arr[i].data.fd == socket_fd && (ev_arr[i].events & EPOLLIN) )
            {
                int fd = ev_arr[i].data.fd;
                memset( &read_buf, 0, sizeof(read_buf) );
                recv( fd, read_buf, BUFFER_SIZE-1, 0 );
                printf("%s", read_buf);
            }
            
            
            // 使用 splice 直接将用户输入的数据写到 socket 上 (零拷贝)
            
            if( ev_arr[i].data.fd == 0 && (ev_arr[i].events & EPOLLIN) )
            {
                
                ret = splice( 0, NULL, pipefd[1], NULL, 32768, 
                            SPLICE_F_MORE | SPLICE_F_MOVE );
                ret = splice( pipefd[0], NULL, socket_fd, NULL, 32768,
                            SPLICE_F_MORE | SPLICE_F_MOVE );
            }
        }

    }

    close(socket_fd);

    return 0;

}