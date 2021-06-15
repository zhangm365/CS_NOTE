



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

        printf("child #1(%d)\n", getpid());

        close(fd[0]);
        dup2(fd[1], 1); // redirect stdout to fd[1]

        printf("hello, parent");

        close(fd[0]);
    }
    else
    {
        
        printf("parent #1(%d)\n", getpid());
        
        // close(fd[1]);

        int pc = fork();

        if( pc < 0 )
        {
            perror("again fork\n");
            exit(EXIT_FAILURE);
        } 
        else if( pc == 0 )
        {
            
            printf("child #2\n");
            close(fd[1]);
            dup2(fd[0], 0); 
            char buf[256];
            int r = read(STDIN_FILENO, buf, 256);
            printf("buf = %s\n", buf);

        }
        else
        {

            int wc = waitpid(pc, NULL, 0);
            printf("goodbye\n");

        }

        
    }

    return 0;

}
