#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <error.h> 
#include <errno.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
 
const char* str = "SOCKET PAIR TEST.";
 
int main(int argc, char* argv[]){
    char buf[128] = {0};
    int socket_pair[2]; 
    pid_t pid; 
 
    if(socketpair(AF_UNIX, SOCK_STREAM, 0, socket_pair) == -1 ) { 
        printf("Error, socketpair create failed, errno(%d): %s\n", errno, strerror(errno));
        return EXIT_FAILURE; 
    } 
    printf("%d, %d\n", socket_pair[0], socket_pair[1]);
    int size = write(socket_pair[0], str, strlen(str));
    //可以读取成功；
    read(socket_pair[1], buf, size);    // 从 socket_pair[0] 读取会阻塞
    printf("Read result: %s\n",buf);
    return EXIT_SUCCESS;    
} 
