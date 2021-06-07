

#ifndef _SEM_COM_H_
#define _SEM_COM_H_

#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include <stdio.h>     
#include <stdlib.h>     
#include <unistd.h>  

union semun
{
    int val;    // semval
    struct semid_ds *buf;
    unsigned short *array;

};



int init_sem( int semid, int semnum );

int sem_p( int semid, int semnum );
int sem_v( int semid, int semnum );


#endif