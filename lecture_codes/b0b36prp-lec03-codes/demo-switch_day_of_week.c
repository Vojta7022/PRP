#include <stdio.h>

int main(void) 
{
   int day_of_week = 3;
   switch (day_of_week) {
      case 1:
         printf("Monday");
         break;
      case 2:
         printf("Tuesday");
         break;
      case 3:
         printf("Wednesday");
         break;
      case 4:
         printf("Thursday");
         break;
      case 5:
         printf("Friday");
         break;
      case 6:
         printf("Saturday");
         break;
      case 7:
         printf("Sunday");
         break;
      default:
         fprintf(stderr, "Invalid week\n");
         break;
   }
   printf("\n");
   return 0;
}
