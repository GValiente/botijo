/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_texture.h"

#include "btj_textures.h"
#include "btj_global_pointers.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<Texture>::value, "");
static_assert(! std::is_copy_constructible<Texture>::value, "");
static_assert(! std::is_copy_assignable<Texture>::value, "");
static_assert(std::is_nothrow_move_constructible<Texture>::value, "");
static_assert(std::is_nothrow_move_assignable<Texture>::value, "");

Texture::~Texture() noexcept
{
    if(_id)
    {
        gb.textures->destroy(*_id);
        _id.reset();
    }
}

Texture::Texture(Texture&& other) noexcept :
    Texture(Optional<std::size_t>())
{
    *this = std::move(other);
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    std::swap(_id, other._id);
    return *this;
}

std::size_t Texture::getId() const noexcept
{
    return getTextureInfo().graphics.getId();
}

int Texture::getWidth() const noexcept
{
    return getTextureInfo().width;
}

int Texture::getHeight() const noexcept
{
    return getTextureInfo().height;
}

bool Texture::hasAlpha() const noexcept
{
    return getTextureInfo().alpha;
}

TextureInfo Texture::getTextureInfo() const noexcept
{
    return gb.textures->getTextureInfo(*_id);
}

Texture::Texture(const Optional<std::size_t>& id) noexcept :
    _id(id)
{
}

}
