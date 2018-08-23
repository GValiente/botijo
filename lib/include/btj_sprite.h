/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_SPRITE_H
#define BTJ_SPRITE_H

#include <array>
#include "btj_optional.h"
#include "btj_constants.h"

namespace btj
{

class SizeI;
class SizeF;
class Color;
class Sprites;
class PositionF;
enum class Flip;

class Sprite
{

public:
    ~Sprite() noexcept;

    Sprite(Sprite&& other) noexcept;

    Sprite& operator=(Sprite&& other) noexcept;

    PositionF getPosition() const noexcept;

    void setPosition(const PositionF& PositionF) noexcept;

    SizeI getSize() const noexcept;

    void setSize(const SizeI& size) noexcept;

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

    Color getColor() const noexcept;

    void setColor(const Color& color) noexcept;

    std::array<Color, 4> getColors() const noexcept;

    void setColors(const std::array<Color, 4>& colors) noexcept;

    int getZOrder() const noexcept;

    void setZOrder(int zOrder) noexcept;

    bool isVisible() const noexcept;

    void setVisible(bool visible) noexcept;

private:
    friend class Sprites;

    Optional<std::size_t> _layerId;
    std::size_t _spriteId;

    Sprite(const Optional<std::size_t>& layerId, std::size_t spriteId) noexcept;

    const Sprites& getSprites() const noexcept
    {
        return const_cast<Sprite&>(*this).getSprites();
    }

    Sprites& getSprites() noexcept;
};

}

#endif
