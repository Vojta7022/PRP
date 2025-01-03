#include <stdio.h>

int factorialI(int n) 
{
   int f = 1;
   for (; n > 1; --n) {
      f *= n;
   }
   return f;
}

int factorialR(int n) 
{
   int f = 1;
   if (n > 1) {
      f = n * factorialR(n - 1);
   }
   return f;
}

int main(void)
{
   int n = 11;
   int fI = factorialI(n);
   int fR = factorialR(n);
   printf("Factorial by iteration: %u! = %u\n", n, fI);
   printf("Factorial by recursion: %u! = %u\n", n, fR);
}
