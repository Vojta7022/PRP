#include <stdio.h>
#include <stdlib.h>

long counter; // store number of indiviual operations 

/// - function -----------------------------------------------------------------
long fibonnaciRecursive(int n) 
{
   counter += 1;
   return n < 2 ? 1l : fibonnaciRecursive(n - 1) + fibonnaciRecursive(n - 2);
}

/// - function -----------------------------------------------------------------
long fibonnaciIterative(int n) {
   long fibM2 = 1l;
   long fibM1 = 1l;
   long fib = 1l;
   for (int i = 2; i <= n; ++i) {
      fibM2 = fibM1;
      fibM1 = fib;
      fib = fibM1 + fibM2;
      counter += 3;
   }
   return fib;
}

/// - main ---------------------------------------------------------------------
int main(int argc, char *argv[])
{
   int m = argc > 1 ? atoi(argv[1]) : 45;
   for (int n = 0; n < m; ++n) {
      counter = 0;
      long fibR = fibonnaciRecursive(n);
      long counterR = counter;
      counter = 0; // reset counter

      counter = 0;
      long fibI = fibonnaciIterative(n);
      long counterI = counter;

      printf("%u\t%6.3e\t%6.3e\n", n, (double)counterR, (double)counterI);
   }
   return 0;
}
