
#include "shm_com.h"


int main( int argc, char *argv[] )
{

    if( argc != 4 )
    {
        fprintf(stderr, "Usage: %s shmid semid string\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int shmid, semid;

    shmid = atoi(argv[optind]);
    semid = atoi(argv[optind+1]);
    
    char *addr;

    addr = shmat(shmid, NULL, 0);
    if ( addr == (void *)-1 )
    {
        errExit("shmat");
    }
    
    size_t len = strlen( argv[optind+2] ) + 1;  // include the '\0'
    memcpy(addr, argv[optind+2], len);

    struct sembuf sbuf;
    sbuf.sem_num = 0;
    sbuf.sem_op = -1;
    sbuf.sem_flg = SEM_UNDO;

    if( semop(semid, &sbuf, 1) == -1 )
    {
        errExit("semop");
    }

    

    return 0;

}