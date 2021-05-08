# 同步I/O复用

## 1. select函数

允许应用程序同时监听多个文件描述符，等到用于描述某类I/O操作的一个或多个fd "准备就绪"。

>   准备就绪：无阻塞地进行对应的I/O操作。

可读、可写、异常事件的三个集合分别被监听是否有就绪事件发生。当有事件发生时，对应集合上的fd将被修改并返回。

```c
/* According to POSIX.1-2001, POSIX.1-2008 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/*
	@ nfds : 指定被监听的文件描述符总数 : 设置为三个集合中的编号最大fd,然后加1。
	@ readfds : 指定可读fd集合;
	@ writefds : 可写fd集合;
	@ exceptfds : 异常fd集合;
	@ timeout : 微妙级定时：设置一个间隔用于等待select阻塞等待一个fd是否就绪。
	The call will block until either:
	
       *  a file descriptor becomes ready;
       *  the call is interrupted by a signal handler; or
       *  the timeout expires.
	@ return value：成功返回三个修改集合上的文件描述符总数;
				   失败返回-1, 并设置errno
	
*/

int select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout);


/*
	@ 用于操作fd集合的一系列函数
*/
void FD_CLR(int fd, fd_set *set);	// clear: 移除一个集合上给定的fd
int  FD_ISSET(int fd, fd_set *set);	// 判断一个集合上的fd是否被设置
void FD_SET(int fd, fd_set *set);	// 设置集合上对应的fd
void FD_ZERO(fd_set *set);			// 清除一个集合上所有位

```

