/*
 * File name: texam.c
 * Date:      2017/01/16 08:43
 * Author:    Jan Faigl
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "exam_utils.h"
#include "xwin_sdl.h"

#ifndef COUNT
#define COUNT 100
#endif

#ifndef N
#define N 6
#endif

#define MAX 1920

bool read_args(unsigned char *in, size_t size, int n, int args[n]);

enum
{
   ERROR_OK = EXIT_SUCCESS,
   ERROR = EXIT_FAILURE
};

void print(void);
void print_hex(void);
int write(char *fname);
int read(char *fname);

int main(int argc, char *argv[])
{
   int ret = ERROR_OK;
   char *mode = argc > 1 ? argv[1] : NULL;
   char *fname = argc > 2 ? argv[2] : NULL;

   if (!mode)
   {
      fprintf(stderr, "ERROR: At least one argument must be given!\n");
      ret = ERROR;
   }
   else if (!strcmp(mode, "print"))
   {
      print();
   }
   else if (!strcmp(mode, "hex"))
   {
      print_hex();
   }
   else if (!strcmp(mode, "write"))
   {
      ret = write(fname);
   }
   else if (!strcmp(mode, "read"))
   {
      ret = read(fname);
   }
   else
   {
      fprintf(stderr, "ERROR: Unknown mode!\n");
      ret = ERROR;
   }

   return ret;
}

void print(void)
{
   for (int i = 0; i < COUNT; ++i)
   {
      putchar('n');
      for (int j = 0; j < N; ++j)
      {
         printf(" %d", rand() % MAX);
      }
      putchar('\n');
   }
}

void print_hex(void)
{
   for (int i = 0; i < COUNT; ++i)
   {
      printf(i == 0 ? "" : " ");
      printf("0x%02x", 'n');
      for (int j = 0; j < N; ++j)
      {
         int val = rand() % MAX;
         unsigned char v1 = (val & 0xff00) >> 8;
         unsigned char v2 = (val & 0x00ff);
         printf(" 0x%02x", v1);
         printf(" 0x%02x", v2);
      }
      printf(" 0x%02x", '\n');
   }
}

int write(char *fname)
{
   int ret = fname ? ERROR_OK : ERROR;
   if (ret == ERROR)
   {
      fprintf(stderr, "ERROR: Write needs filename");
      return ret;
   }

   size_t s = (1 + N * 2 + 1) * COUNT;
   size_t d = ceil(sqrt(s / 3.0));
   int w, h;
   w = h = d;
   size_t size = w * h * 3;

   fprintf(stderr, "DEBUG: no. of bytes %lu to be stored in %d x %d with %lu bytes\n", s, w, h, size);

   unsigned char *img = malloc(size * sizeof(unsigned char));
   my_assert(img != NULL, __func__, __LINE__, __FILE__);
   size_t c = 0;

   for (int i = 0; i < COUNT; ++i)
   {
      img[c++] = 'n';
      for (int j = 0; j < N; ++j)
      {
         int val = rand() % MAX;
         img[c++] = (val & 0xff00) >> 8;
         img[c++] = (val & 0x00ff);
      }
      img[c++] = '\n';
   }
   for (; c < size; ++c)
   {
      img[c] = 0x0;
   }

   save_ppm_image(w, h, img, fname);

   free(img);
   return ret;
}

int read(char *fname)
{
   int ret = fname ? ERROR_OK : ERROR;
   if (ret == ERROR)
   {
      fprintf(stderr, "ERROR: Read needs filename");
      return ret;
   }

   int w, h;
   unsigned char *img = xwin_load_image(fname, &w, &h);
   if (!img)
   {
      fprintf(stderr, "ERROR: Cannot read image from %s\n", fname);
      return ERROR;
   }
   size_t size = w * h * 3;
   size_t c = 0;
   bool ok = true;

   while (ok && c < size)
   {
      if (img[c] == 0x0)
      {
         c += 1; // skip
         continue;
      }
      if (img[c] != 'n')
      {
         ok = false;
         continue;
      }
      if ((c + 1 + 2 * N + 1) >= size)
      {
         ok = false;
         continue;
      }
      int args[N];
      ok = read_args(&img[c + 1], size - c - 1, N, args);

      if (ok && img[c + 1 + 2 * N] == '\n')
      {
         c += 1 + 2 * N + 1;
         putchar('n');
         for (int r = 0; r < N; ++r)
         {
            printf(" %d", args[r]);
         }
         putchar('\n');
      }
      else
      {
         fprintf(stderr, "ERROR: Incorrect input\n");
         ok = false;
         continue;
      }
   }

   if (!ok)
   {
      fprintf(stderr, "ERROR: Incorrect input from the file %s\n", fname);
   }

   free(img);
   return ret;
}

bool read_args(unsigned char *in, size_t size, int n, int args[n])
{
   bool ok = (size_t)(n * 2) < size;
   if (!ok)
   {
      return false;
   }
   for (int i = 0; i < n; ++i)
   {
      args[i] = (in[i * 2 + 0] << 8 & 0xff00) |
                (in[i * 2 + 1] & 0x00ff);
   }

   return ok;
}

/* end of texam.c */
