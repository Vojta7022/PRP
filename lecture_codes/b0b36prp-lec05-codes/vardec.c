#include <stdio.h>

#include "vardec.h"

static int module_variable; 
int global_variable;

void function(int p);
int main(int argc, char *argv[])
{
   int local; /* local variable */

   function(1);
   function(1);
   function(1);
   return 0;
}

void function(int p) 
{
   int i = 0; /* local variable */
   static int si = 0; /* local static variable */

   i += 1;
   si += 1;
   fprintf(stdout, "function: p %d, local variable %d, static local variable %d\n", p, i, si);
}


