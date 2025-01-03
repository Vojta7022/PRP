#include <stdio.h>

int main(int argc, char *argv[]) 
{
   char *fname = argc > 1 ? argv[1] : "text.txt";
   FILE *f;
   if ((f = fopen(fname, "r")) == NULL) {
      fprintf(stderr, "Error: Open file '%s'\n", fname);
      return -1;
   }
   char c;
   int count = 0;
   while ((c = getc(f)) != EOF) {
      printf("Read character %d is '%c'\n", count, c);
      count++;
   }
   printf("Number of read characters %d\n", count);
   if (fclose(f) == EOF) {
      fprintf(stderr, "Error: Close file '%s'\n", fname);
      return -1;
   }
   return 0;
}
