


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
#include <errno.h>

#include <iostream>
#include <vector>

#define BUFFER_SIZE 256
#define USER_LIMIT 5
#define FD_LIMIT 65535

typedef struct client_data
{
    struct sockaddr_in addr;
    char read_buf[BUFFER_SIZE];
    char *write_buf;

}client_data;



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

    setnoblocking(fd);

}


int main( int argc, char *argv[] )
{

    int socket_fd;

    if( argc < 1 )
    {
        printf( "Usage: <%s | port>\n", argv[0] );
        exit(EXIT_FAILURE);
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
    server_addr.sin_addr.s_addr = htonl( INADDR_ANY );
    server_addr.sin_port = htons( atoi(argv[1]) );
    
    socklen_t addr_len = sizeof(server_addr);

    if( bind( socket_fd, (struct sockaddr*)&server_addr, addr_len ) < 0 )
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if ( listen(socket_fd, 10) < 0 )
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
 
    // epoll

    int epoll_fd = epoll_create1(0);

    if( epoll_fd < 0 ) 
    {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }
    
    struct epoll_event ev_arr[USER_LIMIT+1];
    memset( ev_arr, 0, sizeof(ev_arr) );

    client_data *user = new client_data[FD_LIMIT];

    // 注册 socket上的可读事件

    addfd( epoll_fd, socket_fd );

    
    int user_counter = 0;   // 用户数
    
    std::vector<int> vec_conn(USER_LIMIT+1, -1);
    

    while(1)
    {

        int nums = epoll_wait( epoll_fd, ev_arr, USER_LIMIT+1, -1 );

        if( nums < 0 )
        {
            perror("epoll_wait");
            break;
        }

        for( int i = 0; i < nums; ++i )
        {

  
            if( ev_arr[i].data.fd == socket_fd )    // 新连接
            {
                struct sockaddr_in clnt_addr;
                socklen_t addr_len = sizeof( clnt_addr );
                
                int conn_fd = accept( socket_fd, (struct sockaddr*)&clnt_addr, &addr_len );
                if( conn_fd < 0 )
                {
                    perror("accept");
                    continue;
                }

                if( user_counter >= USER_LIMIT )
                {
                    const char *info = "Too many users";
                    printf("%s\n", info);
                    send(conn_fd, info, strlen(info), 0);
                    close(conn_fd);
                    continue;
                }

                user[conn_fd].addr = clnt_addr;

                addfd( epoll_fd, conn_fd );
                
                vec_conn[user_counter++] = conn_fd;

                printf("a new user is coming, now have %d users\n", user_counter);

            }
            else if( ev_arr[i].events & EPOLLRDHUP ) // 客户端关闭连接
            {
                
                int fd = ev_arr[i].data.fd;
                
                user[fd] = user[vec_conn[user_counter-1]];
                
                epoll_ctl( epoll_fd, EPOLL_CTL_DEL, fd, 0 );
                user_counter--;
                
                close(fd);
                printf("a client left\n");

            }
            else if( ev_arr[i].events & EPOLLIN )    // 客户端发来数据
            {
                int fd = ev_arr[i].data.fd;
                memset( user[fd].read_buf, 0, BUFFER_SIZE );
                int ret = recv( fd, user[fd].read_buf, BUFFER_SIZE-1, 0 );
                if( ret < 0 )
                {
                    if( errno != EAGAIN )
                    {
                        
                        user[fd] = user[vec_conn[user_counter-1]];
                        epoll_ctl( epoll_fd, EPOLL_CTL_DEL, fd, 0 );

                        close(fd);
                        
                        user_counter--;

                    }
                }
                else if(ret == 0)
                {
                    printf("Don't come here\n");
                }
                else
                {
                
                    printf( "get %d bytes from client %d, the data is %s", ret, fd, user[fd].read_buf );
                    
                    
                    // 通知其他已连接的 socket 准备写数据
                    for( int j = 0; j < user_counter; ++j )
                    {
                        
                        
                        if( vec_conn[j] == fd )
                        {
                            continue;
                        }

                        send( vec_conn[j], user[fd].read_buf, sizeof(user[fd].read_buf), 0 );

                    }
                
                }

            }
            // else if( ev_arr[i].events & EPOLLOUT )
            // {

                
            //     int fd = ev_arr[i].data.fd;
            //     if( !user[fd].write_buf )
            //     {
            //         continue;
            //     }

            //     int ret = send( fd, user[fd].write_buf, strlen(user[fd].write_buf), 0 );

            //     user[fd].write_buf = NULL;

            //     ev_arr[i].events |= ~EPOLLOUT;
            //     ev_arr[i].events |= EPOLLIN;

            // }

            

        }

    }

    close(socket_fd);
    
    delete [] user;

    return 0;

}