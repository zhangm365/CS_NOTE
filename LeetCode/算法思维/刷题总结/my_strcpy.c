

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//
char* my_strcpy(char* dst, const char* src) {

    if(!src || !dst) return NULL;

    char* ret = dst;

    // 记录长度，判断内存重叠
    int n = 0;
    const char* p = src;
    while(*p != '\0') {
        n++;
        p++;
    }
    
    // 内存重叠, 
    if( src < dst && dst < src + n) {
        
        int cnt = n - (dst - src);

        dst = dst + cnt - 1;  // dst 指向自己末尾
        src = src + cnt - 1;    // src 
        
        while(cnt--) {
            *dst = *src;
            dst--;
            src--;
        }
    } else {

        while(*src != '\0' && *dst != '\0') {
            *dst = *src;
            src++;
            dst++;
        }
        if(*dst != '\0') {    // len(dst) < len(src)
            *dst = '\0';
        }
    }
    
    return ret;
}



int main(void) {
    char a[] = "abddac";
    char b[] = "bassdbdsg";
    int n = 6;
    
    printf("%s\n", my_strcpy(a+3, a+1));
    return 0;
}
