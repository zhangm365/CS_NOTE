

#include <stdio.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>


int main()
{


    pid_t pid = fork();


    if( pid < 0 )
    {
        fprintf(stderr, "fork error\n");
        exit(EXIT_FAILURE);
    }
    else if( pid == 0 )
    {

        char * const argv[] = {"ls", NULL}; // 参数列表
        char * const envp[] = {NULL};   // 环境变量列表

        // execl("/bin/ls", "ls", NULL);
        // execle("/bin/ls", "ls", NULL, envp);
        // execlp("ls", "ls", NULL);

        // execv("/bin/ls", argv);
        execve("/bin/ls", argv, envp);
        // execvp("ls", argv);
        // execvpe("ls", argv, envp);
    }
    else
    {
        wait(NULL);
    }


    return 0;

}