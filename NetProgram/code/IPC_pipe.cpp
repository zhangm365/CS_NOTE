
/*

    @ pipe创建一个管道, 用于进程间的单向数据通道。
    @ 返回值：成功返回0, 失败返回-1
    @ fd[0],fd[1]分别指向管道的两端, 且fd[0]只可用来读, fd[1]只用来写

*/


#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>


int main()
{

    int fd[2];

    int ret = pipe(fd); // 创建管道
    assert(ret > -1);
    
    
    pid_t pid = fork();

    if( pid == 0 ) // child
    {

        int i = 0;
        close(fd[0]);   // 关闭读端
        const char *msg = "I am a child";
        while( i < 5 )
        {
            write( fd[1], msg, strlen(msg)+1 );
            sleep(2);
            i++;
        }

        close(fd[1]);
        _exit(EXIT_SUCCESS);

    }
    else if( pid > 0 )  // parent
    {

        close(fd[1]);   // 关闭写端
        char buf[100];
        
        int j = 0;
        while( j < 5 )
        {
            
            memset(buf, 0, sizeof(buf));
            ssize_t len = read(fd[0], buf, sizeof(buf));
            if( len > 0 )
            {

                buf[len-1] = '\0';
                printf("recv : %ld from child , %s\n", len, buf);
            }

            j++;        
        }

        close(fd[0]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        perror("fork error!");
        exit(EXIT_FAILURE);
    }

    return 0;

}