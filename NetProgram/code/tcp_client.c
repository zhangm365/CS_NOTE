
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include <stdlib.h>

int main(int argc, char *argv[])
{

	if (argc != 2) 
	{
		fprintf(stderr, "%s <dotted-address>\n", argv[0]);
		exit(EXIT_FAILURE);
    }

	const char *ip = argv[1];
	int sock;
	/*step 1:  socket,创建一个套接字*/
	sock = socket(
			AF_INET, /*指定要使用的协议族*/
			SOCK_STREAM , /*第二参数，指定要创建的套接字的类型*/
			0 /*第三个参数，要使用的具体协议。0表示不指定具体协议*/
		);
	if (sock == -1)
	{
		perror("sock errno:");
		return -1;
	}


	/*step 2: */
	struct sockaddr_in servAddr;
	bzero(&servAddr,sizeof(servAddr));
	servAddr.sin_family = AF_INET; //
	
	
	inet_pton( AF_INET, ip, &servAddr.sin_addr );

	servAddr.sin_port = htons( 8888);

	int r ;
	r = connect(sock, 
			(struct sockaddr*)&servAddr,
			sizeof(servAddr));
	if (r == -1)
	{
		perror("connect error:");
		return -1;
	}

	char str[1024];
	// r = read(sock, str, 1024);
	// if (r > 0)
	// {
	// 	printf("str: %s\n", str);
	// }
	while(1)
	{
		fgets(str, 1024, stdin);
		int w = write(sock, str, sizeof(str));
		if( w > 0 )
		{
			printf("sendto : %s\n", str);
		}
	}
	
	

	close(sock);
	
	return 0;
}
