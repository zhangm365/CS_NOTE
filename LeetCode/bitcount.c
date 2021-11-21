
#include <stdio.h>

int main()
{

    int i = 0x3a70f21b;
    printf("0x%x\n", i);
     
    i = (i & 0x55555555) + ((i >> 1) & 0x55555555);  
    printf("0x%x\n", i);
    // 步骤2     
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);    
    printf("0x%x\n", i);
    // 步骤3     
    i = (i & 0x0F0F0F0F) + ((i >> 4) & 0x0F0F0F0F);    
    printf("0x%x\n", i);
    // 步骤4     
    i = (i*(0x01010101) >> 24);
    printf("0x%x, %d\n", i, i);
    return 0;

}