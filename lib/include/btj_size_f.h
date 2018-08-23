/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_SIZE_F_H
#define BTJ_SIZE_F_H

#include "btj_glm.h"
#include "btj_assert.h"
#include "btj_constants.h"

namespace btj
{

class SizeF
{

public:
    SizeF() noexcept :
        SizeF(0, 0)
    {
    }

    SizeF(float width, float height) noexcept
    {
        setWidth(width);
        setHeight(height);
    }

    const Vec2& getVector() const noexcept
    {
        return _vector;
    }

    float getWidth() const noexcept
    {
        return _vector[0];
    }

    void setWidth(float width) noexcept
    {
        BTJ_ASSERT(width >= 0);

        _vector[0] = width;
    }

    float getHeight() const noexcept
    {
        return _vector[1];
    }

    void setHeight(float height) noexcept
    {
        BTJ_ASSERT(height >= 0);

        _vector[1] = height;
    }

    bool operator==(const SizeF& other) const noexcept
    {
        return equals(_vector, other._vector);
    }

    bool operator!=(const SizeF& other) const noexcept
    {
        return ! (*this == other);
    }

private:
    Vec2 _vector;
};

static_assert(std::is_nothrow_destructible<SizeF>::value, "");
static_assert(std::is_copy_constructible<SizeF>::value, "");
static_assert(std::is_copy_assignable<SizeF>::value, "");
static_assert(std::is_nothrow_move_constructible<SizeF>::value, "");
static_assert(std::is_nothrow_move_assignable<SizeF>::value, "");

}

#endif
