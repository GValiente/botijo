#ifndef STB_IMAGE_INTERFACE_H
#define STB_IMAGE_INTERFACE_H

#define STBI_NO_PSD
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STBI_NO_PIC
#define STBI_NO_PNM

#ifdef __arm__
    #define STBI_NEON
#endif

#include "stb_image.h"

#endif
