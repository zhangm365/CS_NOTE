

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>


void unix_error( char *msg )
{

    fprintf(stderr, "%s : %s \n", msg, strerror(errno));
    exit(EXIT_FAILURE);

}

int main( int argc, char *argv[], char *envp[] )
{
    
    printf("Command line arguments:\n");
    for( int i = 0 ; argv[i] != NULL; ++i )
        printf("argv[%d] : %s\n", i, argv[i]);

    
    printf("\n");
    printf("Environment variables:\n");
    for( int i = 0; envp[i] != NULL; ++i )
        printf("envp[%d] : %s\n", i, envp[i]);

    return 0;

}
