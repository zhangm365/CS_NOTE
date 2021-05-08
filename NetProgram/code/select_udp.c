
/*
NAME
       select - synchronous I/O multiplexing
       	select��·���ã���һ������������ͬʱ����
       	����ļ��������Ƿ�ɶ�����д������

       	select��ʵ�ֵ�ʱ���õ���fd_set����Զ�������͡�
       	fd_set������ʾһ���ļ��������ļ��ϡ�
       	FD_ZERO :���������������ļ��������ļ��ϡ�
       	FD_SET(int fd, fd_set *fdset): ������fd����ļ��������ӵ�fdset���������ȥ��
       	FD_CLR(int fd, fd_set *fdset):������fd����ļ��������Ӽ���fdset�������
       	FD_ISSET(int fd, fd_set*fdset):�����ж�fd����ļ��������Ƿ��ڼ���fdset�С�

SYNOPSIS
       #include <sys/select.h>
       int select(int nfds, 
       	fd_set *restrict readfds,  
       	fd_set *restrict writefds, 
       	fd_set *restrict errorfds,
              struct timeval *restrict timeout);
		nfds:Ҫ�������ļ������������������Ǹ��ļ���������1
              readfds: ��ʾҪ�����Ŀɶ����ļ����������ϡ�
              writefds:��ʾҪ�����Ŀ�д���ļ����������ϡ�
              errorfds:��ʾҪ�����ĳ�����ļ����������ϡ�
              timeout:��ʱʱ�䡣
				struct timeval
				{
					long tv_sec; //��
					long tv_usec;//΢��
				};
				����:
				struct timeval tv;
				tv.tv_sec = 5;
				tv.tv_usec = 0;

		����ֵ:
			> 0 : ��ʾ�������ļ��������ĸ���
			=0: ��ʱ�ˡ�
			< 0 :�����ˡ�
			select���غ�readfds, writefds, errorfds������������ֻ�����Ѿ�������
				�ļ�����������
			select���غ󣬡�timeout�����ֵҲ�ı��ˣ�Ϊʣ�µ�ʱ������
				
              
       void FD_CLR(int fd, fd_set *fdset);
       int FD_ISSET(int fd, fd_set *fdset);
       void FD_SET(int fd, fd_set *fdset);
       void FD_ZERO(fd_set *fdset);


*/


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> //unix��Э��ͷ�ļ�
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>



int create_unix_udp_socket(const char *localpath)
{
	int sock;
	int r;
	/*step 1: ����һ��unix��Э���׽���*/
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

		r = select(maxfd,  //һ��Ϊ����������ļ������������ֵ+��
				&rfds, //�����ɶ����ļ�����������
				NULL, //������д���ļ�����������
				NULL,//����������ļ�����������
				&timeout//������ʱʱ��
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

