#include <stdio.h>
#include <stdlib.h>

/* The main program */
int main(int argc, char *argv[])
{
  if (argc == 2)
  {
    int count = atoi(argv[1]);
    print_hello_times(count);
  }
  
  return 0;
}

void print_hello_times(int count){
    if (count)
    {
        printf("Hello\n");
        print_hello_times(count - 1);
    }
}
