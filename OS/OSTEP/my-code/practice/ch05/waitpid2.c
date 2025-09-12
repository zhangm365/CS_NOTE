

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define N 3

void unix_error( char *msg )
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
    pid_t pid[N];

    /* Parent creates N children */
    for (i = 0; i < N; i++)                       //line:ecf:waitpid1:for
	    if ((pid[i] = Fork()) == 0)  /* Child */     //line:ecf:waitpid1:fork
	        exit(100+i);                         //line:ecf:waitpid1:exit


    i = 0 ;
    pid_t retpid;
    /* Parent reaps N children in order */
    while ((retpid = waitpid(pid[i++], &status, 0)) > 0) { //line:ecf:waitpid1:waitpid
        if (WIFEXITED(status))                    //line:ecf:waitpid1:wifexited
            printf("child %d terminated normally with exit status=%d\n",
            retpid, WEXITSTATUS(status));     //line:ecf:waitpid1:wexitstatus
        else
            printf("child %d terminated abnormally\n", retpid);
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD)                          //line:ecf:waitpid1:errno
	    unix_error("waitpid error");

    exit(0);
}
