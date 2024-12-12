#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 2048

// Function prototypes
int search_for_pattern(char line[], const char *pattern);
void print_colored_line(char line[], const char *pattern);
int search_for_pattern_regex(const char *line, const char *pattern);
int strings_equal(const char *s1, const char *s2);

int main(int argc, char *argv[])
{
  FILE *file = NULL;
  const char *pattern = argv[1];

  switch (argc)
  {
  case 2:
    file = stdin;
    break;
  case 3:
    if (strings_equal(argv[1], "-E") == 0 || strings_equal(argv[1], "--color=always") == 0)
    {
      file = stdin;
      pattern = argv[2];
    }
    else
    {
      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        fprintf(stderr, "Error: Cannot open the file\n");
        return EXIT_FAILURE;
      }
    }
    break;
  case 4:
    pattern = argv[2];
    if (strings_equal(argv[1], "-E") != 0 && strings_equal(argv[1], "--color=always") != 0)
    {
      fprintf(stderr, "Error: Invalid option\n");
      return EXIT_FAILURE;
    }
    file = fopen(argv[3], "r");
    if (file == NULL)
    {
      fprintf(stderr, "Error: Cannot open the file\n");
      return EXIT_FAILURE;
    }
    break;
  default:
    fprintf(stderr, "Error: Invalid number of arguments\n");
    return EXIT_FAILURE;
  }

  char line[MAX_LINE_LENGTH];
  int ret = EXIT_FAILURE;
  while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
  {
    if (strings_equal(argv[1], "-E") == 0)
    {
      if (search_for_pattern_regex(line, pattern) == EXIT_SUCCESS)
      {
        printf("%s", line);
        ret = EXIT_SUCCESS;
      }
    }
    else if (search_for_pattern(line, pattern) == EXIT_SUCCESS)
    {
      if (strings_equal(argv[1], "--color=always") == 0)
      {
        print_colored_line(line, pattern);
      }
      else
      {
        printf("%s", line);
      }
      ret = EXIT_SUCCESS;
    }
  }

  fclose(file);
  return ret;
}

int search_for_pattern(char line[], const char *pattern)
{
  if (pattern == NULL)
  {
    return EXIT_FAILURE;
  }

  for (size_t i = 0; line[i] != '\0'; i++)
  {
    if (line[i] == pattern[0])
    {
      for (size_t j = 0; pattern[j] != '\0'; j++)
      {
        if (line[i + j] != pattern[j])
        {
          break;
        }
        if (pattern[j + 1] == '\0')
        {
          return EXIT_SUCCESS;
        }
      }
    }
  }

  return EXIT_FAILURE;
}

void print_colored_line(char line[], const char *pattern)
{
  int end_index = -1;
  int pattern_found = 0;

  for (size_t i = 0; line[i] != '\0'; i++)
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
        break;
      }
    }
    if (pattern_found == 1)
    {
      printf("\x1b[01;31m\x1b[K");
      pattern_found = 2;
    }

    printf("%c", line[i]);

    if (pattern_found == 2 && i == end_index)
    {
      printf("\x1b[m\x1b[K");
      pattern_found = 0;
      end_index = -1;
    }
  }
}

int search_for_pattern_regex(const char *line, const char *pattern)
{
  size_t i = 0, j = 0;

  while (line[i] != '\0')
  {
    if (pattern[j] == '\0')
    {
      return EXIT_SUCCESS;
    }
    else if (pattern[j + 1] == '*')
    {
      // '*' matches zero or more of the preceding character
      while (line[i] == pattern[j])
      {
        i++;
      }
      j += 2;
    }
    else if (pattern[j + 1] == '+')
    {
      // '+' matches one or more of the preceding character
      if (line[i] != pattern[j])
      {
        j = 0;
        continue;
      }
      while (line[i] == pattern[j])
      {
        i++;
      }
      j += 2;
    }
    else if (pattern[j + 1] == '?')
    {
      // '?' matches zero or one of the preceding character
      if (line[i] == pattern[j])
      {
        i++;
      }
      j += 2;
    }
    else
    {
      if (line[i] != pattern[j])
      {
        j = 0;
      }
      else
      {
        j++;
      }
      i++;
    }
  }

  return (pattern[j] == '\0') ? EXIT_SUCCESS : EXIT_FAILURE;
}

int strings_equal(const char *s1, const char *s2)
{
  for (size_t i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
  {
    if (s1[i] != s2[i])
    {
      return 1;
    }
  }
  return 0;
}
