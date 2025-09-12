

#include <stdio.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <fcntl.h>

int main( int argc, char *argv[] )
{
    
    int x = 10;
    printf("hello world(%d), x = %d\n", getpid(), x);
    pid_t pid = fork();

    if( pid < 0 )
    {
        fprintf(stderr, "fork error\n");
        exit(EXIT_FAILURE);
    }
    else if( pid == 0 )
    {
        while(1)
        {
            printf("I am child(%d), before x = %d\n", getpid(), x);
            x += 10;
            printf("I am child(%d), after x = %d\n", getpid(), x);
            sleep(3);
        }
        
    }
    else
    {
        
        while(1)
        {
            printf("I am parent(%d), before x = %d\n", getpid(), x);
            x += 100;
            printf("I am parent(%d), after x = %d\n", getpid(), x);
            // wait(NULL);
            sleep(5);
        }
        
    }

    return 0;

}