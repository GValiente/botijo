#if defined(__GNUC__) || defined(__GNUG__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wcast-qual"
    #pragma GCC diagnostic ignored "-Wcast-align"
    #pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image_interface.h"

#if defined(__GNUC__) || defined(__GNUG__)
    #pragma GCC diagnostic pop
#endif
