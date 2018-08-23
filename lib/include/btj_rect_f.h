/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_RECT_F_H
#define BTJ_RECT_F_H

#include "btj_size_f.h"
#include "btj_position_f.h"

namespace btj
{

class RectF
{

public:
    PositionF position;
    SizeF size;

    RectF() = default;

    RectF(const PositionF& _position, const SizeF& _size) noexcept :
        position(_position),
        size(_size)
    {
    }

    RectF(float x, float y, float width, float height) noexcept :
        position(x, y),
        size(width, height)
    {
    }

    PositionF getTopLeftCorner() const noexcept
    {
        return position;
    }

    PositionF getTopRightCorner() const noexcept
    {
        return PositionF(position.getX() + size.getWidth(), position.getY());
    }

    PositionF getBottomLeftCorner() const noexcept
    {
        return PositionF(position.getX(), position.getY() + size.getHeight());
    }

    PositionF getBottomRightCorner() const noexcept
    {
        return PositionF(position.getX() + size.getWidth(), position.getY() + size.getHeight());
    }

    bool operator==(const RectF& other) const noexcept
    {
        return position == other.position && size == other.size;
    }

    bool operator!=(const RectF& other) const noexcept
    {
        return ! (*this == other);
    }
};

static_assert(std::is_nothrow_destructible<RectF>::value, "");
static_assert(std::is_copy_constructible<RectF>::value, "");
static_assert(std::is_copy_assignable<RectF>::value, "");
static_assert(std::is_nothrow_move_constructible<RectF>::value, "");
static_assert(std::is_nothrow_move_assignable<RectF>::value, "");

}

#endif
