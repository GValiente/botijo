/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_ROTATION_H
#define BTJ_ROTATION_H

#include "btj_glm.h"

namespace btj
{

class Rotation
{

public:
    explicit Rotation(float angle) noexcept :
        _angle(angle),
        _negCos(std::cos(-angle)),
        _negSin(std::sin(-angle))
    {
    }

    float getAngle() const noexcept
    {
        return _angle;
    }

    float getNegCos() const noexcept
    {
        return _negCos;
    }

    float getNegSin() const noexcept
    {
        return _negSin;
    }

    Mat44 getTransform() const noexcept
    {
        Mat44 transform(1);
        transform[0][0] = _negCos;
        transform[0][1] = _negSin;
        transform[1][0] = -_negSin;
        transform[1][1] = _negCos;
        return transform;
    }

private:
    float _angle;
    float _negCos;
    float _negSin;
};

}

#endif
