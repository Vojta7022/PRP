#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "my_malloc.h"
#include "graph.h"

#ifndef INIT_SIZE
#define INIT_SIZE 10
#endif

graph_t *enlarge_graph(graph_t *g)
{
   assert(g != NULL);
   int n = g->capacity == 0 ? INIT_SIZE : g->capacity * 2; /* double the memory */

   edge_t *e = myMalloc(n * sizeof(edge_t));
   memcpy(e, g->edges, g->num_edges * sizeof(edge_t));
   free(g->edges);
   g->edges = e;
   g->capacity = n;
   return g;
}

void print_graph(graph_t *g)
{
   assert(g != NULL);
   fprintf(stderr, "Graph has %d edges and %d edges are allocated\n", g->num_edges, g->capacity);
   edge_t *e = g->edges;
   for (int i = 0; i < g->num_edges; ++i, ++e)
   {
      printf("%d %d %d\n", e->from, e->to, e->cost);
   }
}
