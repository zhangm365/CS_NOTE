



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
        printf("I am child(%d), before x = %d\n", getpid(), x);
        x += 10;
        printf("I am child(%d), after x = %d\n", getpid(), x);
        /*
            @brief 
                wait 函数放在子进程中会errno返回 -1
        int w = wait(NULL);
        printf("w = %d\n", w);
        */
       
    }
    else
    {
        
        printf("I am parent(%d), before x = %d\n", getpid(), x);
        x += 100;
        printf("I am parent(%d), after x = %d\n", getpid(), x);
        int w = wait(NULL);
        printf("w = %d\n", w);  // 返回 child's pid

        
        
    }

    return 0;

}