#include <stdio.h>

union U
{
  int a;
  char b;


};



int main()
{
  
  union U u;
  u.a = 0x12345678;

  if( u.b == 0x78 )
    printf("%x, little endian\n", u.b);
  else
    printf("big endian\n");


  return 0;

}
