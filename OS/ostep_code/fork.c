

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/wait.h>

int main( int argc, char* argv[] )
{

    printf("hello world (pid : %d)\n", (int)getpid());

    pid_t pid = fork();

    if( pid < 0 )
    {
        fprintf(stderr, "fork error\n");
        exit(EXIT_FAILURE);
    }
    else if( pid == 0 ) // 子进程中获得返回值为0
    {

        printf("I am child (pid : %d)\n", (int)getpid());

    }
    else    // pid > 0 表示父进程. 即父进程中获得返回值是新创建的子进程pid
    {
        
        printf("I am parent of %d, my pid (pid : %d)\n", pid, (int)getpid());
        wait(NULL);
        
    }

    return 0;

}