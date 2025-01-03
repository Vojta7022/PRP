#include <stdio.h>
#include <string.h>

#include <stdlib.h>

int parse_int(const char *str, int len);
char* int_to_string(int v, char *buf, size_t capacity);

int main(int argc, char *argv[])
{
   char *str = "31495155 ";
   const int n = 256;
   char out[n];

   int v = parse_int(str, strlen(str));
   char *sint = int_to_string(v, out, n);

   printf("Parse string \"%s\" to int value %d.\n", str, v);
   printf("Convert int %d into string \"%s\".\n", v, sint);

   return EXIT_SUCCESS;
}

int parse_int(const char *str, int len)
{
   int num = 0;
   int i = 0;
   while (i < len && str[i] >= '0' && str[i] <= '9') {
      num = num * 10 + (str[i++] - '0');
   }
   return str[i] == ' ' || str[i] == '\n' ? num : -1;
}

char* int_to_string(int v, char *buf, size_t capacity)
{
   char *cur = buf + capacity - 1; //last char of the buffer buf
   *cur = '\0';
   do {
      int least = v % 10;
      v /= 10;
      *(--cur) = least + '0';
   } while (v != 0);
   return cur;
}
