

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/wait.h>

#include <unistd.h>

int main( int argc, char* argv[] )
{


    printf("hello world(pid : %d)\n", (int)getpid());

    pid_t pid = fork();

    if( pid < 0 )
    {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if( pid == 0 ) // child process
    {
        printf("I am child (pid : %d)\n", (int)getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc" (word count)
        myargs[1] = strdup("fork_exec.c");  //argument : file to count
        myargs[2] = NULL;
        execvp(myargs[0], myargs);  // runs word count
        printf("this should't print out\n");


    }
    else
    {
        pid_t w_pid = wait(NULL);
        printf("I am parent of %d, (wc : %d), (pid : %d)\n", pid, w_pid, (int)getpid());
    }



    return 0;

}