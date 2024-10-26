#include <stdio.h>
#include <stdlib.h>

#define ERROR_INPUT 100
#define ERROR_INTERVAL 101
#define ERROR_ODD 102
#define ERROR_FENCE_SIZE 103

#define MIN_VALUE 3
#define MAX_VALUE 69

/* Function prototypes */
int read_input(int *num1, int *num2, int *num3);
void print_error(int err);
void print_roof(int width, int height);
void print_house(int width, int height, int fence_width);
void print_fence(int fence_width, int house_height, int height);

int main(int argc, char *argv[])
{
  int width, height;
  int fence_size = 0;
  int ret = read_input(&width, &height, &fence_size);

  if (ret != EXIT_SUCCESS)
  {
    print_error(ret);
    return ret;
  }

  print_roof(width, height);
  print_house(width, height, fence_size);

  return EXIT_SUCCESS;
}

/**
 * Reads the input from the user.
 * @var num1 - the width of the house
 * @var num2 - the height of the house
 * @var num3 - the size of the fence
 */
int read_input(int *num1, int *num2, int *num3)
{
  int ret = scanf("%d %d", num1, num2);

  if (ret != 2)
  {
    return ERROR_INPUT;
  }
  if (!((*num1 >= MIN_VALUE && *num1 <= MAX_VALUE) &&
        (*num2 >= MIN_VALUE && *num2 <= MAX_VALUE)))
  {
    return ERROR_INTERVAL;
  }
  if (!(*num1 % 2 == 1))
  {
    return ERROR_ODD;
  }
  if (*num1 == *num2)
  {
    ret = scanf("%d", num3);

    if (ret != 1)
    {
      return ERROR_INPUT;
    }
    if (*num3 >= *num2 || *num3 <= 0)
    {
      return ERROR_FENCE_SIZE;
    }
  }

  return EXIT_SUCCESS;
}

/**
 * Prints the error message.
 * @var err - the error code
 */
void print_error(int err)
{
  switch (err)
  {
  case ERROR_INPUT:
    fprintf(stderr, "Error: Chybny vstup!\n");
    break;
  case ERROR_INTERVAL:
    fprintf(stderr, "Error: Vstup mimo interval!\n");
    break;
  case ERROR_ODD:
    fprintf(stderr, "Error: Sirka neni liche cislo!\n");
    break;
  case ERROR_FENCE_SIZE:
    fprintf(stderr, "Error: Neplatna velikost plotu!\n");
    break;
  default:
    break;
  }
}

/**
 * Prints the roof of the house.
 * @var width - the width of the house
 * @var height - the height of the house
 */
void print_roof(int width, int height)
{
  for (int i = width / 2; i > 0; i--)
  {
    for (int j = 0; j <= width - i - 1; j++)
    {
      // Print 'X' at the edges of the roof
      if (j == i || j == width - i - 1)
      {
        putchar('X');
      }
      else
      {
        putchar(' ');
      }
    }
    putchar('\n');
  }
}

/**
 * Prints the house.
 * @var width - the width of the house
 * @var height - the height of the house
 * @var fence_size - the size of the fence
 */
void print_house(int width, int height, int fence_size)
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      // Print 'X' at the edges and top/bottom of the house
      if (j == 0 || j == width - 1 || i == 0 || i == height - 1)
      {
        putchar('X');
      }
      // Print 'o' or '*' in the middle of the house if fence should be created
      else if (width == height)
      {
        putchar((i + j) % 2 == 0 ? 'o' : '*');
      }
      else
      {
        putchar(' ');
      }
    }
    if (width == height && i >= (height - fence_size))
    {
      print_fence(fence_size, height, i);
    }
    putchar('\n');
  }
}

/**
 * Prints the fence.
 * @var fence_size - the size of the fence
 * @var house_height - the height of the house
 * @var current_height - the current height
 */
void print_fence(int fence_size, int house_height, int current_height)
{
  for (int i = 0; i < fence_size; i++)
  {
    // Check if the fence size is even or odd
    if (fence_size % 2 == 0)
    {
      // Print '|' at the odd indexes
      if (i % 2 == 1)
      {
        putchar('|');
      }
      // Print '-' at the bottom and top of the fence
      else if (current_height == house_height - 1 ||
               current_height == house_height - fence_size)
      {
        putchar('-');
      }
      else
      {
        putchar(' ');
      }
    }
    else
    {
      // Print '|' at the even indexes
      if (i % 2 == 0)
      {
        putchar('|');
      }
      // Print '-' at the bottom and top of the fence
      else if (current_height == house_height - 1 ||
               current_height == house_height - fence_size)
      {
        putchar('-');
      }
      else
      {
        putchar(' ');
      }
    }
  }
}
