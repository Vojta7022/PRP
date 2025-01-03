#include <stdio.h>

void print_array(int n, int a[n])
{
   printf("Size of the array a is %lu\n", sizeof(a));
   for (int i = 0; i < n; ++i) {
      printf("array[%i]=%i\n", i, a[i]);
   }
}

int main(int argc, char *argv[])
{
   int n = 10;
   if (argc > 1 && sscanf(argv[1], "%d", &n) != 1) {
      fprintf(stderr, "Warning: cannot parse number from argv[1]; thus the default value %d is used.\n", n);
   }
   int array[n]; //vla array size depends on n
   printf("Size of the array is %lu\n", sizeof(array));
   for (int i = 0; i < n; ++i) {
      array[i] = 2*i;
   }
   print_array(n, array);
   return 0;
}
