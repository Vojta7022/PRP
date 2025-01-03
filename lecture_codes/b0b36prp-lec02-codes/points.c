#include <stdio.h>

int main(void)
{
   int x1 = 1;
   double y1 = 2.2357;
   float x2 = 2.5343f;
   double y2 = 2;

   printf("P1 = (%i, %f)\n", x1, y1);
   printf("P1 = (%i, %i)\n", x1, (int)y1);
   printf("P1 = (%f, %f)\n", (double)x1, (double)y1);
   printf("P1 = (%.3f, %.3f)\n", (double)x1, (double)y1);

   printf("P2 = (%f, %f)\n", x2, y2);

   double dx = (x1 - x2); // implicitni konverze na float, resp. double
   double dy = (y1 - y2);

   printf("(P1 - P2)=(%.3f, %0.3f)\n", dx, dy); 
   printf("|P1 - P2|^2=%.2f\n", dx * dx + dy * dy); 
   return 0;
}
