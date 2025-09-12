
#include <stdio.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main( int argc, char *argv[] )
{
    
    printf("hello world(%d)\n", getpid());

    int fd = open("./1.txt", O_CREAT| O_RDWR | O_TRUNC, S_IRWXU);

    if( fd < 0 )
    {
        fprintf(stderr, "fork error\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if( pid < 0 )
    {
        fprintf(stderr, "fork error\n");
        exit(EXIT_FAILURE);
    }
    else if( pid == 0 )
    {
        
        char buf[] = "hello child\n";
        printf("I am child(%d), writing...fd = %d\n", getpid(), fd);
        for( int i = 0; i < 5; ++i )
            write(fd, buf, strlen(buf));
        printf("I am child(%d), write done...\n", getpid());
        close(fd);
        
        
    }
    else
    {
        
        char buf[] = "hello parent\n";
        printf("I am parent(%d), writing...fd = %d\n", getpid(), fd);

       for( int i = 0; i < 5; ++i )
            write(fd, buf, strlen(buf));
        printf("I am parent(%d), write done...\n", getpid());
        
        wait(NULL);
        close(fd);
       
        
    }

    return 0;

}