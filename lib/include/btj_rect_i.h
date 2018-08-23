/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_RECT_I_H
#define BTJ_RECT_I_H

#include "btj_size_i.h"
#include "btj_position_i.h"

namespace btj
{

class RectI
{

public:
    PositionI position;
    SizeI size;

    RectI() = default;

    RectI(const PositionI& _position, const SizeI& _size) noexcept :
        position(_position),
        size(_size)
    {
    }

    RectI(int x, int y, int width, int height) noexcept :
        position(x, y),
        size(width, height)
    {
    }

    PositionI getTopLeftCorner() const noexcept
    {
        return position;
    }

    PositionI getTopRightCorner() const noexcept
    {
        return PositionI(position.getX() + size.getWidth(), position.getY());
    }

    PositionI getBottomLeftCorner() const noexcept
    {
        return PositionI(position.getX(), position.getY() + size.getHeight());
    }

    PositionI getBottomRightCorner() const noexcept
    {
        return PositionI(position.getX() + size.getWidth(), position.getY() + size.getHeight());
    }

    bool operator==(const RectI& other) const noexcept
    {
        return position == other.position && size == other.size;
    }

    bool operator!=(const RectI& other) const noexcept
    {
        return ! (*this == other);
    }
};

static_assert(std::is_nothrow_destructible<RectI>::value, "");
static_assert(std::is_copy_constructible<RectI>::value, "");
static_assert(std::is_copy_assignable<RectI>::value, "");
static_assert(std::is_nothrow_move_constructible<RectI>::value, "");
static_assert(std::is_nothrow_move_assignable<RectI>::value, "");

}

#endif
