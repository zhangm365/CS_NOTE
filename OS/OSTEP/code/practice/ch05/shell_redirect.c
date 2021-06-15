


/*
    shell 程序 重定向的原理 ：
    fork进程后， 在子进程中在执行 exec 函数前 先关闭 标准输出, 这样程序的输出重定向到指定的文件。
    父进程 wait 子进程结束
*/

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/wait.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( int argc, char* argv[] )
{



    pid_t pid = fork();

    if( pid < 0 )
    {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if( pid == 0 ) // child process
    {
        
        close(STDOUT_FILENO);   // 在执行 exec 函数前, 先关闭标准输出 .
        open( "./a.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU );

        char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc" (word count)
        myargs[1] = strdup("shell_redirect.c");  //argument : file to count
        myargs[2] = NULL;
        execvp(myargs[0], myargs);  // runs word count
        printf("this should't print out\n");


    }
    else
    {
        wait(NULL);
        
    }



    return 0;

}