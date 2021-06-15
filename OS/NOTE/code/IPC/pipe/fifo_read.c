


#include <sys/types.h>
#include <sys/stat.h>
// #include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define MAXSIZE 1024

int main( int argc, char *argv[] )
{
    
    if( argc != 2 )
    {
        fprintf(stderr, "Usage : %s pathname\n", argv[0] );
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);

    printf("fd = %d\n", fd);
    if( fd == -1 )
    {
        perror("open");
        exit(EXIT_FAILURE);        
    }
    
    char buf[MAXSIZE];
    
    int r = read( fd, buf, MAXSIZE );

    buf[r] = '\0';

    printf("data : %s\n", buf);

    close(fd);	// 
    
    return 0;


}