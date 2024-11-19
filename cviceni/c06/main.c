#include <stdio.h>
#include <stdlib.h> // malloc, calloc, realloc, free, EXIT_SUCCESS,...

#define INIT_SIZE 5
#define ERROR_READ 100

typedef struct lines {
    char **lines;
    int no_lines;
} lines;

/**
 * Reads file from fd
 * @param fd
 * @param no_lines
 * @return Pointer to array of strings (char*)
 */
char **read_file(FILE *fd, int *no_lines);
/**
 * Reads one line (ends '\n')
 * @param fd
 * @return Pointer to array of chars (string)
 */
char *read_line(FILE *fd);
/**
 * Prints lines to stdout in reverse order
 * @param lines
 * @param no_lines
 */
void print_reverse(char **lines, int no_lines);
void print_reverse_s(lines lines);

void free_lines(char **lines, int i)
{
    for (int j = 0; j < i; j++)
    {
        free(lines[j]);
    }
    free(lines);
    lines = NULL;
}
int main(int argc, char **argv)
{
    int ret = EXIT_SUCCESS;
    // FILE *fd = fopen(filaname, flags); fclose(fd);
    FILE *fd = stdin;
    int no_lines = 0;
    // char *line = read_line(fd);
    // if (!line)
    // { // line == NULL
    //     fprintf(stderr, "Chyba nacitani\n");
    //     ret = ERROR_READ;
    // }
    // else
    // {
    //     printf("DEBUG: '%s'\n", line);
    // }
    // //
    // if (line)
    // {
    //     // free(line);
    //     line = NULL;
    // }
    char **lines = read_file(fd, &no_lines);
    if (!lines)
    {
        fprintf(stderr, "Chyba nacitani\n");
        ret = ERROR_READ;
    }
    else
    {
        print_reverse(lines, no_lines);
    }
    if (lines)
    {
        free_lines(lines, no_lines);
    }
    return ret;
}
void print_reverse(char **lines, int no_lines)
{
    for (int i = no_lines - 1; i >= 0; i--)
    {
        printf("'%s'\n", lines[i]);
    }
}

void print_reverse_s(lines lines)
{
    for (int i = lines.no_lines - 1; i >= 0; i--)
    {
        printf("'%s'\n", lines.lines[i]);
    }
}

char **read_file(FILE *fd, int *no_lines)
{
    int size = INIT_SIZE;
    char **lines = (char **)malloc(sizeof(char *) * size);
    if (!lines)
    {
        *no_lines = 0;
        return NULL;
    }
    //
    int i = 0;                                          // *no_lines = 0 da se misto i
    while (lines && (lines[i] = read_line(fd)) != NULL) // lines[*no_lines] = read...
    {
        if (i == size)
        {
            size *= 2;
            char **tmp = (char **)realloc(lines, sizeof(char *) * size);
            if (!tmp)
            { // tmp == NULL
                free_lines(lines, i);
                i = 0;
                break;
            }
            lines = tmp;
        }
        i++; // (*no_lines)++;
    }
    *no_lines = i;
    return lines;
}
char *read_line(FILE *fd)
{
    // string "abc" = ['a', 'b', 'c', '\0']
    int size = INIT_SIZE;
    char *line = (char *)malloc(sizeof(char) * (size + 1));
    if (!line) // line == NULL
    {
        return NULL;
    }
    //
    int ch = '\0';
    int i = 0;
    while (line && (ch = getc(fd)) != EOF)
    {
        // if (line == NULL) break;
        // ch = getc(fd);
        // if (ch == EOF) break;
        if (i == size)
        {
            size *= 2;
            char *tmp = (char *)realloc(line, sizeof(char) * (size + 1));
            if (!tmp)
            { // tmp == NULL
                free(line);
                line = NULL;
                break;
            }
            line = tmp;
        }
        if (ch == '\n')
        {
            break;
        }
        line[i++] = ch;
        // line[i] = ch; i += 1;
    }
    if (line && i > 0)
    {
        line[i] = '\0';
    }
    else if (line) // i == 0
    {
        free(line);
        line = NULL;
    }
    return line;
}
