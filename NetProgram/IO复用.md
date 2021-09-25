# 同步`I/O`复用

## 1. `select `函数

允许应用程序同时监听多个文件描述符，等到用于描述某类`I/O`操作的一个或多个`fd ` "准备就绪"。但是可以监听的`fd`最大数量为`1024`个。

>   准备就绪：无阻塞地进行对应的`I/O`操作。

可读、可写、异常事件的三个集合分别被监听是否有就绪事件发生。当有事件发生时，对应集合上的`fd`将被修改并返回。

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
	@ timeout : 微妙级定时：设置一个间隔用于select阻塞等待是否有监听的fd准备就绪。
	The call will block until either:
	
       *  a file descriptor becomes ready;
       *  the call is interrupted by a signal handler; or
       *  the timeout expires.
       
    If both fields of the timeval structure are zero, then select() returns immediately.  (This is useful for polling.)  If timeout is 		NULL (no timeout), select() can block indefinitely.
    
	@ return value：成功返回三个修改集合上的文件描述符总数;
				   失败返回-1, 并设置errno
	
*/

int select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout);


/*
	@ 用于操作fd_set集合的一系列函数
*/
void FD_CLR(int fd, fd_set *set);	// clear: 移除集合上的对应位fd
int  FD_ISSET(int fd, fd_set *set);	// 判断一个集合上的位fd是否被修改返回
void FD_SET(int fd, fd_set *set);	// 设置集合上的位fd
void FD_ZERO(fd_set *set);			// 清除一个集合上所有位

```

## 2. `poll`函数

`poll()`系统调用和`select()`功能类似，都是等待一个集合上是否有`fd`准备就绪。

```c

#define _GNU_SOURCE         /* See feature_test_macros(7) */

#include <poll.h>

int poll(struct pollfd *fds, nfds_t nfds, int timeout);

/*	arguement
	@ fds：一个struct pollfd结构定义给出
	@ nfds: 指定fds数组的大小
	@ timeout：微妙级定时
	Specifying a negative value in timeout means an infinite timeout.  Specifying a timeout of zero causes poll() to return immediately, 		even if no file descriptors are ready.

*/
struct pollfd 
{
    int   fd;         /* file descriptor */
    short events;     /* requested events */
    short revents;    /* returned events */
};


```

## 3. `epoll `函数

### 3.1 `epoll_create1`

### 3.2 `epoll_ctl`

### 3.3 `epoll_wait`

