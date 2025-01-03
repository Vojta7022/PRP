#include <stdio.h>

int main(void)
{
   double a = 1e+10;
   double b = 1e-10;

   printf("a  : %24.12lf\n", a);
   printf("b  : %24.12lf\n", b);
   printf("a+b: %24.12lf\n", a + b);

   return 0;
}
