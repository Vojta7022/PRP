#include <stdio.h>
#include <stdlib.h>

#define ERROR_INPUT 100
#define ERROR_RANGE 101

// gcc -DMAX_VALUE=15 -Wall main.c -o main
#define MIN_VALUE 1
#ifndef MAX_VALUE
#define MAX_VALUE 10
#endif

#ifndef PRINT_CHAR
#define PRINT_CHAR '*'
#endif

// ./main < in.txt > out.std 2> out.err

/**
 * Reads a size of the triangle from stdin.
 * @var n - Reference to where the size of the triangle is stored.
 * @return If success - EXIT_SUCCESS, otherwise ERROR_INPUT or ERROR_RANGE.
 */
int read_input(int *n)
{
    printf("Enter the size of the triangle between %d and %d: ", MIN_VALUE, MAX_VALUE);
    int ret = scanf("%d", n);
    if (ret != 1)
    {
        return ERROR_INPUT;
    }
    if (!(*n >= MIN_VALUE && *n <= MAX_VALUE))
    {
        return ERROR_RANGE;
    }

    return EXIT_SUCCESS;
}

/**
 * Prints error message to stderr.
 * @var ret - Type of the error message.
 * @var n - Sze of the triangle.
 */
void print_error(int ret, int n)
{
    /*if (ret == ERROR_INPUT)
    {
        fprintf(stderr, 
                "ERROR: Cannot read integer value from the standard input\n");
    } else if (ret == ERROR_RANGE)
    {
        fprintf(stderr, 
                "ERROR: Given value %d is not within the range [%d, %d]\n", 
                n, 
                MIN_VALUE, 
                MAX_VALUE);
    } else {
        // unknown error
    }*/

    switch(ret)
    {
        case ERROR_INPUT: fprintf(stderr, 
                "ERROR: Cannot read integer value from the standard input\n");
            break;
        case ERROR_RANGE: fprintf(stderr, 
                "ERROR: Given value %d is not within the range [%d, %d]\n", 
                n, 
                MIN_VALUE, 
                MAX_VALUE);
            break;
        default: fprintf(stderr, "Unknown error %d\n", ret);
    }
}

/**
 * Prints triangle line of characters c to stdout.
 * @var c - Character of the triangle.
 * @var length - of the line
 */
void print_triangle_line(char c, int length)
{
    for (int j = 0; j < length; j++)
    {
        putchar(c);
    }
}

/**
 * Prints triangle of characters c to stdout.
 * @var c - Character of the triangle.
 * @var size_of_triangle
 */
void print_triangle(char c, int size_of_triangle)
{
    for (int i = 0; i < size_of_triangle; i++)
    {
        print_triangle_line(c, size_of_triangle - i);
        putchar('\n');
    }
}

int main(int argc, char* argv[])
{
    int n; // size of triangle
    int ret = read_input(&n);
    if (ret != EXIT_SUCCESS) // !EXIT_SUCCESS
    {
        print_error(ret, n);
        return ret;
    }
    print_triangle(PRINT_CHAR, n);

    return EXIT_SUCCESS;
}