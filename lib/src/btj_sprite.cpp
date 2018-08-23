/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_sprite.h"

#include "btj_layers.h"
#include "btj_sprites.h"
#include "btj_global_pointers.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<Sprite>::value, "");
static_assert(! std::is_copy_constructible<Sprite>::value, "");
static_assert(! std::is_copy_assignable<Sprite>::value, "");
static_assert(std::is_nothrow_move_constructible<Sprite>::value, "");
static_assert(std::is_nothrow_move_assignable<Sprite>::value, "");

Sprite::~Sprite() noexcept
{
    if(_layerId)
    {
        getSprites().destroy(_spriteId);
        _layerId.reset();
    }
}

Sprite::Sprite(Sprite&& other) noexcept :
    Sprite(Optional<std::size_t>(), 0)
{
    *this = std::move(other);
}

Sprite& Sprite::operator=(Sprite&& other) noexcept
{
    std::swap(_layerId, other._layerId);
    std::swap(_spriteId, other._spriteId);
    return *this;
}

PositionF Sprite::getPosition() const noexcept
{
    return getSprites().getPosition(_spriteId);
}

void Sprite::setPosition(const PositionF& position) noexcept
{
    getSprites().setPosition(_spriteId, position);
}

SizeI Sprite::getSize() const noexcept
{
    return getSprites().getSize(_spriteId);
}

void Sprite::setSize(const SizeI& size) noexcept
{
    getSprites().setSize(_spriteId, size);
}

SizeF Sprite::getScale() const noexcept
{
    return getSprites().getScale(_spriteId);
}

void Sprite::setScale(const SizeF& scale) noexcept
{
    getSprites().setScale(_spriteId, scale);
}

float Sprite::getRotationRadians() const noexcept
{
    return getSprites().getRotation(_spriteId);
}

void Sprite::setRotationRadians(float radians) noexcept
{
    getSprites().setRotation(_spriteId, radians);
}

PositionF Sprite::getShear() const noexcept
{
    return getSprites().getShear(_spriteId);
}

void Sprite::setShear(const PositionF& shear) noexcept
{
    getSprites().setShear(_spriteId, shear);
}

Flip Sprite::getFlip() const noexcept
{
    return getSprites().getFlip(_spriteId);
}

void Sprite::setFlip(Flip flip) noexcept
{
    getSprites().setFlip(_spriteId, flip);
}

Color Sprite::getColor() const noexcept
{
    return getSprites().getColor(_spriteId);
}

void Sprite::setColor(const Color& color) noexcept
{
    getSprites().setColor(_spriteId, color);
}

std::array<Color, 4> Sprite::getColors() const noexcept
{
    return getSprites().getColors(_spriteId);
}

void Sprite::setColors(const std::array<Color, 4>& colors) noexcept
{
    getSprites().setColors(_spriteId, colors);
}

int Sprite::getZOrder() const noexcept
{
    return getSprites().getZOrder(_spriteId);
}

void Sprite::setZOrder(int zOrder) noexcept
{
    getSprites().setZOrder(_spriteId, zOrder);
}

bool Sprite::isVisible() const noexcept
{
    return getSprites().isVisible(_spriteId);
}

void Sprite::setVisible(bool visible) noexcept
{
    getSprites().setVisible(_spriteId, visible);
}

Sprite::Sprite(const Optional<std::size_t>& layerId, std::size_t spriteId) noexcept :
    _layerId(layerId),
    _spriteId(spriteId)
{
}

Sprites& Sprite::getSprites() noexcept
{
    return gb.layers->getSprites(*_layerId);
}

}
