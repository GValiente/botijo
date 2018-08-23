/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_SIZE_I_H
#define BTJ_SIZE_I_H

#include <type_traits>
#include "btj_assert.h"

namespace btj
{

class SizeI
{

public:
    SizeI() noexcept :
        SizeI(0, 0)
    {
    }

    SizeI(int width, int height) noexcept
    {
        setWidth(width);
        setHeight(height);
    }

    int getWidth() const noexcept
    {
        return _width;
    }

    void setWidth(int width) noexcept
    {
        BTJ_ASSERT(width >= 0);

        _width = width;
    }

    int getHeight() const noexcept
    {
        return _height;
    }

    void setHeight(int height) noexcept
    {
        BTJ_ASSERT(height >= 0);

        _height = height;
    }

    bool operator==(const SizeI& other) const noexcept
    {
        return _width == other._width && _height == other._height;
    }

    bool operator!=(const SizeI& other) const noexcept
    {
        return ! (*this == other);
    }

private:
    int _width;
    int _height;
};

static_assert(std::is_nothrow_destructible<SizeI>::value, "");
static_assert(std::is_copy_constructible<SizeI>::value, "");
static_assert(std::is_copy_assignable<SizeI>::value, "");
static_assert(std::is_nothrow_move_constructible<SizeI>::value, "");
static_assert(std::is_nothrow_move_assignable<SizeI>::value, "");

}

#endif
