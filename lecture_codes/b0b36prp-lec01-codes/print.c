#include <stdio.h>
#include <stdlib.h>

int main(void)
{
   int ret = EXIT_SUCCESS;
   int n;
   printf("Enter a positive integer number from 1 to 9: ");
   int r = scanf("%d", &n);
   if (r == 1 && n > 0 && n < 10) {
      int i = 0;
      while (i < n) {
         puts("I like B0B36PRP!");
         i = i + 1;
      }
   } else {
      printf("ERROR: Input value must be in the range (0,10)\n");
      ret = EXIT_FAILURE;
   }
   return ret;
}