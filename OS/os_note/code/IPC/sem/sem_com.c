


#include "sem_com.h"


int init_sem( int semid, int semnum )
{

    union semun sem_union;
    
    sem_union.val = 1;
    
    
    if( semctl( semid, semnum, SETVAL, sem_union ) == -1 )
    {
        perror("semctl");
        return -1;
    }
    
    return 0;
    
}

int sem_p( int semid, int semnum )
{
    struct sembuf pbuf;
    pbuf.sem_num = semnum;
    pbuf.sem_op = -1;
    pbuf.sem_flg = SEM_UNDO;
    if( semop(semid, &pbuf, 1) == -1 )
    {
        perror("p_semop");
        return -1;
    }

    return 0;

}

int sem_v( int semid, int semnum )
{
    struct sembuf vbuf;
    vbuf.sem_num = semnum;
    vbuf.sem_op = 1;
    vbuf.sem_flg = SEM_UNDO;

    if( semop( semid, &vbuf, 1 ) == -1 )
    {
        perror( "v_semop");
        return -1;
    }

    return 0;

}