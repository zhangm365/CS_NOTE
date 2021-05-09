

#include <sys/select.h>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

typedef long int __fd_mask;

#define __NFDBITS	(8 * (int) sizeof (__fd_mask))

int main(void)
{
    fd_set set;

    FD_ZERO(&set);
    printf("%d\n", __NFDBITS);  // 64
    printf("long int = %ld Bytes, fd_set = %ld\n", sizeof(long int), sizeof(set) / sizeof(set.__fds_bits[0]));  //8 16
    int i;
    for(i = 0;i < 16;i++)
    {
        
        printf("set.__fds_bits[%d]:%ld\n",i,set.__fds_bits[i]);
        
    }
    printf("\n------------------------\n");

    FD_ZERO(&set);
    FD_SET(64,&set);
    for(i = 0;i < 16;i++)
    {
        
        printf("set.__fds_bits[%d]:%ld\n",i,set.__fds_bits[i]);
    }
    
    printf("\n-------------------------\n");

    FD_ZERO(&set);
    FD_SET(1024,&set);
    for(i = 0;i < 16;i++)
    {
        
        printf("set.__fds_bits[%d]:%ld\n",i,set.__fds_bits[i]);
    }

    return 0;

}