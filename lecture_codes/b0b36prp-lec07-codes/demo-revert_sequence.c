#include <stdio.h>

void reverse(void);

int main(void)
{
   fprintf(stderr, "Enter a sequence of numbers (use Ctrl+D for the end of the the sequence)\n");
   reverse();
   printf("\n");
   return 0;
}

void reverse(void)
{
   int v;
   if (scanf("%i", &v) == 1) {
      reverse();
      printf("%3d ", v);
   }
}
