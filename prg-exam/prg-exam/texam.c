/*
 * File name: texam.c
 * Date:      2017/01/16 08:43
 * Author:    Jan Faigl
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "exam_utils.h"
#include "save_jpeg.h"
#include "xwin_sdl.h"


void swap_pixels(unsigned char *img, int w, int h, int x_src, int y_src, int width, int height, int x_dst, int y_dst);

void process_commands(unsigned char *img, int w, int h, const char *fname, bool is_animated);

void copy_pixels(unsigned char *img, int w, int h, int x_src, int y_src, int width, int height, int x_dst, int y_dst);


int main(int argc, char *argv[]) 
{
    my_assert(argc == 4 || argc == 5, __func__, __LINE__, __FILE__);
    const char *load_fname = argv[1]; // file name of the image we want to process
    const char *commands_fname = argv[2]; // file name of the command file
    const char *save_fname = argv[3]; // destination of our processed image
    bool is_animated = argc == 5 && strstr(argv[4], "--anim");
    bool is_jpeg = strstr(save_fname, "jpeg") != NULL || strstr(save_fname, "jpg") != NULL;
    int h = 0, w = 0; //the size of the image will be saved here after the image is loaded

    unsigned char *img = xwin_load_image(load_fname, &w, &h);
    my_assert(img != NULL, __func__, __LINE__, __FILE__);
    if(is_animated){
        my_assert(xwin_init(w, h) == 0,  __func__, __LINE__, __FILE__);
    }
    process_commands(img, w, h, commands_fname, is_animated);

    if(is_jpeg)
    {
        save_image_jpeg(w, h, img, save_fname);
    }
    else
    {
        save_image_ppm(w,h,img, save_fname);
    }

    if(img) {
        free(img);
        img = NULL;
    }
    return EXIT_SUCCESS;
}

void swap_pixels(unsigned char *img, int w, int h, int x_src, int y_src, int width, int height, int x_dst, int y_dst)
{
    // out of bounds check
    my_assert(width < w && height < h && width + x_src < w && height + y_src < h && x_dst + width < w && y_src+height < h, __func__, __LINE__, __FILE__);
    unsigned char *buffer = malloc(3*width*height);
    if(buffer == NULL){
        free(img);
        my_assert(false, __func__, __LINE__, __FILE__);
    }
    size_t length = 0;
    for(int i = 0; i < height; i++)
    {
        /* copies from pointer img at starting index, moves to the correct line and then offsets to the correct x offset
         * It then copies the whole line of the square we need to copy to the buffer */
        memcpy(buffer + length, img + (y_src*w*3 + x_src*3 + w*3*i), width*3);
        length += width*3;
    }
    my_assert(length == 3*width*height, __func__, __LINE__, __FILE__);
    for(int i = 0; i < height; i++)
    {
        //copies from the destiantion to the source
        memcpy(img + (y_src*w*3 + x_src*3 + w*3*i), img + (y_dst*w*3 + x_dst*3 + w*3*i), width*3);
    }
    for(int i = 0; i < height; i++)
    {
        //copies from the source in buffer to the destination
        memcpy(img + (y_dst*w*3 + x_dst*3 + w*3*i), buffer + i * width*3, width * 3);
    }
    //better safe than sorry
    if(buffer){
        free(buffer);
        buffer = NULL;
    }
}

void copy_pixels(unsigned char *img, int w, int h, int x_src, int y_src, int width, int height,int x_dst, int y_dst)
{
    // out of bounds check
    my_assert(width < w && height < h && width + x_src < w && height + y_src < h && x_dst + width < w && y_src+height < h, __func__, __LINE__, __FILE__);

    for(int i = 0; i < height; i++)
    {
        //copies from the destination to the source
        memcpy(img + (y_dst*w*3 + x_dst*3 + w*3*i), img + (y_src*w*3 + x_src*3 + w*3*i), width*3);
    }
}

void process_commands(unsigned char *img, int w, int h, const char *fname, bool is_animated)
{
    FILE *fd = fopen(fname, "r");
    my_assert(fd != NULL, __func__, __LINE__, __FILE__);
    while(!feof(fd)){
        int x_src, y_src, width, height, x_dst, y_dst;
        if(fscanf(fd, "sw %d %d %d %d %d %d\n", &x_src, &y_src, &width, &height, &x_dst, &y_dst) == 6)
        {
            swap_pixels(img, w, h, x_src, y_src, width, height, x_dst, y_dst);
        }
        else if(fscanf(fd, "cp %d %d %d %d %d %d\n", &x_src, &y_src, &width, &height, &x_dst, &y_dst) == 6){
            copy_pixels(img, w, h, x_src, y_src, width, height, x_dst, y_dst);
        }else{
            my_assert(false,  __func__, __LINE__, __FILE__);
        }
        if(is_animated) {
            xwin_redraw(w, h, img);
            delay(10);
        }
    }
    my_assert(fclose(fd) == 0, __func__, __LINE__, __FILE__);
}
/* end of texam.c */

// erhjgnoejrnoearn
