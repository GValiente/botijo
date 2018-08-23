/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_layer.h"

#include "btj_sprite.h"
#include "btj_layers.h"
#include "btj_textures.h"
#include "btj_global_pointers.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<Layer>::value, "");
static_assert(! std::is_copy_constructible<Layer>::value, "");
static_assert(! std::is_copy_assignable<Layer>::value, "");
static_assert(std::is_nothrow_move_constructible<Layer>::value, "");
static_assert(std::is_nothrow_move_assignable<Layer>::value, "");

Layer::~Layer() noexcept
{
    if(_id)
    {
        gb.layers->destroy(*_id);
        _id.reset();
    }
}

Layer::Layer(Layer&& other) noexcept :
    Layer(Optional<std::size_t>())
{
    *this = std::move(other);
}

Layer& Layer::operator=(Layer&& other) noexcept
{
    std::swap(_id, other._id);
    return *this;
}

PositionF Layer::getPosition() const noexcept
{
    return gb.layers->getPosition(*_id);
}

void Layer::setPosition(const PositionF& position) noexcept
{
    gb.layers->setPosition(*_id, position);
}

SizeF Layer::getScale() const noexcept
{
    return gb.layers->getScale(*_id);
}

void Layer::setScale(const SizeF& scale) noexcept
{
    gb.layers->setScale(*_id, scale);
}

float Layer::getRotationRadians() const noexcept
{
    return gb.layers->getRotation(*_id);
}

void Layer::setRotationRadians(float radians) noexcept
{
    gb.layers->setRotation(*_id, radians);
}

PositionF Layer::getShear() const noexcept
{
    return gb.layers->getShear(*_id);
}

void Layer::setShear(const PositionF& shear) noexcept
{
    gb.layers->setShear(*_id, shear);
}

Flip Layer::getFlip() const noexcept
{
    return gb.layers->getFlip(*_id);
}

void Layer::setFlip(Flip flip) noexcept
{
    gb.layers->setFlip(*_id, flip);
}

int Layer::getZOrder() const noexcept
{
    return gb.layers->getZOrder(*_id);
}

void Layer::setZOrder(int zOrder) noexcept
{
    gb.layers->setZOrder(*_id, zOrder);
}

bool Layer::isVisible() const noexcept
{
    return gb.layers->isVisible(*_id);
}

void Layer::setVisible(bool visible) noexcept
{
    gb.layers->setVisible(*_id, visible);
}

void Layer::reserveSprites(std::size_t count)
{
    gb.layers->getSprites(*_id).reserve(count);
}

Sprite Layer::createSprite(const SizeI& size, int zOrder)
{
    TextureRegion dummyTextureRegion(gb.textures->getDummyTexture());
    return gb.layers->getSprites(*_id).createSprite(*_id, size, dummyTextureRegion, zOrder);
}

Sprite Layer::createSprite(const TextureRegion& textureRegion, int zOrder)
{
    SizeI size = textureRegion.getRect().size;
    return gb.layers->getSprites(*_id).createSprite(*_id, size, textureRegion, zOrder);
}

Sprite Layer::createSprite(const Texture& texture, int zOrder)
{
    return createSprite(TextureRegion(texture), zOrder);
}

Layer::Layer(const Optional<std::size_t>& id) noexcept :
    _id(id)
{
}

}
