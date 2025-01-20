#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_INPUT 100
#define MAX_SEQUENCE 52
#define MAX_ELEMENTS 200000
#define INIT_SIZE 10

#define PRIORITY_ADD 1
#define PRIORITY_SUB 1
#define PRIORITY_MUL 2

typedef struct matrix
{
  int rows;
  int cols;
  int *elems;
  size_t size;
} matrix_t;

typedef struct operation
{
  char sign;
  int priority;
} operation_t;

// Function prototypes
int read_matrix(matrix_t *matrix, char input[]);
int read_sign(char *sign);
void print_matrix(matrix_t matrix);
int matrices_are_compatible(matrix_t *matrix1, matrix_t *matrix2, char sign);
int compute_matrix(matrix_t *matrix1, char sign, matrix_t *matrix2);
void add_matrix(matrix_t *matrix1, matrix_t *matrix2);
void sub_matrix(matrix_t *matrix1, matrix_t *matrix2);
int mul_matrix(matrix_t *matrix1, matrix_t *matrix2);
void free_matrix(matrix_t *matrix);
int read_sequence(matrix_t matrices[], operation_t operations[], int *matrix_count, int *operation_count);
int compute_sequence(matrix_t matrices[], operation_t operations[], int *matrix_count, int *operation_count);
int copy_matrix(matrix_t *dest, const matrix_t *src);

int main(int argc, char *argv[])
{
  matrix_t matrices[MAX_SEQUENCE];

  for (size_t i = 0; i < MAX_SEQUENCE; i++)
  {
    matrices[i].rows = 0;
    matrices[i].cols = 0;
    matrices[i].elems = NULL;
    matrices[i].size = 0;
  }

  for (size_t i = 0; i < MAX_SEQUENCE; i++)
  {
    char input[MAX_ELEMENTS];

    if (fgets(input, MAX_ELEMENTS, stdin) == NULL)
    {
      return ERROR_INPUT;
    }

    if (input[0] == '\n')
    {
      break;
    }

    int index = input[0] - 'A';

    if (read_matrix(&matrices[index], input) == ERROR_INPUT)
    {
      fprintf(stderr, "Error: Chybny vstup!\n");
      for (size_t i = 0; i < MAX_SEQUENCE; i++)
      {
        free_matrix(&matrices[i]);
      }
      return ERROR_INPUT;
    }
  }

  char sequence[2048];
  if (fgets(sequence, 2048, stdin) == NULL)
  {
    return ERROR_INPUT;
  }

  matrix_t matrix_sequence[1000];

  for (size_t i = 0; i < 500; i++)
  {
    matrix_sequence[i].rows = 0;
    matrix_sequence[i].cols = 0;
    matrix_sequence[i].elems = NULL;
    matrix_sequence[i].size = 0;
  }

  operation_t operation_sequence[1000];

  int matrix_count = 0;
  int operation_count = 0;

  int i = 0;

  while (sequence[i] != '\0')
  {
    if (sequence[i] >= 'A' && sequence[i] <= 'Z')
    {
      if (copy_matrix(&matrix_sequence[matrix_count], &matrices[sequence[i] - 'A']) != EXIT_SUCCESS)
      {
        for (int j = 0; j < matrix_count; j++)
        {
          free(matrix_sequence[j].elems);
        }
        return ERROR_INPUT;
      }
      matrix_count++;
    }
    else if (sequence[i] == '+' || sequence[i] == '-')
    {
      operation_sequence[operation_count].sign = sequence[i];
      operation_sequence[operation_count].priority = PRIORITY_ADD;
      operation_count++;
    }
    else if (sequence[i] == '*')
    {
      operation_sequence[operation_count].sign = sequence[i];
      operation_sequence[operation_count].priority = PRIORITY_MUL;
      operation_count++;
    }

    i++;
  }

  if (compute_sequence(matrix_sequence, operation_sequence, &matrix_count, &operation_count) == ERROR_INPUT)
  {
    fprintf(stderr, "Error: Chybny vstup!\n");
    for (size_t i = 0; i < matrix_count; i++)
    {
      free_matrix(&matrix_sequence[i]);
    }
    return ERROR_INPUT;
  }

  // Print the final result
  print_matrix(matrix_sequence[0]);
  free_matrix(&matrix_sequence[0]);

  for (size_t i = 0; i < MAX_SEQUENCE; i++)
  {
    if (matrices[i].cols > 0)
    {
      free_matrix(&matrices[i]);
    }
  }

  return EXIT_SUCCESS;
}

/**
 * Reads the matrix.
 * @param matrix The matrix.
 */
int read_matrix(matrix_t *matrix, char input[])
{
  matrix->size = INIT_SIZE;
  matrix->elems = (int *)calloc(INIT_SIZE, sizeof(int));
  if (!matrix->elems)
  {
    return ERROR_INPUT;
  }
  int cols = 0;
  int elems = 0;
  int i = 2;

  while (input[i] != '\n' && input[i] != '\0')
  {
    if (input[i] == ';')
    {
      cols = 0;
      i++;
    }
    else if (input[i] == '-')
    {
      i++;
      while (input[i] >= '0' && input[i] <= '9')
      {
        matrix->elems[elems] = matrix->elems[elems] * 10 + (input[i] - '0');
        i++;
      }
      matrix->elems[elems] *= -1;
      elems++;
      cols++;
    }
    else if (input[i] == '[' || input[i] == ']' || input[i] == '=' || input[i] == ' ')
    {
      i++;
      continue;
    }
    else
    {
      while (input[i] >= '0' && input[i] <= '9')
      {
        matrix->elems[elems] = matrix->elems[elems] * 10 + (input[i] - '0');
        i++;
      }
      elems++;
      cols++;
    }

    if (elems >= matrix->size)
    {
      int *new_elems = (int *)realloc(matrix->elems, 2 * elems * sizeof(int));
      if (!new_elems)
      {
        return ERROR_INPUT;
      }
      matrix->elems = new_elems;
      for (size_t i = matrix->size; i < 2 * elems; i++)
      {
        matrix->elems[i] = 0;
      }
      matrix->size *= 2;
    }
  }

  matrix->cols = cols;
  matrix->rows = elems / cols;

  return EXIT_SUCCESS;
}

/**
 * Reads the sign of the operation.
 * @param sign The sign of the operation.
 */
int read_sign(char *sign)
{
  if (scanf(" %c", sign) != 1)
  {
    return ERROR_INPUT;
  }

  return 0;
}

/**
 * Prints the matrix.
 * @param matrix The matrix.
 */
void print_matrix(matrix_t matrix)
{
  printf("[");
  for (size_t i = 0; i < matrix.rows; i++)
  {
    for (size_t j = 0; j < matrix.cols; j++)
    {
      printf("%d", matrix.elems[i * matrix.cols + j]);
      if (j < matrix.cols - 1)
      {
        printf(" ");
      }
    }
    if (i < matrix.rows - 1)
    {
      printf("; ");
    }
  }
  printf("]\n");
}

/**
 * Checks if the matrices are compatible for the given operation.
 * @param matrix1 The first matrix.
 * @param matrix2 The second matrix.
 * @param sign The sign of the operation.
 * @return 1 if the matrices are compatible, ERROR_INPUT otherwise.
 */
int matrices_are_compatible(matrix_t *matrix1, matrix_t *matrix2, char sign)
{
  switch (sign)
  {
  case '+':
  case '-':
    if (matrix1->rows == matrix2->rows && matrix1->cols == matrix2->cols)
      return 1;
    break;
  case '*':
    if (matrix1->cols == matrix2->rows)
      return 1;
    break;
  }
  return ERROR_INPUT; // Matrices are incompatible
}

/**
 * Computes the result of the operation.
 * @param matrix1 The first matrix.
 * @param sign The sign of the operation.
 * @param matrix2 The second matrix.
 * @return The result of the operation.
 */
int compute_matrix(matrix_t *matrix1, char sign, matrix_t *matrix2)
{
  if (matrices_are_compatible(matrix1, matrix2, sign) == ERROR_INPUT)
  {
    return ERROR_INPUT;
  }

  switch (sign)
  {
  case '+':
    add_matrix(matrix1, matrix2);
    break;
  case '-':
    sub_matrix(matrix1, matrix2);
    break;
  case '*':
    return mul_matrix(matrix1, matrix2);
  }

  return EXIT_SUCCESS;
}

/**
 * Adds two matrices.
 * @param matrix1 The first matrix.
 * @param matrix2 The second matrix.
 */
void add_matrix(matrix_t *matrix1, matrix_t *matrix2)
{
  for (size_t i = 0; i < matrix1->rows; i++)
  {
    for (size_t j = 0; j < matrix1->cols; j++)
    {
      matrix1->elems[i * matrix1->cols + j] += matrix2->elems[i * matrix1->cols + j];
    }
  }
}

/**
 * Subtracts two matrices.
 * @param matrix1 The first matrix.
 * @param matrix2 The second matrix.
 */
void sub_matrix(matrix_t *matrix1, matrix_t *matrix2)
{
  for (size_t i = 0; i < matrix1->rows; i++)
  {
    for (size_t j = 0; j < matrix1->cols; j++)
    {
      matrix1->elems[i * matrix1->cols + j] -= matrix2->elems[i * matrix1->cols + j];
    }
  }
}

/**
 * Multiplies two matrices.
 * @param matrix1 The first matrix.
 * @param matrix2 The second matrix.
 */
int mul_matrix(matrix_t *matrix1, matrix_t *matrix2)
{
  matrix_t result_matrix;
  result_matrix.rows = matrix1->rows;
  result_matrix.cols = matrix2->cols;
  result_matrix.size = result_matrix.rows * result_matrix.cols;
  result_matrix.elems = (int *)calloc(result_matrix.rows * result_matrix.cols, sizeof(int));
  if (!result_matrix.elems)
  {
    return ERROR_INPUT;
  }

  for (size_t i = 0; i < result_matrix.rows; i++)
  {
    for (size_t j = 0; j < result_matrix.cols; j++)
    {
      result_matrix.elems[i * result_matrix.cols + j] = 0;
      for (size_t k = 0; k < matrix1->cols; k++)
      {
        result_matrix.elems[i * result_matrix.cols + j] += matrix1->elems[i * matrix1->cols + k] * matrix2->elems[k * matrix2->cols + j];
      }
    }
  }

  free_matrix(matrix1);
  if (copy_matrix(matrix1, &result_matrix) != EXIT_SUCCESS)
  {
    free_matrix(&result_matrix);
    return ERROR_INPUT;
  }

  free_matrix(&result_matrix);

  return EXIT_SUCCESS;
}

/**
 * Frees the matrix.
 * @param matrix The matrix.
 */
void free_matrix(matrix_t *matrix)
{
  if (matrix->elems)
  {
    free(matrix->elems);
    matrix->elems = NULL;
    matrix->rows = 0;
    matrix->cols = 0;
    matrix->size = 0;
  }
}

int compute_sequence(matrix_t matrices[], operation_t operations[], int *matrix_count, int *operation_count)
{
  while (*operation_count > 0)
  {
    int highest_priority = -1;
    int highest_index = -1;

    for (size_t i = 0; i < *operation_count; i++)
    {
      if (operations[i].priority > highest_priority)
      {
        highest_priority = operations[i].priority;
        highest_index = i;
      }
    }

    matrix_t *matrix1 = &matrices[highest_index];
    matrix_t *matrix2 = &matrices[highest_index + 1];
    char sign = operations[highest_index].sign;

    if (compute_matrix(matrix1, sign, matrix2) == ERROR_INPUT)
    {
      return ERROR_INPUT;
    }

    free_matrix(matrix2);

    for (size_t i = highest_index + 1; i < *matrix_count - 1; i++)
    {
      matrices[i] = matrices[i + 1];
    }
    for (size_t i = highest_index; i < *operation_count - 1; i++)
    {
      operations[i] = operations[i + 1];
    }

    (*matrix_count)--;
    (*operation_count)--;
  }

  return EXIT_SUCCESS;
}

/**
 * Copies the contents of one matrix to another.
 * @param dest The destination matrix.
 * @param src The source matrix.
 * @return EXIT_SUCCESS on success, ERROR_INPUT on failure.
 */
int copy_matrix(matrix_t *dest, const matrix_t *src)
{
  dest->rows = src->rows;
  dest->cols = src->cols;
  dest->size = src->size;

  dest->elems = (int *)malloc(dest->size * sizeof(int));
  if (!dest->elems)
  {
    return ERROR_INPUT;
  }
  memcpy(dest->elems, src->elems, dest->size * sizeof(int));
  return EXIT_SUCCESS;
}
