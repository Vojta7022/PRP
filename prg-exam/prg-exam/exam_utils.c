/*
 * File name: exam_utils.c
 * Date:      2017/01/16 08:43
 * Author:    Jan Faigl
 */

#include <stdio.h>
#include <stdlib.h>

#include "exam_utils.h"

#define IMAGE_COMMENT "#PRG-exam"

#define MAX_COLOR_VALUE 255

void my_assert(int r, const char *fcname, int line, const char *fname)
{
   if (!(r)) {
      fprintf(stderr, "ERROR: my_assert FAIL: %s() line %d in %s\n", fcname, line, fname);
      exit(-1);
   }
}


void save_image_ppm(int w, int h, unsigned char *img, const char *fname)
{
    FILE *fd = fopen(fname, "wb");
    my_assert(fd != NULL, __func__, __LINE__, __FILE__);
    fprintf(fd, "P6\n %s\n %d\n %d\n %d\n", IMAGE_COMMENT, w, h, MAX_COLOR_VALUE);
    my_assert(fwrite(img, 1, w*h*3, fd) == w*h*3, __func__, __LINE__, __FILE__);
    fclose(fd);
}


/* end of exam_utils.c */
