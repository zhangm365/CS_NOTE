
/*
NAME
       select - synchronous I/O multiplexing
       	select多路复用，它一个函数，可以同时监听
       	多个文件描述符是否可读、可写、出错。

       	select在实现的时候，用到了fd_set这个自定义的类型。
       	fd_set用来表示一个文件描述符的集合。
       	FD_ZERO :这个函数用来清空文件描述符的集合。
       	FD_SET(int fd, fd_set *fdset): 用来把fd这个文件描述符加到fdset这个集合中去。
       	FD_CLR(int fd, fd_set *fdset):用来把fd这个文件描述符从集合fdset中清掉。
       	FD_ISSET(int fd, fd_set*fdset):用来判断fd这个文件描述符是否在集合fdset中。

SYNOPSIS
       #include <sys/select.h>
       int select(int nfds, 
       	fd_set *restrict readfds,  
       	fd_set *restrict writefds, 
       	fd_set *restrict errorfds,
              struct timeval *restrict timeout);
		nfds:要监听的文件描述符集合里最大的那个文件描述符加1
              readfds: 表示要监听的可读的文件描述符集合。
              writefds:表示要监听的可写的文件描述符集合。
              errorfds:表示要监听的出错的文件描述符集合。
              timeout:超时时间。
				struct timeval
				{
					long tv_sec; //秒
					long tv_usec;//微秒
				};
				例如:
				struct timeval tv;
				tv.tv_sec = 5;
				tv.tv_usec = 0;

		返回值:
			> 0 : 表示就绪的文件描述符的个数
			=0: 超时了。
			< 0 :出错了。
			select返回后，readfds, writefds, errorfds这三个集合里只保留已经就绪的
				文件描述符　。
			select返回后，　timeout里面的值也改变了，为剩下的时间数。
				
              
       void FD_CLR(int fd, fd_set *fdset);
       int FD_ISSET(int fd, fd_set *fdset);
       void FD_SET(int fd, fd_set *fdset);
       void FD_ZERO(fd_set *fdset);


*/


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> //unix域协议头文件
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>



int create_unix_udp_socket(const char *localpath)
{
	int sock;
	int r;
	/*step 1: 创建一个unix域协议套接字*/
	sock = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sock == -1)
	{
		perror("socket error:");
		return -1;
	}

	/* unlink */

	/* step 2: bind*/
	struct sockaddr_un localAddr;
	memset(&localAddr, 0, sizeof(localAddr));
	localAddr.sun_family = AF_UNIX;
	strcpy(localAddr.sun_path, localpath);

	r = bind(sock, (struct sockaddr*)&localAddr, sizeof(localAddr));
	if (r == -1)
	{
		perror("bind error:");
		return -1;
	}

	return sock;
}

int send_data(int sock, const char *remotepath, char *buf, int len)
{
	struct sockaddr_un remoteAddr;
	memset(&remoteAddr, 0, sizeof(remoteAddr));
	remoteAddr.sun_family = AF_UNIX;
	strcpy(remoteAddr.sun_path, remotepath);

	int r;
	r = sendto(sock, buf, len, 0, (struct sockaddr*)&remoteAddr, sizeof(remoteAddr));
	if (r == -1)
	{
		perror("sendto error:");
		return -1;
	}
	return r;
}


#define UNIX_PATH_1  "/tmp/1.socket"



int main(int argc, char *argv[])
{

	int sock = create_unix_udp_socket(UNIX_PATH_1);

	char buf[1024];
	struct sockaddr_un remoteAddr;
	socklen_t addrLen = sizeof(remoteAddr);

	int r;

	fd_set rfds;
	int maxfd;
	struct timeval timeout;

	while (1)
	{
		FD_ZERO(&rfds);
		FD_SET(sock, &rfds);

		maxfd = sock  + 1;
		timeout.tv_sec = 2;
		timeout.tv_usec = 0;

		r = select(maxfd,  //一般为你想监听的文件描述符里最大值+１
				&rfds, //监听可读的文件描述符集合
				NULL, //监听可写的文件描述符集合
				NULL,//监听出错的文件描述符集合
				&timeout//监听超时时间
			);
		if (r < 0)
		{
			perror("select error:");
			return -1;
		} 
		else if (r == 0)
		{
			printf("timeout \n");
			continue;
		}

		if (FD_ISSET(sock, &rfds))
		{
			
			r = recvfrom(sock, buf, 1024, 0, (struct sockaddr*)&remoteAddr, &addrLen);
			if (r > 0)
			{
				buf[r] = '\0';
				printf("data: %s from %s\n", buf, remoteAddr.sun_path);
			}
	
		}


	}


	close(sock);
	return 0;

	
}

