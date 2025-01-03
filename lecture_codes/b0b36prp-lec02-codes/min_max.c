#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void min_max(int v, int *min, int *max);

int main(void)
{
   int ret = EXIT_SUCCESS;
   int min = INT_MAX;
   int max = INT_MIN;
   int c = 0;
   int v;

   while (scanf("%i", &v) == 1) {
      min_max(v, &min, &max);
      c = c + 1;
   }
   if (c > 0) {
      printf("Read %d numbers, min: %d, max: %d\n", c, min, max);
   } else {
      fprintf(stderr, "ERROR: No input given!\n");
      ret = EXIT_FAILURE;
   }
   return ret;
}

void min_max(int v, int *min, int *max)
{
   if (v < *min) *min = v;
   if (v > *max) *max = v; 
}
