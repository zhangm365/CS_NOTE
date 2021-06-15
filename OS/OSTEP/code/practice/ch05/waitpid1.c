

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define N 3

void unix_error( const char *msg )
{

    fprintf(stderr, "%s : %s \n", msg, strerror(errno));
    exit(EXIT_FAILURE);

}

pid_t Fork()
{

    pid_t pid;

    if( (pid = fork()) < 0 )
        unix_error("fork error");
    
    return pid;

}


int main() 
{
    int status, i;
    pid_t pid;

    /* Parent creates N children */
    for (i = 0; i < N; i++)                       //line:ecf:waitpid1:for
	    if ((pid = Fork()) == 0)  /* Child */     //line:ecf:waitpid1:fork
	        exit(100+i);                         //line:ecf:waitpid1:exit


    /* Parent reaps N children in no particular order */
    while ((pid = waitpid(-1, &status, 0)) > 0) { //line:ecf:waitpid1:waitpid
        if (WIFEXITED(status))                    //line:ecf:waitpid1:wifexited
            printf("child %d terminated normally with exit status=%d\n",
            pid, WEXITSTATUS(status));     //line:ecf:waitpid1:wexitstatus
        else
            printf("child %d terminated abnormally\n", pid);
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD)                          //line:ecf:waitpid1:errno
	    unix_error("waitpid error");

    exit(0);
}
