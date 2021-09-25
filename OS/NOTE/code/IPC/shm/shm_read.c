

#include "shm_com.h"

int main( int argc, char *argv[] )
{

    int shmid, semid;

    key_t key = ftok(PATH_NAME, PRO_KEY);

    // 创建一个信号量集合：集合中只有一个信号量，信号量的编号从 0 开始
    semid = semget( key, 1, IPC_CREAT | 0644 );
    if( semid == -1 )
    {
        errExit("semget");
    }

    // 共享内存段
    shmid = shmget( IPC_PRIVATE, MEM_SIZE, IPC_CREAT | 0644 );
    if( shmid == -1 )
    {
        errExit("shmget");
        
    }
    
    char *addr = shmat( shmid, 0, SHM_RDONLY );

    if( addr == (void *)-1 )
    {
        errExit("shmat");
    } 

    // 初始化信号量集合中的信号量
    union semun sem_arg, dummy;

    sem_arg.val = 1;    // 信号量的值为 1

    if ( semctl( semid, 0, SETVAL, sem_arg ) == -1 )
    {
        errExit("semctl");
    }

    printf( "shmid = %d, semid = %d\n", shmid, semid );


    /* wait for the semaphore value to become 0 */

    struct sembuf sbuf;
    
    sbuf.sem_num = 0;
    sbuf.sem_op = 0;
    sbuf.sem_flg = SEM_UNDO;

    if ( semop(semid, &sbuf, 1) == -1 )
    {
        errExit("semop");
    }

    printf("read data : %s from semid : %d\n", addr, shmid);


    if( semctl(semid, 0, IPC_RMID, sem_arg) == -1 )
    {
        errExit("semctl");
    }

    if( shmctl(shmid, IPC_RMID, NULL) == -1 )
    {
        errExit("shmctl");
    }

    return 0;

}