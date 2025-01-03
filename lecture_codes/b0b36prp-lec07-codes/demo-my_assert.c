#include <stdlib.h>

#include "my_assert.h"

#ifndef SIZE
#define SIZE 104857600
#endif

int main(int argc, char *argv[])
{
   int ret = EXIT_SUCCESS;
   int *a = malloc(SIZE * sizeof(*a));

   my_assert(a, __LINE__, __FILE__);

   free(a);

   return ret;
}
