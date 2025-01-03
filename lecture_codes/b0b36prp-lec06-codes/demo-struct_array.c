#include <stdio.h>

void print(const char *str, int n, int *a);

#define N 10 // Define N as symbolic constant for literal 10.

int main(void)
{
   const int n = N;

   struct { // Anonymous struct
      int a[N]; // We cannot use VLA here, therefore, n would not work and N (as literal) is required. 
   } s1, s2; // Two variables of the struct type

   printf("s1 %p; s2 %p\n", &s1, &s2);
   for (int i = 0; i < n; ++i) {
      s1.a[i] = i;
   }
   print("s1.a", n, s1.a);
   s2 = s1; // Assignment 
   print("s2.a", n, s2.a);
   for (int i = 0; i < n; ++i) {
      s1.a[i] = n - i;
   }
   print("s1.a", n, s1.a);
   print("s2.a", n, s2.a);
   return 0;
}

void print(const char *str, int n, int *a) {
   printf("%s %p: ", str, a);
   for (int i = 0; i < n; ++i) {
      printf("%d%s", a[i], i < (n-1) ? ", " : "\n");
   }
}
