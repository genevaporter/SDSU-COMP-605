#define STB_IMAGE_IMPLEMENTATION
#define CHANNEL_NUM 3

#include "stb_image.h"
#include "stb_image_write.h"

int main() {
    int width, height, bpp;

    uint8_t* rgb_image = stbi_load("mandelbrot-set-color.bmp", &width, &height, &bpp, 3);

    stbi_image_free(rgb_image);


    // Write your code to populate rgb_image here

    stbi_write_png("mandelbrot-set-grey.png", width, height, CHANNEL_NUM, rgb_image, width*CHANNEL_NUM);

    return 0;
}
