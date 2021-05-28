
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



int main( int argc, char *argv[] )
{
    
    int fd[2];
    pid_t pid;
    
    char buf;
    
   	if( argc != 2 )
    {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if( pipe(fd) == -1 )
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    pid = fork();
    
    if( pid == -1 )
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if( pid == 0 )	/* Child read from pipe */
    {
        close(fd[1]);
        while( read(fd[0], &buf, 1) > 0 )
        {
            write( STDOUT_FILENO, &buf, 1 );
        }
        
        write( STDOUT_FILENO, "\n", 1 );
        close(fd[0]);
        
        _exit(EXIT_SUCCESS);
        
    }
    else	// parent write argv[1] to pipe
    {
        close(fd[0]);
        write( fd[1], argv[1], strlen(argv[1]) );
        close(fd[1]);	// 
        wait(NULL);		// write for child
        
        exit(EXIT_SUCCESS);
    }

    
    return 0;


}