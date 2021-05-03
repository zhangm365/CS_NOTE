


#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    struct in_addr addr;

    if (argc != 2) {
        fprintf(stderr, "%s <dotted-address>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(inet_aton(argv[1], &addr) == 0)
    {
        fprintf(stderr, "Invalid address\n");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", inet_ntoa(addr));


    /*
        // inet_addr: 对于有效地址255.255.255.255返回-1，所以是有问题的。
        
    addr.s_addr = inet_addr(argv[1]);
    if (addr.s_addr == -1) {
        fprintf(stderr, "Invalid address\n");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", inet_ntoa(addr));
    */



    exit(EXIT_SUCCESS);
}