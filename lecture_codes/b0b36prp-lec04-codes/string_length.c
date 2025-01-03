#include <stdio.h>
#include <string.h>

int getLength(char *str);
int getLengthPtr1(char *str);
int getLengthPtr2(char *str);

int main(int argc, char *argv[]) 
{
   for (int i = 0; i < argc; ++i) {
      printf("argv[%i]: getLength = %i -- strlen = %lu\n", i, getLength(argv[i]), strlen(argv[i]));
   }

   printf("\nString length using pointer arithmetic\n");
   for (int i = 0; i < argc; ++i) {
      printf("argv[%i]: getLength = %i -- strlen = %lu\n", i, getLengthPtr1(argv[i]), strlen(argv[i]));
   }

   printf("\nString length using pointer arithmetic (short version) getLengthPtr2\n");
   for (int i = 0; i < argc; ++i) {
      printf("argv[%i]: getLength = %i -- strlen = %lu\n", i, getLengthPtr2(argv[i]), strlen(argv[i]));
   }
   return 0;
}

int getLength(char *str)
{
   int ret = 0;
   while (str && str[ret] != '\0') {
      ret += 1;
   }
   return ret;
}

int getLengthPtr1(char *str)
{
   int ret = 0;
   while (str && (*str++) != '\0') {
      ret += 1;
   }
   return ret;
}

int getLengthPtr2(char *str)
{
   int ret = 0;
   while (str && (*str++)) ret += 1;
   return ret;
}

