#include <stdio.h>
#include <stdlib.h>

#define ERROR_INPUT 100
#define MAX_SEQUENCE 100

#define PRIORITY_ADD 1
#define PRIORITY_SUB 1
#define PRIORITY_MUL 2

typedef struct matrix
{
  int rows;
  int cols;
  int *elems;
} matrix_t;

typedef struct operation
{
  char sign;
  int priority;
} operation_t;

// Function prototypes
int read_matrix(matrix_t *matrix);
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

int main(int argc, char *argv[])
{
  matrix_t matrices[MAX_SEQUENCE];
  operation_t operations[MAX_SEQUENCE - 1];
  int matrix_count, operation_count;

  for (size_t i = 0; i < MAX_SEQUENCE; i++)
  {
    matrices[i].rows = 0;
    matrices[i].cols = 0;
    matrices[i].elems = NULL;
  }

  if (read_sequence(matrices, operations, &matrix_count, &operation_count) == ERROR_INPUT)
  {
    fprintf(stderr, "Error: Chybny vstup!\n");
    for (size_t i = 0; i < matrix_count + 1; i++)
    {
      free_matrix(&matrices[i]);
    }
    return ERROR_INPUT;
  }

  if (compute_sequence(matrices, operations, &matrix_count, &operation_count) == ERROR_INPUT)
  {
    fprintf(stderr, "Error: Chybny vstup!\n");
    for (size_t i = 0; i < matrix_count; i++)
    {
      free_matrix(&matrices[i]);
    }
    return ERROR_INPUT;
  }

  // Print the final result
  print_matrix(matrices[0]);

  free_matrix(&matrices[0]);

  return EXIT_SUCCESS;
}

/**
 * Reads the matrix.
 * @param matrix The matrix.
 */
int read_matrix(matrix_t *matrix)
{
  if (scanf("%d %d", &matrix->rows, &matrix->cols) != 2 || matrix->rows <= 0 || matrix->cols <= 0)
  {
    return ERROR_INPUT;
  }

  matrix->elems = (int *)malloc(matrix->rows * matrix->cols * sizeof(int));
  if (!matrix->elems)
  {
    return ERROR_INPUT;
  }

  for (size_t i = 0; i < matrix->rows; i++)
  {
    for (size_t j = 0; j < matrix->cols; j++)
    {
      if (scanf("%d", &matrix->elems[i * matrix->cols + j]) != 1)
      {
        return ERROR_INPUT;
      }
    }
  }

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
  printf("%d %d\n", matrix.rows, matrix.cols);
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
    printf("\n");
  }
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
  result_matrix.elems = (int *)malloc(result_matrix.rows * result_matrix.cols * sizeof(int));
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
  *matrix1 = result_matrix;

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
  }
}

int read_sequence(matrix_t matrices[], operation_t operations[], int *matrix_count, int *operation_count)
{
  *matrix_count = 0;
  *operation_count = 0;

  while (*matrix_count < MAX_SEQUENCE)
  {
    if (read_matrix(&matrices[*matrix_count]) == ERROR_INPUT)
    {
      return ERROR_INPUT;
    }
    (*matrix_count)++;

    char sign;
    if (read_sign(&sign) == ERROR_INPUT)
    {
      break;
    }

    operations[*operation_count].sign = sign;
    switch (sign)
    {
    case '+':
      operations[*operation_count].priority = PRIORITY_ADD;
      break;
    case '-':
      operations[*operation_count].priority = PRIORITY_SUB;
      break;
    case '*':
      operations[*operation_count].priority = PRIORITY_MUL;
      break;

    default:
      return ERROR_INPUT;
    }
    (*operation_count)++;
  }

  return EXIT_SUCCESS;
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
