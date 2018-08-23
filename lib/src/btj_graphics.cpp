/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_graphics.h"

#include "btj_layer.h"
#include "btj_texture.h"
#include "btj_graphics_impl.h"
#include "btj_global_pointers.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<Graphics>::value, "");
static_assert(std::is_copy_constructible<Graphics>::value, "");
static_assert(std::is_copy_assignable<Graphics>::value, "");
static_assert(std::is_nothrow_move_constructible<Graphics>::value, "");
static_assert(std::is_nothrow_move_assignable<Graphics>::value, "");

SizeI Graphics::getSize() const noexcept
{
    return gb.graphics->getSize();
}

Color Graphics::getBackgroundColor() const noexcept
{
    return gb.graphics->getBackgroundColor();
}

void Graphics::setBackgroundColor(const Color& color) noexcept
{
    gb.graphics->setBackgroundColor(color);
}

void Graphics::reserveTextures(std::size_t count)
{
    gb.graphics->reserveTextures(count);
}

Texture Graphics::createTexture(const Image& image)
{
    return gb.graphics->createTexture(image);
}

void Graphics::reserveLayers(std::size_t count)
{
    gb.graphics->reserveLayers(count);
}

Layer Graphics::createLayer(int zOrder)
{
    return gb.graphics->createLayer(zOrder);
}

}
