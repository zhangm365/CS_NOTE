

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PATH_NAME "/home/zhangmao/msg.txt"
#define PRO_ID 66
#define MAX_SIZE 256


struct msgbuf
{
    long mtype;     // 正消息类型, > 0
    char mtext[MAX_SIZE];    // 消息数据
};


int main( int argc, char *argv[] )
{

    if( argc != 2 )
    {
        fprintf(stderr, "Usage: %s <string>\n", argv[0] );
        return -1;
    }
    //  step 1 : ftok 生成一个key
    key_t key;  // key_t 是定义在 sys/types.h 中的一个长整型。
   
    key = ftok(PATH_NAME, PRO_ID);   
    if( key == -1 ) 
    {
        perror("ftok");
        return -1;
    
    }

    printf("key = %d\n", key);
    // step2 : msgget 创建一个消息队列ID
    int msgid;
    msgid = msgget( key, IPC_CREAT | 0666 );
    if( msgid == -1 )
    {
        if( errno == EEXIST )
        {
            perror("msgget");
            return -1;
        }
    }

    // step3 : 服务器端 发送消息

    struct msgbuf *mbuf = (struct msgbuf *)malloc(sizeof(struct msgbuf));
    mbuf->mtype = 5;

    strcpy(mbuf->mtext, argv[1]);
    int len = strlen(mbuf->mtext);
    
    int ret = msgsnd(msgid, mbuf, len, IPC_NOWAIT); // 要有写权限
    if( ret == -1 )
    {
        perror("msgsnd");
        return -1;
    }
   
    printf("msgsnd has send data : %ld, %s\n", mbuf->mtype, mbuf->mtext);
    return 0;

}