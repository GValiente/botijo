/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_GRAPHICS_BACKEND_H
#define BTJ_GRAPHICS_BACKEND_H

#include "btj_vector.h"

namespace btj
{

class Color;
class Image;
class PositionF;
class SpriteGraphics;
class TextureGraphics;

namespace GraphicsBackend
{

bool init();

void destroy() noexcept;

TextureGraphics createTextureGraphics();

void destroyTextureGraphics(const TextureGraphics& textureGraphics) noexcept;

void bindTextureGraphics(const TextureGraphics& textureGraphics);

void uploadTextureImage(const Image& image);

SpriteGraphics createSpriteGraphics();

void destroySpriteGraphics(const SpriteGraphics& spriteGraphics) noexcept;

void bindSpriteGraphics(const SpriteGraphics& spriteGraphics);

void uploadSpritePositions(const SpriteGraphics& spriteGraphics, const Vector<PositionF>& positions);

void uploadSpriteColors(const SpriteGraphics& spriteGraphics, const Vector<Color>& colors);

void uploadSpriteTextureCoords(const SpriteGraphics& spriteGraphics, const Vector<PositionF>& textureCoords);

void drawSpriteGraphics(const SpriteGraphics& spriteGraphics);

void setAlphaEnabled(bool enabled);

void setBackgroundColor(const Color& color);

void update();

}

}

#endif
