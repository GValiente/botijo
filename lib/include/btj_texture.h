/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_TEXTURE_H
#define BTJ_TEXTURE_H

#include <cstddef>
#include "btj_optional.h"

namespace btj
{

class TextureInfo;

class Texture
{

public:
    ~Texture() noexcept;

    Texture(Texture&& other) noexcept;

    Texture& operator=(Texture&& other) noexcept;

    std::size_t getId() const noexcept;

    int getWidth() const noexcept;

    int getHeight() const noexcept;

    bool hasAlpha() const noexcept;

private:
    friend class Textures;
    friend class TextureRegion;

    Optional<std::size_t> _id;

    explicit Texture(const Optional<std::size_t>& id) noexcept;

    TextureInfo getTextureInfo() const noexcept;
};

}

#endif
