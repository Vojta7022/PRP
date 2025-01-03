#include <stdio.h>

void swap0(int a, int b);
void swap(int *a, int *b);

int main(void)
{
   int v1 = 10;
   int v2 = 20;

   printf("v1: %i v2: %i\n", v1, v2);
   swap0(v1, v2);
   printf("v1: %i v2: %i\n", v1, v2);
   swap(&v1, &v2); //předání paměťového místa
   printf("v1: %i v2: %i\n", v1, v2);
   return 0;
}

void swap0(int a, int b)
{
   int t = a;
   a = b;
   b = t;
}

void swap(int *a, int *b)
{
   int t = *a;
   *a = *b;
   *b = t;
}
