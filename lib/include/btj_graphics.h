/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_GRAPHICS_H
#define BTJ_GRAPHICS_H

#include <cstddef>

namespace btj
{

class SizeI;
class Layer;
class Color;
class Image;
class Texture;

class Graphics
{

public:
    SizeI getSize() const noexcept;

    Color getBackgroundColor() const noexcept;

    void setBackgroundColor(const Color& color) noexcept;

    void reserveTextures(std::size_t count);

    Texture createTexture(const Image& image);

    void reserveLayers(std::size_t count);

    Layer createLayer(int zOrder = 0);
};

}

#endif
