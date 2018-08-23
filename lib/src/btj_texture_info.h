/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_TEXTURE_INFO_H
#define BTJ_TEXTURE_INFO_H

#include "btj_texture_graphics.h"

namespace btj
{

class TextureInfo
{

public:
    TextureGraphics graphics;
    int width = 0;
    int height = 0;
    bool alpha = false;
};

}

#endif
