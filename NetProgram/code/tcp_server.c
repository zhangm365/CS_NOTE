/*
	SOCKET API
1. socket:创建一个网络套接字
	语法:
		#include <sys/types.h>
		#include <sys/socket.h>

			socket用来创建一个网络套接字
		int socket(int domain, int type, int protocol);
			domain: 指定协议域，协议族. 
					AF_UNIX/SF_LOCAL: unix域协议族
					AF_INET: ipv4协议族
					AF_INET6:IPV6协议族
					AF_BLUETOOTH:
					....
			type:指定创建的套接字的类型:
				 SOCK_STREAM: 流式套接字 -> tcp 
				 SOCK_DGRAM: 数据报套接字　-> udp
				 SOCK_RAM: 原始套接字　　
			protocol: 指定具体的协议. 一般为0

			返回值:
				成功返回套接字描述符( >0)
				失败返回-1, errno被设置。

2. 	网络地址相关的数据结构及函数

	通用地址结构　　linux/socket.h
	struct sockaddr
	{
		sa_family_t sa_family;
		char sa_data[14];
	};

	internet 协议地址结构
	struct sockaddr_in
	{
		sa_family_t sin_family; //协议族，AF_INET
		u_int16_t sin_port; //端口号
		struct in_addr sin_addr;  //ip地址
		char sin_zero[8];

	};
	
	struct in_addr
	{
		in_addr_t s_addr;
	};

	typedef u_int32_t in_addr_t ;

	地址转换函数(点分式的ip地址　<=> 32bits整数,网络地址)

	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	
	int inet_aton(const char *cp, struct in_addr *inp);
		inet_aton用来把cp指向的点分式的ip地址字符串，
		转换成32bits整数的网络地址(转换后的结果
		保存在inp指向的结构体中。)
	
	in_addr_t inet_addr(const char *cp);
		inet_addr用来把cp指向的点分式的ip地址字符串，
		转换成一个32bits整数的网络地址ip。
		其转换结果通过函数返回值返回。
	
	in_addr_t inet_network(const char *cp);
		inet_network用来把cp指向的点分式的ip地址字符串，
		转换成一个32bits整数的主机字节序IP地址
		其转换结果通过函数返回值返回.
	


		inet_ntoa用来把in表示的32bits整数的网络地址转换成
		一个点分式的ip地址字符串，其转换结果
		通过函数返回值返回。
	char *inet_ntoa(struct in_addr in);


		下面这些函数用来在网络字节序与主机字节序之间进行转换
		

	       #include <arpa/inet.h>

		h to n: host ->network
		l :  long 长整数(32位)
		s:  short 短整形(16bits)

		n to h: network->host
       uint32_t htonl(uint32_t hostlong);

       uint16_t htons(uint16_t hostshort);

       uint32_t ntohl(uint32_t netlong);
                  
       uint16_t ntohs(uint16_t netshort);

3. bind: 把网络地址绑定到套接字上。
		一般服务器程序需要bind

		#include <sys/types.h>
		#include <sys/socket.h>

		int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
			sockfd:要绑定的套接字描述符
			addr: 网络地址。要绑定到套接字上面的网络地址。
			addrlen:　网络地址结构体的长度

		返回值:
			成功返回0
			失败返回-1, errno被设置。
4. 设置监听数目
	NAME
       listen - listen for connections on a socket

SYNOPSIS
       #include <sys/types.h>          
       #include <sys/socket.h>

		listen用来设置内核请求连接队列上的最大请求数。
       int listen(int sockfd, int backlog);
       	sockfd:要监听的套接字。要设置请求连接数的套接字
       	backlog:监听队列上最大请求数。
       	返回值:
       		成功返回0,
       		失败返回-1, errno被设置

5. accept: 在监听套接字(listen后的套接字)上等待并接受客户端的连接请求
	NAME
       accept - accept a new connection on a socket

SYNOPSIS
       #include <sys/socket.h>

	
       int accept(int socket, struct sockaddr *restrict address,    socklen_t *restrict address_len);
       	socket:监听套接字
       	address:struct sockaddr的指针，用来保存客户端的网络地址。
       	address_len: 指针。用来保存客户端网络地址的长度
       			NOTE:此处在调用时address_len里需要保存address指向的那个结构体
       			的大小，函数返回时，address_len指向客户端地址的实际大小。
       	返回值:
       		成功返回一个连接套接字(>0),
       			此连接套接字表示与一个客户端的连接，
       			是一个文件描述符，read/write,close
       		失败返回-1, errno被设置。

6. connect: 　连接TCP服务器
	NAME
       connect - connect a socket

SYNOPSIS
       #include <sys/socket.h>

       int connect(int socket, const struct sockaddr *addr,  socklen_t addr_len);
       	socket:套接字描述符。
       	addr: struct sockaddr的指针，指向服务器的地址。
       	addr_len: 第二个参数指向的结构体的长度
       	
		返回值:
			成功返回0
			失败返回-1, errno被设置
7. 往套接字上发送数据
	write/send/sendto　这三个函数在发送数据时，tcp应用都可以用
		而udp只能用sendto

	int write(int fd, void *buf, size_t size); //此处省略xxx个字，前面文件IO已经提到

	NAME
       send - send a message on a socket

	SYNOPSIS
       #include <sys/socket.h>

       ssize_t  send(int socket, const void *buffer, size_t length,    int flags);
       	socket: 套接字描述符。表示要往哪个套接字上发数据
       	buffer:要发送的数据的首地址
       	length:意向要发送的数据的长度
       	flags : 此处为0

       	返回值:
       		成功返回发送的字节数
       		失败返回-1,errno被设置
	==
	NAME
       sendto - send a message on a socket

	SYNOPSIS
       #include <sys/socket.h>

       ssize_t  sendto(int  socket,  const  void  *message,  size_t   length, int flags, 
       		const struct sockaddr *dest_addr,
             		 socklen_t dest_len);
             		此函数前面四个参数，与send一样。
             		socket:
             		message:
             		length:
             		flags:

             		dest_addr:表示数据的发送目的地。
             		dest_len:表示上一个参数结构体的长度。
             	返回值:
             		成功返回发送的字节数
             		失败返回-1, errno被设置

8. 在套接字上面接收数据
	read/recv/recvfrom  这三个参数在接收数据，tcp应用都可以用
		而udp只能用recvfrom
		

NAME
       recv - receive a message from a connected socket

SYNOPSIS
       #include <sys/socket.h>

       ssize_t  recv(int  socket,  void *buffer, size_t length, int   flags);
       	socket: 套接字描述符。表示要从哪个套接字上接收数据
       	buffer:指针，用来保存接收到的数据
       	length:想要接收多少数据，以字节为单位
       	flags: 为0
       	返回值:
       		> 0: 成功接收到多少数据
       		= -1: 失败，errno被设置
       		= 0: 对方已经把连接关闭了
		
	====
	NAME
       recvfrom - receive a message from a socket

SYNOPSIS
       #include <sys/socket.h>

       ssize_t  recvfrom(int  socket, void *restrict buffer, size_t   length,
              int flags, struct sockaddr *restrict address,
              socklen_t *restrict address_len);

		此参数前面四个参数与recv一样
		address: 网络地址结构体指针。表示要从哪个主机上接收数据
		address_len:上面那个参数指针的结构体的长度

	返回值:
		       > 0: 成功接收到多少数据
       		= -1: 失败，errno被设置
       		= 0: 对方已经把连接关闭了

9. shutdown :关闭套接字
	NAME
       shutdown - shut down socket send and receive operations

	SYNOPSIS
       #include <sys/socket.h>

       int shutdown(int socket, int how);
       	socket:要关闭的套接字
       	how: 关闭方式，有以下三种情况
       		SHUT_RD: 关闭读
       		SHUT_WR:　关闭写
       		SHUT_RDWR:　关闭读写

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

	/*step 1: 创建一个套接字*/
	sock = socket(AF_INET,  
				SOCK_STREAM, 
				0
				);
	if (sock == -1)
	{
		perror("socket error:");
		return -1;
	}


	/*step 3: 绑定。*/
	/*struct sockaddr_in
	{
		sa_family_t sin_family; //协议族，AF_INET
		u_int16_t sin_port; //端口号
		struct in_addr sin_addr;  //ip地址
		char sin_zero[8];

	};*/

	struct sockaddr_in  servAddr;
	bzero(&servAddr, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	//inet_aton("192.168.1.204", &(servAddr.sin_addr));
	//servAddr.sin_addr.s_addr = inet_addr("192.168.1.204");
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //表示主机上任一网卡的地址都可以
											  //让系统自动帮我去选一个网卡地址
	servAddr.sin_port = htons( 8888);  //

	r = bind(sock, (const struct sockaddr*) &servAddr, sizeof(servAddr));

	/*step 4 : listen*/
	listen(sock,  10);


	/*step 5: accept*/
	struct sockaddr_in cliAddr; //用来保存客户端的地址
	socklen_t addrlen; //用来保存客户端地址的长度
	addrlen = sizeof(struct sockaddr_in); //NOTE: addrlen在调用accept前存放保存客户端地址的结构体的长度
	
	
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

