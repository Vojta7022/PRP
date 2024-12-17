#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

graph_t *allocate_graph()
{
    graph_t *graph = my_malloc(sizeof(graph_t));
    graph->edges = NULL;
    graph->num_edges = 0;
    graph->capacity = 0;
    return graph;
}

void free_graph(graph_t **graph)
{
    if ((*graph)->capacity > 0)
    {
        free((*graph)->edges);
    }
    free(*graph);
    *graph = NULL;
}

void load_txt(const char *fname, graph_t *graph)
{
    FILE *f = fopen(fname, "r");
    if (!f)
    {
        fprintf(stderr, "Error: Cannot open file %s\n", fname);
        exit(EXIT_FAILURE);
    }

    int from, to, cost;
    while (fscanf(f, "%d %d %d", &from, &to, &cost) == 3)
    {
        if (graph->num_edges >= graph->capacity)
        {
            graph = enlarge_graph(graph);
        }
        graph->edges[graph->num_edges].from = from;
        graph->edges[graph->num_edges].to = to;
        graph->edges[graph->num_edges].cost = cost;
        graph->num_edges++;
    }
    fclose(f);
}

void load_bin(const char *fname, graph_t *graph) {
    FILE *f = fopen(fname, "rb");
    if (!f)
    {
        fprintf(stderr, "Error: Cannot open file %s\n", fname);
        exit(EXIT_FAILURE);
    }

    int from, to, cost;
    while (fread(&from, sizeof(int), 1, f) == 1 &&
           fread(&to, sizeof(int), 1, f) == 1 &&
           fread(&cost, sizeof(int), 1, f) == 1)
    {
        if (graph->num_edges >= graph->capacity)
        {
            graph = enlarge_graph(graph);
        }
        graph->edges[graph->num_edges].from = from;
        graph->edges[graph->num_edges].to = to;
        graph->edges[graph->num_edges].cost = cost;
        graph->num_edges++;
    }
    fclose(f);
}

void save_txt(const graph_t * const graph, const char *fname) {
    FILE *f = fopen(fname, "w");
    if (!f)
    {
        fprintf(stderr, "Error: Cannot open file %s\n", fname);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->num_edges; i++)
    {
        fprintf(f, "%d %d %d\n", graph->edges[i].from, graph->edges[i].to, graph->edges[i].cost);
    }
    fclose(f);
}

void save_bin(const graph_t * const graph, const char *fname) {
    FILE *f = fopen(fname, "wb");
    if (!f)
    {
        fprintf(stderr, "Error: Cannot open file %s\n", fname);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->num_edges; i++)
    {
        fwrite(&graph->edges[i].from, sizeof(int), 1, f);
        fwrite(&graph->edges[i].to, sizeof(int), 1, f);
        fwrite(&graph->edges[i].cost, sizeof(int), 1, f);
    }
    fclose(f);
}

graph_t *enlarge_graph(graph_t *graph)
{
    int n = graph->capacity == 0 ? INIT_SIZE : graph->capacity * 2;

    /* double the memory */
    edge_t *e = my_malloc(n * sizeof(edge_t));
    memcpy(e, graph->edges, graph->num_edges * sizeof(edge_t));

    free(graph->edges);
    graph->edges = e; /* update edges */
    graph->capacity = n;
    return graph;
}

void *my_malloc(size_t size)
{
    void *ret = malloc(size);
    if (!ret)
    {
        fprintf(stderr, "Error: Cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }
    return ret;
}
