#include <stdio.h>
#include <stdlib.h>

float* init_values(size_t n, float v);
float sum_naive(size_t n, float *v);
float sum_alter(size_t n, float *v, size_t power);

int main(void) 
{
   float v = 1e-20f; // small value to be sum
   const size_t power = 30; // try 3 vs. 30
   size_t n = 1l<<power ; // 1073741824 is 2^30 values, about 1e9
   const double k = 1e11; 

   float *values = init_values(n, v);

   double sum1 = v*n * k;
   double sum2 = sum_naive(n, values) * k;
   float sum3 = sum_alter(n, values, power) * k;

   printf("Sum of %lu numbers of the value %.22lf\n", n, v);
   printf("Sum1 (multiplication): %.22lf\n", sum1);
   printf("Sum2 (naive)         : %.22lf\n", sum2);
   printf("Sum3 (alter)         : %.22lf\n", sum3);
   free(values);
   return EXIT_SUCCESS;
}

float* init_values(size_t n, float v)
{
   float *r = malloc(n * sizeof(v));
   if (!r) {
      fprintf(stderr, "ERROR: MEM_ALLOC\n");
      exit(-1);
   }
   for (size_t i = 0; i < n; ++i) {
      r[i] = v;
   }
   return r;
}

float sum_naive(size_t n, float *v)
{
   float r = 0;
   for (size_t i = 0; i < n; ++i) {
      r += v[i];
   }
   return r;
}

float sum_alter(size_t n, float *v, size_t power)
{
   float r = 0;
   const size_t order = power - 1;
   size_t k = 2;
   for (size_t l = 1; l < order; ++l, k *= 2) {
      for (size_t i = 0; i < n; i += k) {
         v[i] = v[i] + v[i+k/2];
      }
   }
   k /= 2;
   for (size_t i = 0; i < n; i += k) {
      r += v[i];
   }
   return r;
}

