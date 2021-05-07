# 1. struct linger 结构体

```cpp



```

# 2. 主机字节序与网络字节序

​	小端字节序：一个整数的低位字节存储在内存的低地址；

​	大端字节序：一个整数的高位字节存储在内存的高地址；

​	主机字节序：小端模式的字节序称为主机字节序；

​	网络字节序：大端模式的字节序称为网络字节序；

​	判断大小端模式字节序的方法：使用联合体进行判断

```cpp

// union联合体判断机器的字节序到底是小端模式or大端模式
union  
{
    int val;	// 4字节
    char one_byte;	// 1字节
}u_test;

u_test.val = 0x78563412;

if( u_test.one_byte == 0x12 )
{
    printf("little endian\n");
}
else if( u_test.one_byte == 0x78 )
{
    printf("big endian\n");
}
else
{
    printf("Unknown ...\n");
}



// linux下提供四个API函数来支持主机字节序和网络字节序的转换

#include <arpa/inet.h>

uint32_t htonl(uint32_t hostlong);	// The htonl() function converts the unsigned integer hostlong from host byte order to network											// byte order.

uint16_t htons(uint16_t hostshort); // The htons() function converts the unsigned short integer hostshort from host byte order to network 										// byte order.

uint32_t ntohl(uint32_t netlong);	// The ntohl() function converts the unsigned integer netlong from network byte order to host byte 										// order.

uint16_t ntohs(uint16_t netshort);	// The ntohs() function converts the unsigned short integer netshort from network byte order to host 									// byte order.
```



# 3. socket套接字

1.  在TCP/IP模型中，数据链路层、网络层、传输层的相关协议均在内核中定义实现，所以操作系统必须提供一组系统调用，使得应用程序可以访问下层协议提供的服务。实现这组系统调用的API主要是socket套接字。

    

    socket套接字定义的一组API主要提供两个功能：

    -   将应用程序数据从用户缓冲区复制到TCP/UDP内核发送缓冲区，以交付内核来处理数据；或从TCP/UDP内核接收缓冲区复制数据到用户缓冲区，以供应用程序读取数据；
    -   应用程序可以通过这些API来修改内核中各层协议的某些头部信息或者其他数据结构，从而可以精细地控制底层通信的行为；



2.  socket相关地址

    -   socket通用地址：

    ```c++
    #include <bits/socket.h>
    struct socketaddr
    {
        sa_family_t sa_family;	// sa_family 是地址族类型(sa_family_t)变量. 通常取值为AF_UNIX, AF_INET, AF_INET6
        char sa_data[14];		// socket地址值
    };
    ```

    

    -   socket专用地址

    ```cpp
    // ip4地址结构体
    struct sockaddr_in
    {
    	sa_family_t sin_family;	// 地址族:AF_INET
    	uint16_t sin_port;		// 端口号, 网络字节序
        struct in_addr sin_addr;	// ipv4地址结构体
    };
    
    struct in_addr
    {
    	uint32_t s_addr;  	// ipv4地址, 网络字节序
    };
    ```

    所有socket专用地址在使用过程中，必须转化为socket通用地址socketaddr，因为所有socket编程接口使用的地址参数类型均为通用地址。

    

3.  IP地址转换函数

    通常情况下，我们使用点分十进制字符串来表示IPv4地址，使用十六进制字符串表示IPv6地址。但在编程中，我们需要先把它们转化成整数(二进制)方能使用。因此下面是一组API用来IP地址和网络字节序整数之间的转换。

    ```cpp
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    
    typedef uint32_t in_addr_t;
    struct in_addr
    {
    	in_addr_t s_addr;  	// ipv4地址, 网络字节序
    };
    
    /*
    	@ desc: converts the Internet host address cp from the IPv4 numbers-and-dots notation into binary form (in network byte order) 			and stores it in the structure that inp points to.
    	@ return value: success for 1, 0 for fail.
    */
    int inet_aton(const char *cp, struct in_addr *inp);	
    
    /*
    	@ converts the Internet host address cp from the IPv4 numbers-and-dots notation into binary data in network byte order.
    	@ return value: -1 for fail.
    	@ key: Use of this function is problematic because -1 is a valid address (255.255.255.255). So, avoid the its use in favor of 			inet_aton(), inet_pton();
    */
    in_addr_t inet_addr(const char *cp);
    
    /*
    	@ desc: The inet_ntoa() function converts the Internet host address in, given in network byte order, to a string in IPv4 dotted-		decimal notation. The string is returned in a statically allocated buffer, which subsequent calls will overwrite.
    */
    char *inet_ntoa(struct in_addr in);
    
    ```

    

# 4. 数据读写

## 	4.1 TCP数据读写

​	socket编程接口中提供了几个专门用于socket数据读写的系统调用，它们增加了对数据读写的控制。其中用于TCP流数据读写的系统调用为：	

```c++
#include <sys/types.h>
#include <sys/socket.h>
/*
	@ The  recv(),  recvfrom(),  and recvmsg() calls are used to receive messages from a socket. They may be used to receive data on 		both connectionless and connection-oriented sockets.
	
	@ Those calls places the received message into the buffer buf.  The caller must specify the size of the buffer in len.
	
	@ The following call
		recv(sockfd, buf, len, flags);
    is equivalent to
    	recvfrom(sockfd, buf, len, flags, NULL, NULL);
*/


/*
	The recv() call is normally used only on a connected socket
*/
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
ssize_t send(int sockfd, const void *buf, size_t len, int flags);

/*
*/
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);


ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
/*
	The recvmsg() call uses a msghdr structure to minimize the number of directly supplied arguments. This structure is defined as 			follows in <sys/socket.h>:
*/
struct iovec {                    /* Scatter/gather array items */
    void  *iov_base;              /* Starting address */
    size_t iov_len;               /* Number of bytes to transfer */
};

struct msghdr {
    void         *msg_name;       /* Optional address */
    socklen_t     msg_namelen;    /* Size of address */
    struct iovec *msg_iov;        /* Scatter/gather array */
    size_t        msg_iovlen;     /* # elements in msg_iov */
    void         *msg_control;    /* Ancillary data, see below */
    size_t        msg_controllen; /* Ancillary data buffer len */
    int           msg_flags;      /* Flags on received message */
};


```

