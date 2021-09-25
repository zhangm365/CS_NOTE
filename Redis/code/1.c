
#include <stdio.h>
int main() 
{

    struct s1{
        char a;
        int b;
    }ts1;

    printf("%lu\n", sizeof(ts1));   // 8 : 采用了内存对齐的分配方式

    struct __attribute__ ((__packed__)) s2{
        char a;
        int b;
    }ts2;

    printf("%lu\n", sizeof(ts2));   // 5: 紧凑型内存分配方式
  
    struct __attribute__ ((__packed__)) sdshdr32 {
        unsigned int len; /* used */
        unsigned int alloc; /* excluding the header and null terminator */
        unsigned char flags; /* 3 lsb of type, 5 unused bits */
        char buf[];
    };

    printf("%lu\n", sizeof(struct sdshdr32));   // 9, 最后的buf不分配空间
    
    return 0;


}