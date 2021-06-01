



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

    
    //  step 1 : ftok 生成一个key
    key_t key;  // key_t 是定义在 sys/types.h 中的一个长整型。
    
    key = ftok(PATH_NAME, PRO_ID);   
    if( key == -1 ) 
    {
        perror("ftok");
        return -1;
    
    }

    printf("key = %d\n", key);

    // step2 : msgget 打开一个现有消息队列ID
    int msgid;
    msgid = msgget( key, IPC_CREAT | 0666 );   // 客户端引用一个现有消息队列
    if( msgid == -1 )
    {
        if( errno == EEXIST )
        {
            perror("msgget");
            return -1;
        }
    }

    // step3 : 客户端 接收消息

    struct msgbuf *mbuf = (struct msgbuf *)malloc(sizeof(struct msgbuf));
    
    int ret = msgrcv(msgid, mbuf, MAX_SIZE, 0, MSG_NOERROR | IPC_NOWAIT ); // 要有读权限
    if( ret == -1 )
    {
        perror("msgsnd");
        return -1;
    }
   
    if( ret > 0 )
    {
        printf("type: %ld, text: %s\n", mbuf->mtype, mbuf->mtext);
    }
    return 0;

}