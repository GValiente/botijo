/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_POSITION_I_H
#define BTJ_POSITION_I_H

#include <type_traits>

namespace btj
{

class PositionI
{

public:
    PositionI() noexcept :
        PositionI(0, 0)
    {
    }

    PositionI(int x, int y) noexcept :
        _x(x),
        _y(y)
    {
    }

    int getX() const noexcept
    {
        return _x;
    }

    void setX(int x) noexcept
    {
        _x = x;
    }

    int getY() const noexcept
    {
        return _y;
    }

    void setY(int y) noexcept
    {
        _y = y;
    }

    bool operator==(const PositionI& other) const noexcept
    {
        return _x == other._x && _y == other._y;
    }

    bool operator!=(const PositionI& other) const noexcept
    {
        return ! (*this == other);
    }

    PositionI& operator+=(const PositionI& other) noexcept
    {
        _x += other._x;
        _y += other._y;
        return *this;
    }

    friend PositionI operator+(PositionI a, const PositionI& b)
    {
        a += b;
        return a;
    }

    PositionI& operator-=(const PositionI& other) noexcept
    {
        _x -= other._x;
        _y -= other._y;
        return *this;
    }

    friend PositionI operator-(PositionI a, const PositionI& b)
    {
        a -= b;
        return a;
    }

private:
    int _x;
    int _y;
};

static_assert(std::is_nothrow_destructible<PositionI>::value, "");
static_assert(std::is_copy_constructible<PositionI>::value, "");
static_assert(std::is_copy_assignable<PositionI>::value, "");
static_assert(std::is_nothrow_move_constructible<PositionI>::value, "");
static_assert(std::is_nothrow_move_assignable<PositionI>::value, "");

}

#endif
