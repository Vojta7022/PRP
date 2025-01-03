#include <stdio.h>

#include "extern_var.h"

static int module_variable; 

void function(int p) 
{
   fprintf(stdout, "function: p %d global variable %d\n", p, global_variable);
}
