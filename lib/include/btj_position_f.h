/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_POSITION_F_H
#define BTJ_POSITION_F_H

#include "btj_glm.h"
#include "btj_constants.h"

namespace btj
{

class PositionF
{

public:
    PositionF() noexcept :
        _vector(0, 0)
    {
    }

    PositionF(float x, float y) noexcept :
        _vector(x, y)
    {
    }

    const Vec2& getVector() const noexcept
    {
        return _vector;
    }

    float getX() const noexcept
    {
        return _vector[0];
    }

    void setX(float x) noexcept
    {
        _vector[0] = x;
    }

    float getY() const noexcept
    {
        return _vector[1];
    }

    void setY(float y) noexcept
    {
        _vector[1] = y;
    }

    bool operator==(const PositionF& other) const noexcept
    {
        return equals(_vector, other._vector);
    }

    bool operator!=(const PositionF& other) const noexcept
    {
        return ! (*this == other);
    }

    PositionF& operator+=(const PositionF& other) noexcept
    {
        _vector += other._vector;
        return *this;
    }

    friend PositionF operator+(PositionF a, const PositionF& b)
    {
        a += b;
        return a;
    }

    PositionF& operator-=(const PositionF& other) noexcept
    {
        _vector -= other._vector;
        return *this;
    }

    friend PositionF operator-(PositionF a, const PositionF& b)
    {
        a -= b;
        return a;
    }

private:
    Vec2 _vector;
};

static_assert(std::is_nothrow_destructible<PositionF>::value, "");
static_assert(std::is_copy_constructible<PositionF>::value, "");
static_assert(std::is_copy_assignable<PositionF>::value, "");
static_assert(std::is_nothrow_move_constructible<PositionF>::value, "");
static_assert(std::is_nothrow_move_assignable<PositionF>::value, "");

}

#endif
