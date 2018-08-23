/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_TEXTURE_REGION_H
#define BTJ_TEXTURE_REGION_H

#include "btj_rect_i.h"

namespace btj
{

class RectF;
class Texture;

class TextureRegion
{

public:
    explicit TextureRegion(const Texture& texture) noexcept;

    TextureRegion(const Texture& texture, const RectI& rect) noexcept;

    std::size_t getId() const noexcept
    {
        return _id;
    }

    int getWidth() const noexcept
    {
        return _width;
    }

    int getHeight() const noexcept
    {
        return _height;
    }

    bool hasAlpha() const noexcept
    {
        return _alpha;
    }

    const RectI& getRect() const noexcept
    {
        return _rect;
    }

    RectF getNormalizedRect() const noexcept;

    bool operator==(const TextureRegion& other) const noexcept
    {
        return _id == other._id && _rect == other._rect;
    }

    bool operator!=(const TextureRegion& other) const noexcept
    {
        return ! (*this == other);
    }

private:
    RectI _rect;
    std::size_t _id;
    int _width;
    int _height;
    bool _alpha;
};

}

#endif
