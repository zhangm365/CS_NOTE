/*
NAME
       poll - input/output multiplexing
       	poll�Ĺ�����select���ƣ�Ҳ��������������ļ�������
       	�Ƿ�ɶ�����д�������ˡ�
       	poll�õ�һ��struct pollfd�Ľṹ�壬������ʾ�ļ��������Ƿ������

       	struct pollfd
       	{
       		int fd; //����ĵ��ļ�������
       		short events;//�������ĵĸ��ļ����¼�
       				//��linux�ں����棬��bitλ����ʾ�ļ��Ŀɶ�����д��
       				�����ȵ��¼���
       				����:POLLIN ��ʾ���ݿɶ����¼�
       						POLLOUT��ʾ���ݿ�д���¼�
       				
       		short revents;// return events ���ں˷��صĹ�������ļ��ľ������¼���
       	};

SYNOPSIS
       #include <poll.h>

       int poll(struct pollfd fds[], nfds_t nfds, int timeout);
       		fds: �������ĵ��ļ�������struct pollfd������
       		nfds: ��һ����������Ĵ�С��Ҳ��������ͷ�����ļ�����
       		timeout: ��ʱʱ�䡣��λΪ���롣
       		����ֵ:
       			> 0��ʾ�������ļ�����
       			=0:��ʾ��ʱ��
       			<0: �����ˡ�


*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> //unix��Э��ͷ�ļ�
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
 #include <poll.h>


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
		 
		if (fds[0].revents & POLLIN) //POLL_IN�¼�����
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

