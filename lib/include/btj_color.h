/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_COLOR_H
#define BTJ_COLOR_H

#include "btj_glm.h"
#include "btj_assert.h"
#include "btj_constants.h"

namespace btj
{

class Color
{

public:
    Color() noexcept :
        _vector(0, 0, 0, 1)
    {
    }

    Color(float r, float g, float b, float a = 1) noexcept
    {
        setR(r);
        setG(g);
        setB(b);
        setA(a);
    }

    const Vec4& getVector() const noexcept
    {
        return _vector;
    }

    float getR() const noexcept
    {
        return _vector[0];
    }

    void setR(float r) noexcept
    {
        BTJ_ASSERT(r >= 0 && r <= 1);

        _vector[0] = r;
    }

    float getG() const noexcept
    {
        return _vector[1];
    }

    void setG(float g) noexcept
    {
        BTJ_ASSERT(g >= 0 && g <= 1);

        _vector[1] = g;
    }

    float getB() const noexcept
    {
        return _vector[2];
    }

    void setB(float b) noexcept
    {
        BTJ_ASSERT(b >= 0 && b <= 1);

        _vector[2] = b;
    }

    float getA() const noexcept
    {
        return _vector[3];
    }

    void setA(float a) noexcept
    {
        BTJ_ASSERT(a >= 0 && a <= 1);

        _vector[3] = a;
    }

    bool operator==(const Color& other) const noexcept
    {
        return equals(_vector, other._vector);
    }

    bool operator!=(const Color& other) const noexcept
    {
        return ! (*this == other);
    }

private:
    Vec4 _vector;
};

static_assert(std::is_nothrow_destructible<Color>::value, "");
static_assert(std::is_copy_constructible<Color>::value, "");
static_assert(std::is_copy_assignable<Color>::value, "");
static_assert(std::is_nothrow_move_constructible<Color>::value, "");
static_assert(std::is_nothrow_move_assignable<Color>::value, "");

}

#endif
