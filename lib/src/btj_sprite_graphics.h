/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_SPRITE_GRAPHICS_H
#define BTJ_SPRITE_GRAPHICS_H

#include "btj_texture_graphics.h"

namespace btj
{

class SpriteGraphics
{

public:
    struct PublicData
    {
        TextureGraphics textureGraphics;
        std::size_t numSprites = 0;
        int alpha = 0;
    };

    PublicData publicData;
    char backendData[32];
};

}

#endif
