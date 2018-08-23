/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_GLM_H
#define BTJ_GLM_H

#define GLM_PRECISION_MEDIUMP_FLOAT
#define GLM_FORCE_EXPLICIT_CTOR
#include "glm/common.hpp"
#include "glm/gtc/epsilon.hpp"
#include "glm/gtc/type_aligned.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "btj_constants.h"

namespace btj
{
    using Vec2 = glm::aligned_vec2;
    using Vec3 = glm::aligned_vec3;
    using Vec4 = glm::aligned_vec4;
    using Mat44 = glm::mat<4, 4, float, glm::aligned_mediump>;

    static bool equals(float a, float b) noexcept
    {
        return std::abs(a - b) < epsilon;
    }

    static bool equals(const Vec2& a, const Vec2& b) noexcept
    {
        return glm::all(glm::epsilonEqual(a, b, epsilon));
    }

    static bool equals(const Vec3& a, const Vec3& b) noexcept
    {
        return glm::all(glm::epsilonEqual(a, b, epsilon));
    }

    static bool equals(const Vec4& a, const Vec4& b) noexcept
    {
        return glm::all(glm::epsilonEqual(a, b, epsilon));
    }

    static bool equals(const Mat44& a, const Mat44& b) noexcept
    {
        return equals(a[0], b[0]) && equals(a[1], b[1]) && equals(a[2], b[2]) && equals(a[3], b[3]);
    }
}

#endif
