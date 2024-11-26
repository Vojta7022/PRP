#include <stdio.h>
#include <stdlib.h>

#define ERROR_INPUT 100

typedef struct matrix
{
  int rows;
  int cols;
  int *elems;
} matrix_t;

// Function prototypes
int read_matrix(matrix_t *matrix);
int read_sign(char *sign);
void print_matrix(matrix_t matrix);
int matrices_are_compatible(matrix_t *matrix1, matrix_t *matrix2, char sign);
int compute_matrix(matrix_t *matrix1, char sign, matrix_t *matrix2);
void add_matrix(matrix_t *matrix1, matrix_t *matrix2);
void sub_matrix(matrix_t *matrix1, matrix_t *matrix2);
int mul_matrix(matrix_t *matrix1, matrix_t *matrix2);
int allocate_matrix(matrix_t *matrix, int rows, int cols);
void free_matrix(matrix_t *matrix);

int main(int argc, char *argv[])
{
  matrix_t matrix1;
  matrix_t matrix2;
  char sign;

  if (read_matrix(&matrix1) == ERROR_INPUT ||
      read_sign(&sign) == ERROR_INPUT ||
      read_matrix(&matrix2) == ERROR_INPUT)
  {
    fprintf(stderr, "Error: Chybny vstup!\n");
    return ERROR_INPUT;
  }

  if (compute_matrix(&matrix1, sign, &matrix2) == ERROR_INPUT)
  {
    fprintf(stderr, "Error: Chybny vstup!\n");
    free_matrix(&matrix1);
    free_matrix(&matrix2);
    return ERROR_INPUT;
  }

  print_matrix(matrix1);

  free_matrix(&matrix1);
  free_matrix(&matrix2);

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
        free_matrix(matrix);
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
    return matrix1->rows == matrix2->rows && matrix1->cols == matrix2->cols;
    break;
  case '*':
    return matrix1->cols == matrix2->rows;
    break;
  default:
    return ERROR_INPUT;
  }
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
 * Allocates the matrix.
 * @param matrix The matrix.
 * @param rows The number of rows.
 * @param cols The number of columns.
 * @return EXIT_SUCCESS if the matrix was allocated, ERROR_INPUT otherwise.
 */
int allocate_matrix(matrix_t *matrix, int rows, int cols) {
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->elems = (int *)malloc(rows * cols * sizeof(int));
    return matrix->elems ? EXIT_SUCCESS : ERROR_INPUT;
}

/**
 * Frees the matrix.
 * @param matrix The matrix.
 */
void free_matrix(matrix_t *matrix) {
    free(matrix->elems);
    matrix->elems = NULL;
}
