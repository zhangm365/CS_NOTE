

#include "shm_com.h"

int main( int argc, char *argv[] )
{

    int shmid, semid;

    key_t key = ftok(PATH_NAME, PRO_KEY);


    semid = semget( key, 1, IPC_CREAT | 0644 );
    if( semid == -1 )
    {
        errExit("semget");
    }

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

    union semun sem_arg, dummy;

    sem_arg.val = 1;

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


    if( semctl(semid, 0, IPC_RMID, dummy) == -1 )
    {
        errExit("semctl");
    }

    if( shmctl(shmid, IPC_RMID, NULL) == -1 )
    {
        errExit("shmctl");
    }

    return 0;

}