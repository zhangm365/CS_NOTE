

 #include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <string.h>

#define BUF_SIZE 1024

int main( int argc, const char * argv[] )
{

    while( argc < 3 )
    {
        perror("usage format :  ip | port\n");
        continue;
        
    }

    int ret;

    int port = atoi(argv[2]);


    // step 1 : socket
    int sock_fd = socket( PF_INET, SOCK_STREAM, 0 );
    assert(sock_fd > 0);

    struct sockaddr_in sockaddress;
    bzero(&sockaddress, sizeof(sockaddress));

    sockaddress.sin_family = AF_INET;
    sockaddress.sin_port = htons(port);

    ret = inet_pton(AF_INET, argv[1], &sockaddress.sin_addr);
    assert(ret > 0);

    // step 2 : bind 
    ret = bind( sock_fd, (struct sockaddr *)&sockaddress, sizeof(sockaddress) );

    assert( ret != -1 );


    // step 3 : listen
    ret = listen(sock_fd, 5);
    assert( ret != -1 );


    struct sockaddr_in clientaddr;
    socklen_t addrlen = sizeof(clientaddr);
    int confd = accept(sock_fd, (struct sockaddr*)&clientaddr, &addrlen);

    if( confd < 0 )
    {
        perror("accept errno!\n");
        close(confd);
        exit(EXIT_FAILURE);
    }


    fd_set rfds;
    fd_set efds;    // 异常事件

    FD_ZERO(&rfds);
    FD_ZERO(&efds);

    char buf[BUF_SIZE];

    while(1)
    {

        memset(buf, 0, sizeof(buf));

        FD_ZERO(&rfds);

        FD_SET(confd, &rfds);

        FD_ZERO(&efds);
        
        FD_SET(confd, &efds);

        int nfds = select( confd + 1, &rfds, &efds, NULL, 0);

        if( nfds < 0 ) 
        {
            perror("select error\n");
            break;
        }

        if( FD_ISSET(confd, &rfds) )
        {
            ret = recv(confd, buf, sizeof(buf), 0);
            if( ret <= 0 )
            {
                break;
            }

            printf("recv from client %d bytes normal data : %s\n", ret, buf);

        }
        else if( FD_ISSET(confd, &efds) )   // 带外数据属于异常事件
        {
            ret = recv(confd, buf, sizeof(buf), MSG_OOB);
            if( ret <= 0 )
                break;
            printf("recv from client %d bytes OOB data : %s\n", ret, buf);
        }

        
        
    }


    exit(EXIT_SUCCESS);


}
