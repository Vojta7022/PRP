/*
 * File name: texam.c
 * Date:      2017/01/16 08:43
 * Author:    Jan Faigl
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "xwin_sdl.h"
#include "save_jpeg.h"
#include "exam_utils.h"

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

// Function prototypes
bool process_file(FILE *fd, unsigned char *img, int image_w, int image_h, bool anim);
bool copy(unsigned char *img, int image_w, int image_h, int x1, int y1, int w, int h, int x2, int y2);
bool swap(unsigned char *img, int image_w, int image_h, int x1, int y1, int w, int h, int x2, int y2);
bool mirror_horizontal(unsigned char *img, int image_w, int image_h);
bool mirror_vertical(unsigned char *img, int image_w, int image_h);

// - main function ----------------------------------------------------------------
int main(int argc, char *argv[])
{
   // 1. Process arguments
   const char *fimage = argc > 1 ? argv[1] : NULL;
   const char *fcmds = argc > 2 ? argv[2] : NULL;
   const char *fout = argc > 3 ? argv[3] : NULL;
   const bool anim = argc > 4 && strcmp(argv[4], "--anim") == 0 ? true : false;

   my_assert(fimage != NULL && fcmds != NULL && fout != NULL, __func__, __LINE__, __FILE__);

   // 2. load image
   int image_w, image_h;
   unsigned char *img = xwin_load_image(fimage, &image_w, &image_h);
   my_assert(img != NULL, __func__, __LINE__, __FILE__);

   if (anim)
   {
      xwin_init(image_w, image_h);
   }

   // 3. process cmds
   FILE *fd = fopen(fcmds, "r");
   // my_assert(fd != NULL, __func__, __LINE__, __FILE__);
   if (fd == NULL)
   {
      fprintf(stderr, "ERROR: cannot open file '%s'\n", fout);
      free(img);
      if (anim)
      {
         xwin_close();
      }
      exit(-1);
   }

   my_assert(process_file(fd, img, image_w, image_h, anim), __func__, __LINE__, __FILE__);

   // 4. save output
   if (fout && (strstr(fout, ".jpeg") || strstr(fout, ".jpg")))
   {
      save_image_jpeg(image_w, image_h, img, fout);
   }
   else
   {
      save_ppm_image(image_w, image_h, img, fout);
   }

   if (anim)
   {
      xwin_close();
   }
   free(img);

   return EXIT_SUCCESS;
}

// - function ----------------------------------------------------------------
bool process_file(FILE *fd, unsigned char *img, int image_w, int image_h, bool anim)
{
   bool ret = true;
   int x1, y1, x2, y2;
   int w, h;
   char cmd[3];
   int counter = 0;

   while (ret && !feof(fd))
   {
      int r = fscanf(fd, "%2s %d %d %d %d %d %d\n", cmd, &x1, &y1, &w, &h, &x2, &y2);
      if (r == 7 && strcmp(cmd, "cp") == 0)
      {
         ret = copy(img, image_w, image_h, x1, y1, w, h, x2, y2);
      }
      else if (r == 7 && strcmp(cmd, "sw") == 0)
      {
         ret = swap(img, image_w, image_h, x1, y1, w, h, x2, y2);
      }
      else
      {
         ret = false;
         break;
      }

      counter += 1;
      if (anim && (counter % 15) == 0)
      {
         xwin_redraw(image_w, image_h, img);
         delay(1);
      }
   }
   return ret;
}

// - function ----------------------------------------------------------------
bool copy(unsigned char *img, int image_w, int image_h, int x1, int y1, int w, int h, int x2, int y2)
{
   bool ret = true;
   for (int xi = 0; xi < w; ++xi)
   {
      for (int yi = 0; yi < h; ++yi)
      {
         const int sx = x1 + xi;
         const int sy = y1 + yi;
         const int dx = x2 + xi;  
         const int dy = y2 + yi;

         if (sx >= 0 && sx < image_w && sy >= 0 && sy < image_h &&
             dx >= 0 && dx < image_w && dy >= 0 && dy < image_h)
         {
            for (int i = 0; i < 3; ++i)
            {
               img[(dy * image_w + dx) * 3 + i] = img[(sy * image_w + sx) * 3 + i];
            }
         }
         else
         {
            fprintf(stderr, "ERROR: copy cmd out of range");
            return false;
         }
      }
   }
   return ret;
}

// - function ----------------------------------------------------------------
bool swap(unsigned char *img, int image_w, int image_h, int x1, int y1, int w, int h, int x2, int y2)
{
   bool ret = true;
   for (int xi = 0; xi < w; ++xi)
   {
      for (int yi = 0; yi < h; ++yi)
      {
         const int sx = x1 + xi;
         const int sy = y1 + yi;
         const int dx = x2 + xi;
         const int dy = y2 + yi;

         if (sx >= 0 && sx < image_w && sy >= 0 && sy < image_h &&
             dx >= 0 && dx < image_w && dy >= 0 && dy < image_h) 
         {
            for (int i = 0; i < 3; ++i)
            {
               unsigned char temp = img[(dy * image_w + dx) * 3 + i];
               img[(dy * image_w + dx) * 3 + i] = img[(sy * image_w + sx) * 3 + i];
               img[(sy * image_w + sx) * 3 + i] = temp;
            }
         }
         else
         {
            fprintf(stderr, "ERROR: copy cmd out of range");
            return false;
         }
      }
   }
   return ret;
}

bool mirror_horizontal(unsigned char *img, int image_w, int image_h)
{
    if (!img || image_w <= 0 || image_h <= 0) {
        fprintf(stderr, "ERROR: Invalid image dimensions or data.\n");
        return false;
    }

    for (int x = 0; x < image_w; ++x)
    {
        for (int y = 0; y < image_h / 2; ++y)
        {
            int top_idx = (y * image_w + x) * 3;
            int bottom_idx = ((image_h - y - 1) * image_w + x) * 3;

            for (int i = 0; i < 3; ++i) // Swap RGB values
            {
                unsigned char temp = img[top_idx + i];
                img[top_idx + i] = img[bottom_idx + i];
                img[bottom_idx + i] = temp;
            }
        }
    }

    return true;
}

bool mirror_vertical(unsigned char *img, int image_w, int image_h)
{
    if (!img || image_w <= 0 || image_h <= 0) {
        fprintf(stderr, "ERROR: Invalid image dimensions or data.\n");
        return false;
    }

    for (int y = 0; y < image_h; ++y)
    {
        for (int x = 0; x < image_w / 2; ++x)
        {
            int left_idx = (y * image_w + x) * 3;
            int right_idx = (y * image_w + (image_w - x - 1)) * 3;

            for (int i = 0; i < 3; ++i) // Swap RGB values
            {
                unsigned char temp = img[left_idx + i];
                img[left_idx + i] = img[right_idx + i];
                img[right_idx + i] = temp;
            }
        }
    }

    return true;
}

/* end of texam.c */
