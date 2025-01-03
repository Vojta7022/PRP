#include <stdio.h>

int main(void)
{
   const int number = 100;
   double dV = 0.0;
   float fV = 0.0f;

   for (int i = 0; i < number; ++i) {
      dV += 1.0 / 10.0;
      fV += 1.0 / 10.0;
   }

   printf("double value: %lf ", dV);
   printf(" float value: %lf\n", fV);

   return 0;
}
