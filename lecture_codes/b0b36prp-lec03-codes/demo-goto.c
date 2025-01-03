#include <stdio.h>

int main(void)
{
   for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
         printf("i-j: %i-%i\n", i, j);
         if (j == 1) {
            break;
         }
      }
   }
   printf("\nBreak outer loop\n");

   for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 3; ++j) {
         printf("i-j: %i-%i\n", i, j);
         if (j == 2) {
            goto outer;
         }
      }
   }
outer:

   return 0;
}
