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
long fibonnaciIterative(int n) 
{
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
   int n = argc > 1 ? atoi(argv[1]) : 25;
   counter = 0; // reset counter
   long fibR = fibonnaciRecursive(n);
   long counterR = counter;

   counter = 0; // reset counter 
   long fibI = fibonnaciIterative(n);
   long counterI = counter;

   printf("Fibonacci number recursive: %li\n", fibR);
   printf("Fibonacci number iteration: %li\n", fibI);
   printf("Counter recursive: %li\n", counterR);
   printf("Counter iteration: %li\n", counterI);

   return 0;
}
