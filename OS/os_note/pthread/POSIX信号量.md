# 线程同步机制

1.  ## POSIX信号量

    ## 相关函数

    1.  NAME
               **sem_init** - initialize an unnamed semaphore

        SYNOPSIS
              
        
        >   ```cpp
        >   //Link with -pthread.
        >   #include <semaphore.h>
        >   int sem_init(sem_t *sem, int pshared, unsigned int value);
        >   
        >   /****** DESCRIPTION ************
        >   sem_init() initializes the unnamed semaphore at the address pointed to by sem.  The value argument specifies the initial value for the semaphore.
    >   The pshared argument indicates whether this semaphore is to be shared between the threads of a process, or between processes.
        >   *********/
        >   ```
    >
    

    
2.  NAME
    
    ​	  **sem_wait, sem_timedwait, sem_trywait** - lock a semaphore
    
    SYNOPSIS
    
    >   ```cpp
        >   int sem_wait(sem_t *sem);
        >   int sem_trywait(sem_t *sem);
        >   int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
        >   
        >   /******** DESCRIPTION ***************
    >   
    >   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):	
    >   sem_timedwait(): _POSIX_C_SOURCE >= 200112L
    >   
    >   sem_wait() decrements (locks) the semaphore pointed to by **sem**.  If the semaphore's value is greater than zero, then the decrement proceeds, and the function returns, immediately.  If the semaphore currently has the value zero, then the call blocks until either it becomes possible to perform the decrement (i.e., the  semaphore  value  rises above zero), or a signal handler interrupts the call.
    >   
        >   sem_trywait()  is  the same as sem_wait(), except that if the decrement cannot be immediately performed, then call returns an error (errno set to EAGAIN) 	instead of blocking.
    >   	
    >   ***********/
        >   ```
        >
        
        ​	
        