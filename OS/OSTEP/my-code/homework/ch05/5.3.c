

#include <stdio.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

void sig_handler( int signum )
{

    printf("goodbye\n");
    exit(0);

}


int main()
{

    int parent_pid = getpid();

    pid_t pid = fork();

    if( pid < 0 )
    {
        fprintf(stderr, "fork error\n");
        exit(EXIT_FAILURE);
    }

    if( pid == 0 )
    {
        printf("hello\n");
        kill(parent_pid, SIGCONT);  // 向父进程发送一个信号SIGCONT, 表示继续执行

    }
    else if( pid > 0 )
    {

        signal(SIGCONT, sig_handler);   // init signal
        pause();    // 暂停, 直到收到一个信号

    }


    return 0;

}