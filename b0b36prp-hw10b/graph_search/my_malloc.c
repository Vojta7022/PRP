#include <stdio.h>
#include <stdlib.h>

#include "my_malloc.h"

void *myMalloc(size_t size)
{
   void *ret = malloc(size);
   if (!ret)
   {
      fprintf(stderr, "Malloc failed!\n");
      exit(-1);
   }
   return ret;
}

/**
ZIP_FILES =\
   modules.mk\
   dijkstra.c\
   dijkstra.h\
   graph_utils.c\
   graph_utils.h\
   load_simple.c\
   load_simple.h\
   my_malloc.c\
   my_malloc.h\
   graph.c\
   graph.h\
   pq_heap.c\
   pq_heap.h
*/
