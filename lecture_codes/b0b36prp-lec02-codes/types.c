#include <stdio.h>

int main() 
{
   int i;
   char c;
   short s;

   printf("i -   int size: %lu\n", sizeof(i));
   printf("int - int size: %lu\n", sizeof(int));
   printf("c -  char size: %lu\n", sizeof(c));
   printf("s - short size: %lu\n", sizeof(s));

   return 0;
}
