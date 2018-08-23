/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_texture_region.h"

#include "btj_rect_f.h"
#include "btj_texture.h"
#include "btj_texture_info.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<TextureRegion>::value, "");
static_assert(std::is_copy_constructible<TextureRegion>::value, "");
static_assert(std::is_copy_assignable<TextureRegion>::value, "");
static_assert(std::is_nothrow_move_constructible<TextureRegion>::value, "");
static_assert(std::is_nothrow_move_assignable<TextureRegion>::value, "");

TextureRegion::TextureRegion(const Texture& texture) noexcept
{
    auto textureInfo = texture.getTextureInfo();
    _id = textureInfo.graphics.getId();
    _width = textureInfo.width;
    _height = textureInfo.height;
    _alpha = textureInfo.alpha;
    _rect = RectI(0, 0, textureInfo.width, textureInfo.height);
}

TextureRegion::TextureRegion(const Texture& texture, const RectI& rect) noexcept :
    _rect(rect)
{
    auto textureInfo = texture.getTextureInfo();
    _id = textureInfo.graphics.getId();
    _width = textureInfo.width;
    _height = textureInfo.height;
    _alpha = textureInfo.alpha;

    BTJ_ASSERT(_rect.position.getX() >= 0);
    BTJ_ASSERT(_rect.position.getX() + _rect.size.getWidth() <= _width);
    BTJ_ASSERT(_rect.position.getY() >= 0);
    BTJ_ASSERT(_rect.position.getY() + _rect.size.getHeight() <= _height);
}

RectF TextureRegion::getNormalizedRect() const noexcept
{
    auto x = _rect.position.getX();
    auto y = _rect.position.getY();
    auto w = _rect.size.getWidth();
    auto h = _rect.size.getHeight();
    auto widthInv = 1 / float(_width);
    auto heightInv = 1 / float(_height);
    return RectF(x * widthInv, y * heightInv, w * widthInv, h * heightInv);
}

}
