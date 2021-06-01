
#include <sys/types.h>
#include <sys/stat.h>
// #include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>


int main( int argc, char *argv[] )
{
    
    if( argc != 2 )
    {
        fprintf( stderr, "Usage: %s <string>\n", argv[0] );
        return -1;
    }

    if( mkfifo( "/home/zhangmao/myFifo", 0644 ) == -1 )
    {
        if( errno != EEXIST )
        {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }

    }
    
    
    int fd = open("/home/zhangmao/myFifo", O_WRONLY);

    
    if( fd == -1 )
    {
        perror("open");
        exit(EXIT_FAILURE);        
    }
    
    printf("fd = %d\n", fd);
    int w = write( fd, argv[1], strlen(argv[1]) );
    
    if( w > 0 )
    {
        fprintf(stdout, "send the %d bytes data : \n", w);
    }
    close(fd);	// 
    
    return 0;


}