#include <stdio.h>

void print_colored_line(char line[], const char *pattern)
{
  int pattern_found = 0;
  int end_index = -1;

  for (size_t i = 0; line[i] != '\0'; i++)
  {
    if (pattern_found == 0)
    {
      for (size_t j = 0; pattern[j] != '\0'; j++)
      {
        if (line[i + j] != pattern[j])
        {
          break;
        }
        if (pattern[j + 1] == '\0')
        {
          pattern_found = 1;
          end_index = i + j;
        }
      }
    }

    if (pattern_found == 1)
    {
      printf("\x1b[01;31m\x1b[K");
      pattern_found = 2;
    }

    putchar(line[i]);

    if (pattern_found == 2 && i == end_index)
    {
      printf("\x1b[m\x1b[K");
      pattern_found = 0;
    }
  }

  printf("\n");
}

int strings_equal(const char *s1, const char *s2)
{
  for (size_t i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
  {
    if (s1[i] != s2[i])
    {
      return 0;
    }
  }
  return 1;
}

int main()
{
  char line[] = "This is a test line with a pattern.";
  const char *pattern = "pattern";
  print_colored_line(line, pattern);
  return 0;
}
