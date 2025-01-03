#include <stdio.h>

int main(void)
{
   int i = 10;
   while (i > 0) {
      if (i == 5) {
         printf("i reaches 5, leave the loop\n");
         break;
      }
      i--;
      printf("End of the while loop i: %d\n", i);
   }
   return 0;
}
