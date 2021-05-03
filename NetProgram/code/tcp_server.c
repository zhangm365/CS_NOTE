/*
	SOCKET API
1. socket:����һ�������׽���
	�﷨:
		#include <sys/types.h>
		#include <sys/socket.h>

			socket��������һ�������׽���
		int socket(int domain, int type, int protocol);
			domain: ָ��Э����Э����. 
					AF_UNIX/SF_LOCAL: unix��Э����
					AF_INET: ipv4Э����
					AF_INET6:IPV6Э����
					AF_BLUETOOTH:
					....
			type:ָ���������׽��ֵ�����:
				 SOCK_STREAM: ��ʽ�׽��� -> tcp 
				 SOCK_DGRAM: ���ݱ��׽��֡�-> udp
				 SOCK_RAM: ԭʼ�׽��֡���
			protocol: ָ�������Э��. һ��Ϊ0

			����ֵ:
				�ɹ������׽���������( >0)
				ʧ�ܷ���-1, errno�����á�

2. 	�����ַ��ص����ݽṹ������

	ͨ�õ�ַ�ṹ����linux/socket.h
	struct sockaddr
	{
		sa_family_t sa_family;
		char sa_data[14];
	};

	internet Э���ַ�ṹ
	struct sockaddr_in
	{
		sa_family_t sin_family; //Э���壬AF_INET
		u_int16_t sin_port; //�˿ں�
		struct in_addr sin_addr;  //ip��ַ
		char sin_zero[8];

	};
	
	struct in_addr
	{
		in_addr_t s_addr;
	};

	typedef u_int32_t in_addr_t ;

	��ַת������(���ʽ��ip��ַ��<=> 32bits����,�����ַ)

	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	
	int inet_aton(const char *cp, struct in_addr *inp);
		inet_aton������cpָ��ĵ��ʽ��ip��ַ�ַ�����
		ת����32bits�����������ַ(ת����Ľ��
		������inpָ��Ľṹ���С�)
	
	in_addr_t inet_addr(const char *cp);
		inet_addr������cpָ��ĵ��ʽ��ip��ַ�ַ�����
		ת����һ��32bits�����������ַip��
		��ת�����ͨ����������ֵ���ء�
	
	in_addr_t inet_network(const char *cp);
		inet_network������cpָ��ĵ��ʽ��ip��ַ�ַ�����
		ת����һ��32bits�����������ֽ���IP��ַ
		��ת�����ͨ����������ֵ����.
	


		inet_ntoa������in��ʾ��32bits�����������ַת����
		һ�����ʽ��ip��ַ�ַ�������ת�����
		ͨ����������ֵ���ء�
	char *inet_ntoa(struct in_addr in);


		������Щ���������������ֽ����������ֽ���֮�����ת��
		

	       #include <arpa/inet.h>

		h to n: host ->network
		l :  long ������(32λ)
		s:  short ������(16bits)

		n to h: network->host
       uint32_t htonl(uint32_t hostlong);

       uint16_t htons(uint16_t hostshort);

       uint32_t ntohl(uint32_t netlong);
                  
       uint16_t ntohs(uint16_t netshort);

3. bind: �������ַ�󶨵��׽����ϡ�
		һ�������������Ҫbind

		#include <sys/types.h>
		#include <sys/socket.h>

		int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
			sockfd:Ҫ�󶨵��׽���������
			addr: �����ַ��Ҫ�󶨵��׽�������������ַ��
			addrlen:�������ַ�ṹ��ĳ���

		����ֵ:
			�ɹ�����0
			ʧ�ܷ���-1, errno�����á�
4. ���ü�����Ŀ
	NAME
       listen - listen for connections on a socket

SYNOPSIS
       #include <sys/types.h>          
       #include <sys/socket.h>

		listen���������ں��������Ӷ����ϵ������������
       int listen(int sockfd, int backlog);
       	sockfd:Ҫ�������׽��֡�Ҫ�����������������׽���
       	backlog:���������������������
       	����ֵ:
       		�ɹ�����0,
       		ʧ�ܷ���-1, errno������

5. accept: �ڼ����׽���(listen����׽���)�ϵȴ������ܿͻ��˵���������
	NAME
       accept - accept a new connection on a socket

SYNOPSIS
       #include <sys/socket.h>

	
       int accept(int socket, struct sockaddr *restrict address,    socklen_t *restrict address_len);
       	socket:�����׽���
       	address:struct sockaddr��ָ�룬��������ͻ��˵������ַ��
       	address_len: ָ�롣��������ͻ��������ַ�ĳ���
       			NOTE:�˴��ڵ���ʱaddress_len����Ҫ����addressָ����Ǹ��ṹ��
       			�Ĵ�С����������ʱ��address_lenָ��ͻ��˵�ַ��ʵ�ʴ�С��
       	����ֵ:
       		�ɹ�����һ�������׽���(>0),
       			�������׽��ֱ�ʾ��һ���ͻ��˵����ӣ�
       			��һ���ļ���������read/write,close
       		ʧ�ܷ���-1, errno�����á�

6. connect: ������TCP������
	NAME
       connect - connect a socket

SYNOPSIS
       #include <sys/socket.h>

       int connect(int socket, const struct sockaddr *addr,  socklen_t addr_len);
       	socket:�׽�����������
       	addr: struct sockaddr��ָ�룬ָ��������ĵ�ַ��
       	addr_len: �ڶ�������ָ��Ľṹ��ĳ���
       	
		����ֵ:
			�ɹ�����0
			ʧ�ܷ���-1, errno������
7. ���׽����Ϸ�������
	write/send/sendto�������������ڷ�������ʱ��tcpӦ�ö�������
		��udpֻ����sendto

	int write(int fd, void *buf, size_t size); //�˴�ʡ��xxx���֣�ǰ���ļ�IO�Ѿ��ᵽ

	NAME
       send - send a message on a socket

	SYNOPSIS
       #include <sys/socket.h>

       ssize_t  send(int socket, const void *buffer, size_t length,    int flags);
       	socket: �׽�������������ʾҪ���ĸ��׽����Ϸ�����
       	buffer:Ҫ���͵����ݵ��׵�ַ
       	length:����Ҫ���͵����ݵĳ���
       	flags : �˴�Ϊ0

       	����ֵ:
       		�ɹ����ط��͵��ֽ���
       		ʧ�ܷ���-1,errno������
	==
	NAME
       sendto - send a message on a socket

	SYNOPSIS
       #include <sys/socket.h>

       ssize_t  sendto(int  socket,  const  void  *message,  size_t   length, int flags, 
       		const struct sockaddr *dest_addr,
             		 socklen_t dest_len);
             		�˺���ǰ���ĸ���������sendһ����
             		socket:
             		message:
             		length:
             		flags:

             		dest_addr:��ʾ���ݵķ���Ŀ�ĵء�
             		dest_len:��ʾ��һ�������ṹ��ĳ��ȡ�
             	����ֵ:
             		�ɹ����ط��͵��ֽ���
             		ʧ�ܷ���-1, errno������

8. ���׽��������������
	read/recv/recvfrom  �����������ڽ������ݣ�tcpӦ�ö�������
		��udpֻ����recvfrom
		

NAME
       recv - receive a message from a connected socket

SYNOPSIS
       #include <sys/socket.h>

       ssize_t  recv(int  socket,  void *buffer, size_t length, int   flags);
       	socket: �׽�������������ʾҪ���ĸ��׽����Ͻ�������
       	buffer:ָ�룬����������յ�������
       	length:��Ҫ���ն������ݣ����ֽ�Ϊ��λ
       	flags: Ϊ0
       	����ֵ:
       		> 0: �ɹ����յ���������
       		= -1: ʧ�ܣ�errno������
       		= 0: �Է��Ѿ������ӹر���
		
	====
	NAME
       recvfrom - receive a message from a socket

SYNOPSIS
       #include <sys/socket.h>

       ssize_t  recvfrom(int  socket, void *restrict buffer, size_t   length,
              int flags, struct sockaddr *restrict address,
              socklen_t *restrict address_len);

		�˲���ǰ���ĸ�������recvһ��
		address: �����ַ�ṹ��ָ�롣��ʾҪ���ĸ������Ͻ�������
		address_len:�����Ǹ�����ָ��Ľṹ��ĳ���

	����ֵ:
		       > 0: �ɹ����յ���������
       		= -1: ʧ�ܣ�errno������
       		= 0: �Է��Ѿ������ӹر���

9. shutdown :�ر��׽���
	NAME
       shutdown - shut down socket send and receive operations

	SYNOPSIS
       #include <sys/socket.h>

       int shutdown(int socket, int how);
       	socket:Ҫ�رյ��׽���
       	how: �رշ�ʽ���������������
       		SHUT_RD: �رն�
       		SHUT_WR:���ر�д
       		SHUT_RDWR:���رն�д

	close <=> shutdown (, SHUT_RDWR);

*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int sock;
	int r;

	/*step 1: ����һ���׽���*/
	sock = socket(AF_INET,  
				SOCK_STREAM, 
				0
				);
	if (sock == -1)
	{
		perror("socket error:");
		return -1;
	}


	/*step 3: �󶨡�*/
	/*struct sockaddr_in
	{
		sa_family_t sin_family; //Э���壬AF_INET
		u_int16_t sin_port; //�˿ں�
		struct in_addr sin_addr;  //ip��ַ
		char sin_zero[8];

	};*/

	struct sockaddr_in  servAddr;
	bzero(&servAddr, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	//inet_aton("192.168.1.204", &(servAddr.sin_addr));
	//servAddr.sin_addr.s_addr = inet_addr("192.168.1.204");
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //��ʾ��������һ�����ĵ�ַ������
											  //��ϵͳ�Զ�����ȥѡһ��������ַ
	servAddr.sin_port = htons( 8888);  //

	r = bind(sock, (const struct sockaddr*) &servAddr, sizeof(servAddr));

	/*step 4 : listen*/
	listen(sock,  10);


	/*step 5: accept*/
	struct sockaddr_in cliAddr; //��������ͻ��˵ĵ�ַ
	socklen_t addrlen; //��������ͻ��˵�ַ�ĳ���
	addrlen = sizeof(struct sockaddr_in); //NOTE: addrlen�ڵ���acceptǰ��ű���ͻ��˵�ַ�Ľṹ��ĳ���
	
	
	int connfd;
	connfd = accept(sock,
						(struct sockaddr*)&cliAddr,
						&addrlen
				);
			if (connfd  == -1)
			{
				perror("accept error:");
				return -1;
				//continue;
			}

	printf("accept a connetion from %s port[%d]\n", 
			inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
	while(1)
	{

	
		

		// char *str = "welcome to china";
		// r = write(connfd, str, strlen(str) );
		// if (r == -1)
		// {
		// 	perror("write error:");
		// 	return -1;
		// }

		char buf[1024];
	
		r = read(connfd, buf, 1024);
		if (r > 0)
		{	
			buf[r] = '\0';
			printf("%s\n",buf);
		}
	}
	close(connfd);

	close(sock);
	
	return 0;
	
}

