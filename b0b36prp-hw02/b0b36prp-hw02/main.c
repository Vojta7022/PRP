#include <stdio.h>
#include <stdlib.h>

#define ERROR_INTERVAL 100
#define ERROR_INPUT 101

/* The main program */
int main(int argc, char *argv[])
{
  int input;
  int ret = scanf("%d", &input);
  int counter = 0;
  while (input != EOF)
  {
    if (ret != 1)
    {
      fprintf(stderr, "Invalid input\n");
      return ERROR_INPUT;
    }
    if (!(input >= -10000 && input <= 10000))
    {
      fprintf(stderr, "Invalid input\n");
      return ERROR_INTERVAL;
    }
    counter++;
    printf("%d%s}", input, counter == 0 ? "" : ",");
  }
  
  return 0;
}

