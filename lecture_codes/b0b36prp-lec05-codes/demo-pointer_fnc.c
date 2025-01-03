#include <stdio.h>
#include <stdlib.h>

void print(int n, int array[n]);
int compare(const void *pa, const void *pb);

int main(void)
{
   const int n = 10;
   int array[n];
   for (int i = 0; i < n; ++i) {
      array[i] = rand() % 100;
   }
   print(n, array);
   qsort(array, n, sizeof(array[0]), compare);
   print(n, array);
   return 0;
}

void print(int n, int array[n])
{
   for(int i = 0; i < n; ++i) {
      i > 0 ? printf(", ") : 0;
      printf("%d", array[i]);
   }
   n > 0 ? putchar('\n') : 0;
}

int compare(const void *pa, const void *pb)
{
   const int a = *(int*)pa;
   const int b = *(int*)pb;
   return (a < b) - (a > b);
   //return (*(int*)pa < *(int*)pb) - (*(int*)pa > *(int*)pb);
}
