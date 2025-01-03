#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS

int main(void)
{
   int ret = EXIT_SUCCESS;
   double d;

   printf("Enter a double value: ");
   int r = scanf("%lf", &d);
   if (r == 1) {
      printf("You entered %0.1f\n", d);
   } else if (r == 0) {
      fprintf(stderr, "ERROR: Input does not match double value!\n");
      ret = 101;
   } else {
      fprintf(stderr, "WARN: No input provided!\n"); //press Ctrl+D to terminate the input EOT - End of transmission
      ret = 102;
   }
   return ret;
}
