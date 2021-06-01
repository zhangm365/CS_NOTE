


#include "sem_com.h"
#include <sys/wait.h>
#include <sys/stat.h>   


#define PATH_NAME "/home/zhangmao"
#define Key_Port 1234


static void
usage(const char *pname)
{
    // fprintf(stderr, "Usage: %s [-cx] pathname proj-id num-sems\n",
    //         pname);
    // fprintf(stderr, "    -c           Use IPC_CREAT flag\n");
    // fprintf(stderr, "    -x           Use IPC_EXCL flag\n");
    fprintf(stderr, "Usage : %s num-sems\n", pname);
    
    exit(EXIT_FAILURE);

}

int
main(int argc, char *argv[])
{
    int semid, nsems;
    
    key_t key;
    // int flags, opt;
    // flags = 0;
    // while ((opt = getopt(argc, argv, "cx")) != -1) {
    //     switch (opt) {
    //         case 'c': flags |= IPC_CREAT;   break;
    //         case 'x': flags |= IPC_EXCL;    break;
    //         default:  usage(argv[0]);
    //     }
    // }

    // printf("optind = %d\n", optind);
    if (argc != optind + 1)
        usage(argv[0]);

    key = ftok(PATH_NAME, Key_Port);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    nsems = atoi(argv[optind]);
    
    semid = semget(key, nsems, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // printf("ID = %d\n", semid);
    

    // step 2:
    

    //union semun sem_union;
    // sem_union.array = (unsigned short *) malloc( nsems * sizeof(unsigned short));
    // for( int i = 0; i < nsems; ++i )
    // {
    //     sem_union.array[i] = 1;
    // }
    // sem_union.val = 1;  // 指定信号量的值，即有一个共享资源
    // int ret;
    // ret = semctl( semid, 0, SETVAL, sem_union); // 当前集合中只有一个信号量，它的编号为0，值被初始化为 1。
    
    int ret;
    ret = init_sem( semid, 0 );
    if( ret == -1 )
    {
        perror("init_sem");
        exit(EXIT_FAILURE);
    } 
    
    // ret = semctl( semid, 0, GETVAL, sem_union);
    
    
    pid_t pid = fork();

    if( pid < 0 )
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if( pid == 0 ) // child
    {
        //while(1)
        //{
            sem_p( semid, 0 );
            printf("child waiting\n");
            sleep(5);
            printf("child finish\n");
            sem_v( semid, 0 );

        //}
        
    }
    else    // pid > 0 : parent
    {
        
        //while(1)
        //{
            sem_p( semid, 0 );
            printf("father waiting\n");
            sleep(8);
            printf("father finish\n");
            sem_v( semid, 0 );
            wait(NULL);
        //}

    }

    exit(EXIT_SUCCESS);

}