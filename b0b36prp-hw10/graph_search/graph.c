#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "my_malloc.h"
#include "graph_utils.h"

void write_int(FILE *f, int value);
int convert_to_host_order(int num);

graph_t *allocate_graph()
{
    graph_t *graph = myMalloc(sizeof(graph_t));
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

    int from = 0, to = 0, cost = 0;
    int sign = 1, c;

    while ((c = getc(f)) != EOF)
    {
        from = to = cost = 0; // Reset values for each edge
        sign = 1;

        // Read 'from' integer
        while (c != ' ' && c != EOF)
        {
            if (c == '-')
            {
                sign = -1;
            }
            else
            {
                from = from * 10 + (c - '0');
            }
            c = getc(f);
        }
        from *= sign;

        // Read 'to' integer
        c = getc(f);
        sign = 1;
        while (c != ' ' && c != EOF)
        {
            if (c == '-')
            {
                sign = -1;
            }
            else
            {
                to = to * 10 + (c - '0');
            }
            c = getc(f);
        }
        to *= sign;

        // Read 'cost' integer
        c = getc(f);
        sign = 1;
        while (c != '\n' && c != EOF)
        {
            if (c == '-')
            {
                sign = -1;
            }
            else
            {
                cost = cost * 10 + (c - '0');
            }
            c = getc(f);
        }
        cost *= sign;

        // Ensure capacity and add the edge
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

void load_bin(const char *fname, graph_t *graph)
{
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
        from = convert_to_host_order(from);
        to = convert_to_host_order(to);
        cost = convert_to_host_order(cost);

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

void save_txt(const graph_t *const graph, const char *fname)
{
    FILE *f = fopen(fname, "w");
    if (!f)
    {
        fprintf(stderr, "Error: Cannot open file %s\n", fname);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->num_edges; i++)
    {
        write_int(f, graph->edges[i].from);
        putc(' ', f);
        write_int(f, graph->edges[i].to);
        putc(' ', f);
        write_int(f, graph->edges[i].cost);
        putc('\n', f);
    }

    fclose(f);
}

void save_bin(const graph_t *const graph, const char *fname)
{
    FILE *f = fopen(fname, "wb");
    if (!f)
    {
        fprintf(stderr, "Error: Cannot open file %s\n", fname);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->num_edges; i++)
    {
        int from = convert_to_host_order(graph->edges[i].from);
        int to = convert_to_host_order(graph->edges[i].to);
        int cost = convert_to_host_order(graph->edges[i].cost);

        fwrite(&from, sizeof(int), 1, f);
        fwrite(&to, sizeof(int), 1, f);
        fwrite(&cost, sizeof(int), 1, f);
    }
    fclose(f);
}

void write_int(FILE *f, int value)
{
    if (value < 0)
    {
        putc('-', f);
        value = -value;
    }

    char buffer[12];
    int i = 0;

    do
    {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    } while (value > 0);

    while (i > 0)
    {
        putc(buffer[--i], f);
    }
}

int convert_to_host_order(int num)
{
    return ((num & 0xFF000000) >> 24) |
           ((num & 0x00FF0000) >> 8) |
           ((num & 0x0000FF00) << 8) |
           ((num & 0x000000FF) << 24);
}
