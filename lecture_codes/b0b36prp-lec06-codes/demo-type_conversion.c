#include <stdio.h>

int main(void)
{
   {
      double d = 1e30;
      int i = (int)d;

      printf("d = %lf\n", d);
      printf("i = %i\n", i);
   }

   {
      long l = 5000000000L;
      int i = (int)l;

      printf("l = %li\n", l);
      printf("i = %i\n", i);
   }

   return 0;
}
