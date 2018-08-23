/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_TEXTURE_GRAPHICS_H
#define BTJ_TEXTURE_GRAPHICS_H

#include <limits>

namespace btj
{

class TextureGraphics
{

public:
    TextureGraphics() noexcept :
        TextureGraphics(std::numeric_limits<std::size_t>::max())
    {
    }

    explicit TextureGraphics(std::size_t id) noexcept :
        _id(id)
    {
    }

    std::size_t getId() const noexcept
    {
        return _id;
    }

    bool operator==(const TextureGraphics& other) const noexcept
    {
        return _id == other._id;
    }

    bool operator!=(const TextureGraphics& other) const noexcept
    {
        return ! (*this == other);
    }

    bool operator<(const TextureGraphics& other) const noexcept
    {
        return _id < other._id;
    }

private:
    std::size_t _id = 0;
};

}

#endif
