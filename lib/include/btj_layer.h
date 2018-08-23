/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_LAYER_H
#define BTJ_LAYER_H

#include <cstddef>
#include "btj_optional.h"
#include "btj_constants.h"

namespace btj
{

class SizeI;
class SizeF;
class Sprite;
class PositionF;
class Texture;
class TextureRegion;
enum class Flip;

class Layer
{

public:
    ~Layer() noexcept;

    Layer(Layer&& other) noexcept;

    Layer& operator=(Layer&& other) noexcept;

    PositionF getPosition() const noexcept;

    void setPosition(const PositionF& PositionF) noexcept;

    SizeF getScale() const noexcept;

    void setScale(const SizeF& scale) noexcept;

    float getRotationDegrees() const noexcept
    {
        return getRotationRadians() * (180 / pi);
    }

    void setRotationDegrees(float degrees) noexcept
    {
        setRotationRadians(degrees * (pi / 180));
    }

    float getRotationRadians() const noexcept;

    void setRotationRadians(float radians) noexcept;

    PositionF getShear() const noexcept;

    void setShear(const PositionF& shear) noexcept;

    Flip getFlip() const noexcept;

    void setFlip(Flip flip) noexcept;

    int getZOrder() const noexcept;

    void setZOrder(int zOrder) noexcept;

    bool isVisible() const noexcept;

    void setVisible(bool visible) noexcept;

    void reserveSprites(std::size_t count);

    Sprite createSprite(const SizeI& size, int zOrder = 0);

    Sprite createSprite(const TextureRegion& textureRegion, int zOrder = 0);

    Sprite createSprite(const Texture& texture, int zOrder = 0);

private:
    friend class Layers;

    Optional<std::size_t> _id;

    explicit Layer(const Optional<std::size_t>& id) noexcept;
};

}

#endif
