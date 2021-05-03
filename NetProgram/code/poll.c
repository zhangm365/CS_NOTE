/*
NAME
       poll - input/output multiplexing
       	poll的功能与select类似，也是用来监听多个文件描述符
       	是否可读、可写、出错了。
       	poll用到一个struct pollfd的结构体，用来表示文件描述符是否就绪。

       	struct pollfd
       	{
       		int fd; //你关心的文件描述符
       		short events;//你所关心的该文件的事件
       				//在linux内核里面，用bit位来表示文件的可读、可写、
       				出错、等等事件。
       				比如:POLLIN 表示数据可读的事件
       						POLLOUT表示数据可写的事件
       				
       		short revents;// return events 　内核返回的关于这个文件的就绪的事件。
       	};

SYNOPSIS
       #include <poll.h>

       int poll(struct pollfd fds[], nfds_t nfds, int timeout);
       		fds: 你所关心的文件描述符struct pollfd的数组
       		nfds: 第一个参数数组的大小，也就是你所头发的文件个数
       		timeout: 超时时间。单位为毫秒。
       		返回值:
       			> 0表示就绪的文件个数
       			=0:表示超时了
       			<0: 出错了。


*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> //unix域协议头文件
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
 #include <poll.h>


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
	unlink(localpath);
	
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

 
	struct pollfd fds[1];
	while (1)
	{

		fds[0].fd = sock;
		fds[0].events = POLLIN;

		r = poll(fds, 1, 2000);
		if (r < 0)
		{
			perror("poll error:");
			break;
		}else if (r == 0)
		{
			printf("timeout\n");
			continue;
		}
		 
		if (fds[0].revents & POLLIN) //POLL_IN事件产生
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
	unlink(UNIX_PATH_1);
	return 0;
}

