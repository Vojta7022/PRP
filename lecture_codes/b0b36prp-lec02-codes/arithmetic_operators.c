#include <stdio.h>

int main(void)
{
   int a = 10;
   int b = 3;
   int c = 4;
   int d = 5;
   int result;

   result = a - b; // rozdil
   printf("a - b = %i\n", result);

   result = a * b; // nasobeni
   printf("a * b = %i\n", result);

   result = a / b; // celociselne deleni
   printf("a / b = %i\n", result);

   result = a + b * c; // priorita operatoru
   printf("a + b * c = %i\n", result);

   printf("a * b + c * d = %i\n", a * b + c * d);
   printf("(a * b) + (c * d) = %i\n", (a * b) + (c * d));
   printf("a * (b + c) * d = %i\n", a * (b + c) * d);

   return 0;
}
