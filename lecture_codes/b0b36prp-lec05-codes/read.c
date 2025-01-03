#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INIT_SIZE
#define INIT_SIZE 128
#endif 

enum {
   ERROR_OK = EXIT_SUCCESS,
   ERROR_IN = 100,
   ERROR_MEM = 101,
};

char* read(int *error);
char* enlarge_string(size_t len, size_t *capacity, char *str);

// - main ---------------------------------------------------------------------
int main(int argc, char *argv[])
{
   int ret = EXIT_SUCCESS;
   char *str = read(&ret);
   if (str) {
      printf("Input string size %ld\n", strlen(str));
      //printf("Input string \"%s\"\n", str);
      free(str);
   } else {
      fprintf(stderr, "ERROR: read return %d\n", ret);
   }
   return ret;
}

// - function -----------------------------------------------------------------
static char* handle_str(char r, size_t l, char *str, int *error);
char* read(int *error)
{
   size_t capacity = INIT_SIZE;
   size_t l = 0; // current length of the read string
   char* str = malloc(capacity + 1); // +1 for '\0'; str == NULL indicate mem error
   int r = '\0';
   while (str && *error == ERROR_OK && (r = getchar()) != EOF && r != '\n') {
      if (l == capacity) { // ensure str is large enough
         str = enlarge_string(l, &capacity, str); // it might allocate new memory
      }
      str[l++] = r; //TODO endure str is not NULL after calling enlarge_string()
   } // end while
   str = handle_str(r, l, str, error);
   return str;
}

// - function -----------------------------------------------------------------
char* handle_str(char r, size_t l, char *str, int *error)
{
   if (str) {
      if (r != '\n') { // end-of-line has not been read 
         *error = ERROR_IN; // report input error
         free(str);
         str = NULL; 
      } else {
         str[l] = '\0'; // null terminating string
      }
   } else if (*error == ERROR_OK) { // str is NULL but error has not been indicated
      *error = ERROR_MEM;
   }
   return str;
}

// - function -----------------------------------------------------------------
char* enlarge_string(size_t len, size_t *capacity, char *str)
{
   char *t = realloc(str, *capacity * 2 + 1);
   if (!t) {
      free(str);
      str = NULL; // indicate error 
   } else {
      str = t;
      *capacity *= 2;
   }
   return str;
}
