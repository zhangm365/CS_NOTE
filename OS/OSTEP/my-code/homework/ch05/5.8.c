

#include <stdio.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>

int main( int argc, char *argv[] )
{
    
    
    int fd[2];
    int ret = pipe(fd);

    if( ret < 0 )
    {
    
        fprintf(stderr, "pipe error\n");
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

        printf("I am child(%d)\n", getpid());

        close(fd[1]);
        char buf[256];

        int r = read(fd[0], buf, 256);
        if( r < 0 )
        {
            perror("child read\n");
            exit(EXIT_FAILURE);
        }

        buf[r] = '\0';
        printf("read from parent : %s\n", buf);

        close(fd[0]);
    }
    else
    {
        
        printf("I am parent(%d)\n", getpid());
        
        close(fd[0]);

        char buf[] = "hello child, I am your parent";
        
        int w = write(fd[1], buf, strlen(buf) + 1);
        if( w < 0 )
        {
            perror("parent write\n");
            exit(EXIT_FAILURE);
        }

        printf("parent has send %d bytes, data : %s\n", w, buf);

        int wc = wait(NULL);
        printf("wc = %d\n", wc);  // 返回 child's pid

        close(fd[1]);
        
    }

    return 0;

}
