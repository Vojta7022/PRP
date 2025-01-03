#include <stdio.h>

#include "extern_var.h" 

int main(int argc, char *argv[])
{
   global_variable += 1;
   function(1);
   function(1);
   global_variable += 1;
   function(1);
   return 0;
}
