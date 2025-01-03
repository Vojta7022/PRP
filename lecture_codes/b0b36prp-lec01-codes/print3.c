#include <stdio.h>
#include <stdlib.h>

int read(int min, int max, int *n);
void print(int n);

#define MIN 1
#define MAX 9

int main(void)
{
   int ret = EXIT_SUCCESS;
   int n;
   if (read(MIN, MAX, &n)) {
      print(n);
   } else {
      printf("ERROR: Input value must be in the range (%d,%d)\n", MIN - 1, MAX + 1);
      ret = EXIT_FAILURE;
   }
   return ret;
}

int read(int min, int max, int *n)
{
   printf("Enter a positive integer number from %d to %d: ", min, max);
   return scanf("%d", n) == 1 && *n >= min && *n <= max;  // logical true is a value != 0
}

void print(int n)
{
   int i = 0;
   while (i < n) {
      puts("I like B0B36PRP!");
      i = i + 1;
   }
}
