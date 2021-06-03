#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_EVENTS 1

int main (void)
{
    int epfd;
    epfd = epoll_create(5); /* 创建epoll实例 */
    if (epfd < 0) 
    {
        perror ("epoll_createl");
        exit(EXIT_FAILURE);
    }

    struct epoll_event *events;
    int nr_events, i;
    events = malloc (sizeof (struct epoll_event) * MAX_EVENTS);
    if (!events) 
    {
        perror("malloc");
        free(events);
        exit(EXIT_FAILURE);
    }

    /* 打开一个普通文本文件 */
    int listen_fd = open ("./epoll.txt", O_RDONLY);
    printf("listen_fd = %d\n", listen_fd);
    
    int ret;
    events[i].data.fd = listen_fd; /* epoll调用返回后，返回给应用进程的fd号 */
    events[i].events = EPOLLIN; /* 需要监听的事件类型 */
    ret = epoll_ctl (epfd, EPOLL_CTL_ADD, listen_fd, &events[i]); /* 注册fd到epoll实例上 */
    if (ret) 
    {
        
        printf("ret %d, errno %d\n", ret, errno);
        perror ("epoll_ctl");
        free(events);
        exit(EXIT_FAILURE);

    }
    

    /* 应用进程阻塞在epoll上，超时时长置为-1表示一直等到有目标事件才会返回 */
    nr_events = epoll_wait(epfd, events, MAX_EVENTS, -1);
    if (nr_events < 0) 
    {
        perror ("epoll_wait");
        free(events);
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < nr_events; i++) {
        /* 打印出处于就绪状态的fd及其事件 */
        printf("event=%d on fd=%d\n", events[i].events, events[i].data.fd);
    }

    free (events);
    close(epfd);
    return 0;
}