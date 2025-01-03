#include <stdio.h>

int main(void)
{
   double values[] = { 1000, 1e5, 1e20, 1e30 };

   for (int v = 0; v < sizeof(values)/sizeof(double); ++v) {
      printf("\nShow representations of the double values[%i] %lf and its conversion to short and int\n", v, values[v]);
      double d = values[v];
      short sd = (short)d;
      int id = (int)d;

      printf("double: %lf\n", d);
      printf(" short: %u\n", sd);
      printf("   int: %u\n", id);

      char *p = (char*)&d;
      printf("double (hex): ");
      for (int i = 0; i < sizeof(double); ++i) {
         printf(" %02x", *(p++) & 0xff); // for varargs, arguments smaller than int are promoted to int
      }
      printf("\n");

      p = (char*)&sd;
      printf("short (hex): ");
      for (int i = 0; i < sizeof(short); ++i) {
         printf(" %02x", *(p++) & 0xff); // for varargs, arguments smaller than int are promoted to int
      }
      printf("\n");

      p = (char*)&id;
      printf("int (hex): ");
      for (int i = 0; i < sizeof(int); ++i) {
         printf(" %02x", *(p++) & 0xff); // for varargs, arguments smaller than int are promoted to int
      }
      printf("\n");
   }
   return 0;
}
