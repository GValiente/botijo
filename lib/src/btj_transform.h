/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_TRANSFORM_H
#define BTJ_TRANSFORM_H

#include "btj_flip.h"
#include "btj_size_f.h"
#include "btj_position_f.h"
#include "btj_rotation.h"

namespace btj
{

static Mat44 getTranslationTransform(const PositionF& position) noexcept
{
    Mat44 transform(1);
    transform[3][0] = position.getX();
    transform[3][1] = position.getY();
    return transform;
}

static Mat44 getScaleTransform(const SizeF& scale, Flip flip) noexcept
{
    Mat44 transform(1);
    transform[0][0] = scale.getWidth() * (flip == Flip::HORIZONTAL || flip == Flip::BOTH ? -1 : 1);
    transform[1][1] = scale.getHeight() * (flip == Flip::VERTICAL || flip == Flip::BOTH ? -1 : 1);
    return transform;
}

static Mat44 getShearTransform(const PositionF& shear) noexcept
{
    Mat44 transform(1);
    transform[0][1] = shear.getY();
    transform[1][0] = shear.getX();
    return transform;
}

static Mat44 getTransform(const PositionF& position, const Rotation& rotation, const PositionF& shear,
                          const SizeF& scale, Flip flip) noexcept
{
    return getTranslationTransform(position) * rotation.getTransform() * getShearTransform(shear) *
            getScaleTransform(scale, flip);
}

}

#endif
