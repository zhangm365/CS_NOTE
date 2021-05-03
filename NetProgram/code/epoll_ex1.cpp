


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>

int main()
{

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(m_listenfd >= 0);

    //优雅关闭连接
    if (0 == m_OPT_LINGER)
    {
        struct linger tmp = {0, 1};
        setsockopt(m_listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));
    }
    else if (1 == m_OPT_LINGER)
    {
        struct linger tmp = {1, 1};
        setsockopt(m_listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));
    }

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(m_port);

    int flag = 1;
    setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    ret = bind(m_listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret >= 0);
    ret = listen(m_listenfd, 5);
    assert(ret >= 0);
    
    #define MAX_EVENTS 10
                                                    struct epoll_event ev, events[MAX_EVENTS];
                                                    int conn_sock, nfds, epollfd;

                                                    /* Code to set up listening socket, 'listen_sock',
                                                        (socket(), bind(), listen()) omitted */

                                                    epollfd = epoll_create(10);
                                                    if (epollfd == -1) {
                                                        perror("epoll_create1");
                                                        exit(EXIT_FAILURE);
                                                    }

                                                    ev.events = EPOLLIN;
                                                    ev.data.fd = m_listenfd;
                                                    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
                                                        perror("epoll_ctl: listen_sock");
                                                        exit(EXIT_FAILURE);
                                                    }

                                                    for (;;) {
                                                        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
                                                        if (nfds == -1) {
                                                            perror("epoll_wait");
                                                            exit(EXIT_FAILURE);
                                                        }

                                                        for (n = 0; n < nfds; ++n) {
                                                            if (events[n].data.fd == listen_sock) {
                                                                conn_sock = accept(listen_sock,
                                                                                    (struct sockaddr *) &addr, &addrlen);
                                                                if (conn_sock == -1) {
                                                                    perror("accept");
                                                                    exit(EXIT_FAILURE);
                                                                }
                                                                setnonblocking(conn_sock);
                                                                ev.events = EPOLLIN | EPOLLET;
                                                                ev.data.fd = conn_sock;
                                                                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock,
                                                                            &ev) == -1) {
                                                                    perror("epoll_ctl: conn_sock");
                                                                    exit(EXIT_FAILURE);
                                                                }
                                                            }
                                                        }
                                                    }



    


}
