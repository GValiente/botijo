/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_sprites.h"

#include "btj_rect_f.h"
#include "btj_sprite.h"
#include "btj_assert.h"
#include "btj_logger.h"
#include "btj_transform.h"
#include "btj_quicksort.h"
#include "btj_graphics_impl.h"
#include "btj_global_pointers.h"
#include "btj_sort_info_comparator.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<Sprites>::value, "");
static_assert(std::is_copy_constructible<Sprites>::value, "");
static_assert(std::is_copy_assignable<Sprites>::value, "");
static_assert(std::is_nothrow_move_constructible<Sprites>::value, "");
static_assert(std::is_nothrow_move_assignable<Sprites>::value, "");

class Sprites::Swap
{

public:
    Sprites& sprites;

    void operator()(std::size_t a, std::size_t b) noexcept
    {
        std::swap(sprites._indexes[a], sprites._indexes[b]);
        std::swap(sprites._positions[a], sprites._positions[b]);
        std::swap(sprites._sizes[a], sprites._sizes[b]);
        std::swap(sprites._textureRegions[a], sprites._textureRegions[b]);
        std::swap(sprites._scales[a], sprites._scales[b]);
        std::swap(sprites._rotations[a], sprites._rotations[b]);
        std::swap(sprites._shears[a], sprites._shears[b]);
        std::swap(sprites._flips[a], sprites._flips[b]);
        std::swap(sprites._sortInfos[a], sprites._sortInfos[b]);

        auto a4 = a * 4;
        auto b4 = b * 4;
        std::swap(sprites._cornerPositions[a4], sprites._cornerPositions[b4]);
        std::swap(sprites._cornerPositions[a4 + 1], sprites._cornerPositions[b4 + 1]);
        std::swap(sprites._cornerPositions[a4 + 2], sprites._cornerPositions[b4 + 2]);
        std::swap(sprites._cornerPositions[a4 + 3], sprites._cornerPositions[b4 + 3]);
        std::swap(sprites._cornerColors[a4], sprites._cornerColors[b4]);
        std::swap(sprites._cornerColors[a4 + 1], sprites._cornerColors[b4 + 1]);
        std::swap(sprites._cornerColors[a4 + 2], sprites._cornerColors[b4 + 2]);
        std::swap(sprites._cornerColors[a4 + 3], sprites._cornerColors[b4 + 3]);
        std::swap(sprites._cornerTextureCoords[a4], sprites._cornerTextureCoords[b4]);
        std::swap(sprites._cornerTextureCoords[a4 + 1], sprites._cornerTextureCoords[b4 + 1]);
        std::swap(sprites._cornerTextureCoords[a4 + 2], sprites._cornerTextureCoords[b4 + 2]);
        std::swap(sprites._cornerTextureCoords[a4 + 3], sprites._cornerTextureCoords[b4 + 3]);
    }
};

Sprites::SortInfo Sprites::SortInfo::invalid() noexcept
{
    return SortInfo(TextureGraphics(), std::numeric_limits<int>::max(), std::numeric_limits<char>::max(),
                    std::numeric_limits<char>::max(), std::numeric_limits<char>::max());
}

Sprites::SortInfo::SortInfo(const TextureGraphics& _textureGraphics, int _zOrder, char _alpha, char _hidden,
                            char _outOfScreen) noexcept :
    textureGraphics(_textureGraphics),
    zOrder(_zOrder),
    alpha(_alpha),
    hidden(_hidden),
    outOfScreen(_outOfScreen)
{
}

bool Sprites::SortInfo::operator<(const SortInfo& other) const noexcept
{
    if(hidden == other.hidden)
    {
        if(zOrder == other.zOrder)
        {
            if(alpha == other.alpha)
            {
                return textureGraphics < other.textureGraphics;
            }

            return alpha < other.alpha;
        }

        return zOrder < other.zOrder;
    }

    return hidden < other.hidden;
}

Sprites::Sprites() noexcept :
    _newIndex(0),
    _sort(false),
    _updatePositions(false),
    _updateColors(false),
    _updateTextureCoords(false)
{
}

void Sprites::clear() noexcept
{
    if(! _sortInfos.empty())
    {
        for(SortInfo& sortInfo : _sortInfos)
        {
            sortInfo = SortInfo::invalid();
        }

        _updateAll();
    }
}

void Sprites::reserve(std::size_t count)
{
    _indexes.reserve(count);
    _positions.reserve(count);
    _sizes.reserve(count);
    _textureRegions.reserve(count);
    _scales.reserve(count);
    _rotations.reserve(count);
    _shears.reserve(count);
    _flips.reserve(count);
    _cornerPositions.reserve(count * 4);
    _cornerColors.reserve(count * 4);
    _cornerTextureCoords.reserve(count * 4);
    _sortInfos.reserve(count);
}

Sprite Sprites::createSprite(std::size_t layerId, const SizeI& size, const TextureRegion& textureRegion, int zOrder)
{
    return Sprite(layerId, create(size, textureRegion, zOrder));
}

std::size_t Sprites::create(const SizeI& size, const TextureRegion& textureRegion, int zOrder)
{
    auto textureRect = textureRegion.getNormalizedRect();
    auto newIndex = _newIndex;
    std::size_t newId;

    if(newIndex == _indexes.size())
    {
        _indexes.push_back(newIndex);
        _positions.push_back(PositionF());
        _sizes.push_back(size);
        _textureRegions.push_back(textureRegion);
        _scales.push_back(SizeF(1, 1));
        _rotations.push_back(Rotation(0));
        _shears.push_back(PositionF());
        _flips.push_back(Flip());
        _cornerPositions.push_back(PositionF());
        _cornerPositions.push_back(PositionF());
        _cornerPositions.push_back(PositionF());
        _cornerPositions.push_back(PositionF());
        _cornerColors.push_back(Color(1, 1, 1));
        _cornerColors.push_back(Color(1, 1, 1));
        _cornerColors.push_back(Color(1, 1, 1));
        _cornerColors.push_back(Color(1, 1, 1));
        _cornerTextureCoords.push_back(textureRect.getTopLeftCorner());
        _cornerTextureCoords.push_back(textureRect.getTopRightCorner());
        _cornerTextureCoords.push_back(textureRect.getBottomRightCorner());
        _cornerTextureCoords.push_back(textureRect.getBottomLeftCorner());
        _sortInfos.push_back(SortInfo(TextureGraphics(textureRegion.getId()), zOrder));
        newId = _newIndex;
    }
    else
    {
        auto newIndex4 = newIndex * 4;
        _positions[newIndex] = PositionF();
        _sizes[newIndex] = size;
        _textureRegions[newIndex] = textureRegion;
        _scales[newIndex] = SizeF(1, 1);
        _rotations[newIndex] = Rotation(0);
        _shears[newIndex] = PositionF();
        _flips[newIndex] = Flip();
        _cornerPositions[newIndex4] = PositionF();
        _cornerPositions[newIndex4 + 1] = PositionF();
        _cornerPositions[newIndex4 + 2] = PositionF();
        _cornerPositions[newIndex4 + 3] = PositionF();
        _cornerColors[newIndex4] = Color(1, 1, 1);
        _cornerColors[newIndex4 + 1] = Color(1, 1, 1);
        _cornerColors[newIndex4 + 2] = Color(1, 1, 1);
        _cornerColors[newIndex4 + 3] = Color(1, 1, 1);
        _cornerTextureCoords[newIndex4] = textureRect.getTopLeftCorner();
        _cornerTextureCoords[newIndex4 + 1] = textureRect.getTopRightCorner();
        _cornerTextureCoords[newIndex4 + 2] = textureRect.getBottomRightCorner();
        _cornerTextureCoords[newIndex4 + 3] = textureRect.getBottomLeftCorner();
        _sortInfos[newIndex] = SortInfo(TextureGraphics(textureRegion.getId()), zOrder);
        newId = _indexes[newIndex];
    }

    _sortInfos[newIndex].alpha = _getAlphaType(newIndex);
    ++_newIndex;
    _updateAll();
    return newId;
}

void Sprites::destroy(std::size_t id) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    _sortInfos[index] = SortInfo::invalid();
    _updateAll();
}

SizeI Sprites::getSize(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _sizes[index];
}

void Sprites::setSize(std::size_t id, const SizeI& size) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];

    if(_sizes[index] != size)
    {
        _sizes[index] = size;
        _updatePositions = true;
    }
}

TextureRegion Sprites::getTextureRegion(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _textureRegions[index];
}

void Sprites::setTextureRegion(std::size_t id, const TextureRegion& textureRegion) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];

    if(_textureRegions[index] != textureRegion)
    {
        if(_textureRegions[index].getId() != textureRegion.getId() ||
                _textureRegions[index].hasAlpha() != textureRegion.hasAlpha())
        {
            _sort = true;
        }

        auto textureRect = textureRegion.getNormalizedRect();
        auto index4 = index * 4;
        _cornerTextureCoords[index4] = textureRect.getTopLeftCorner();
        _cornerTextureCoords[index4 + 1] = textureRect.getTopRightCorner();
        _cornerTextureCoords[index4 + 2] = textureRect.getBottomRightCorner();
        _cornerTextureCoords[index4 + 3] = textureRect.getBottomLeftCorner();
        _textureRegions[index] = textureRegion;
        _updateTextureCoords = true;
    }
}

PositionF Sprites::getPosition(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _positions[index];
}

void Sprites::setPosition(std::size_t id, const PositionF& position) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];

    if(_positions[index] != position)
    {
        _positions[index] = position;
        _updatePositions = true;
    }
}

SizeF Sprites::getScale(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _scales[index];
}

void Sprites::setScale(std::size_t id, const SizeF& scale) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];

    if(_scales[index] != scale)
    {
        _scales[index] = scale;
        _updatePositions = true;
    }
}

float Sprites::getRotation(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _rotations[index].getAngle();
}

void Sprites::setRotation(std::size_t id, float angle) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];

    if(! equals(_rotations[index].getAngle(), angle))
    {
        _rotations[index] = Rotation(angle);
        _updatePositions = true;
    }
}

PositionF Sprites::getShear(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _shears[index];
}

void Sprites::setShear(std::size_t id, const PositionF& shear) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];

    if(_shears[index] != shear)
    {
        _shears[index] = shear;
        _updatePositions = true;
    }
}

Flip Sprites::getFlip(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _flips[index];
}

void Sprites::setFlip(std::size_t id, Flip flip) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];

    if(_flips[index] != flip)
    {
        _flips[index] = flip;
        _updatePositions = true;
    }
}

Color Sprites::getColor(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _cornerColors[index * 4];
}

void Sprites::setColor(std::size_t id, const Color& color) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    auto index4 = index * 4;

    if(_cornerColors[index4] != color)
    {
        _cornerColors[index4] = color;
        _cornerColors[index4 + 1] = color;
        _cornerColors[index4 + 2] = color;
        _cornerColors[index4 + 3] = color;
        _updateColors = true;

        char alphaType = _getAlphaType(index);

        if(alphaType != _sortInfos[index].alpha)
        {
            _sortInfos[index].alpha = alphaType;
            _sort = true;
        }
    }
}

std::array<Color, 4> Sprites::getColors(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    auto index4 = index * 4;
    return { _cornerColors[index4], _cornerColors[index4 + 1], _cornerColors[index4 + 2], _cornerColors[index4 + 3] };
}

void Sprites::setColors(std::size_t id, const std::array<Color, 4>& colors) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    auto index4 = index * 4;
    Color& a = _cornerColors[index4];
    Color& b = _cornerColors[index4 + 1];
    Color& c = _cornerColors[index4 + 2];
    Color& d = _cornerColors[index4 + 3];

    if(a != colors[0] || b != colors[1] || c != colors[2] || d != colors[3])
    {
        a = colors[0];
        b = colors[1];
        c = colors[2];
        d = colors[3];

        char alphaType = _getAlphaType(index);
        _updateColors = true;

        if(alphaType != _sortInfos[index].alpha)
        {
            _sortInfos[index].alpha = alphaType;
            _sort = true;
        }
    }
}

int Sprites::getZOrder(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _sortInfos[index].zOrder;
}

void Sprites::setZOrder(std::size_t id, int zOrder) noexcept
{
    BTJ_ASSERT(id < _indexes.size());
    BTJ_ASSERT(zOrder != SortInfo::invalid().zOrder);

    auto index = _indexes[id];

    if(zOrder != _sortInfos[index].zOrder)
    {
        _sortInfos[index].zOrder = zOrder;
        _sort = true;
    }
}

bool Sprites::isVisible(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return ! _sortInfos[index].hidden;
}

void Sprites::setVisible(std::size_t id, bool visible) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    bool hidden = ! visible;

    if(hidden != bool(_sortInfos[index].hidden))
    {
        _sortInfos[index].hidden = hidden;
        _updateAll();
    }
}

namespace
{
    template<bool updatePositions, bool updateColors, bool updateTextureCoords>
    void uploadAndDrawSprites(std::size_t spriteGraphicsIndex, const TextureGraphics& textureGraphics, int alpha,
                              Vector<SpriteGraphics>& spriteGraphicsVector, Sprites::UpdateData& updateData)
    {
        auto* graphics = gb.graphics;

        if(spriteGraphicsIndex == spriteGraphicsVector.size())
        {
            spriteGraphicsVector.push_back(graphics->createSpriteGraphics());
        }

        SpriteGraphics& spriteGraphics = spriteGraphicsVector[spriteGraphicsIndex];
        spriteGraphics.publicData.textureGraphics = textureGraphics;
        spriteGraphics.publicData.alpha = alpha;
        graphics->bindSpriteGraphics(spriteGraphics);

        if(updatePositions)
        {
            spriteGraphics.publicData.numSprites = updateData.cornerPositions.size() / 4;
            graphics->uploadSpritePositions(spriteGraphics, updateData.cornerPositions);
        }

        if(updateColors)
        {
            spriteGraphics.publicData.numSprites = updateData.cornerColors.size() / 4;
            graphics->uploadSpriteColors(spriteGraphics, updateData.cornerColors);
        }

        if(updateTextureCoords)
        {
            spriteGraphics.publicData.numSprites = updateData.cornerTextureCoords.size() / 4;
            graphics->uploadSpriteTextureCoords(spriteGraphics, updateData.cornerTextureCoords);
        }

        graphics->drawSpriteGraphics(spriteGraphics);
        updateData.cornerPositions.clear();
        updateData.cornerColors.clear();
        updateData.cornerTextureCoords.clear();
    }

    template<bool updatePositions, bool updateColors, bool updateTextureCoords>
    bool uploadAndDrawData(std::size_t numVisibleSprites,
                           const Vector<PositionF>& cornerPositions,
                           const Vector<Color>& cornerColors,
                           const Vector<PositionF>& cornerTextureCoords,
                           const Vector<Sprites::SortInfo>& sortInfos,
                           Vector<SpriteGraphics>& spriteGraphicsVector,
                           Sprites::UpdateData& updateData)
    {
        std::size_t spriteIndex = numVisibleSprites;

        for(std::size_t index = 0; index < numVisibleSprites; ++index)
        {
            if(! sortInfos[index].outOfScreen)
            {
                spriteIndex = index;
                break;
            }
        }

        if(spriteIndex == numVisibleSprites)
        {
            return false;
        }

        std::size_t spriteGraphicsIndex = 0;
        auto& outputPositions = updateData.cornerPositions;
        auto& outputColors = updateData.cornerColors;
        auto& outputTextureCoords = updateData.cornerTextureCoords;
        auto textureGraphics = sortInfos[spriteIndex].textureGraphics;
        int alpha = sortInfos[spriteIndex].alpha;
        outputPositions.reserve((numVisibleSprites - spriteIndex) * 4);
        outputColors.reserve((numVisibleSprites - spriteIndex) * 4);
        outputTextureCoords.reserve((numVisibleSprites - spriteIndex) * 4);

        auto inputPositionsIt = cornerPositions.begin() + long(spriteIndex * 4);
        auto inputColorsIt = cornerColors.begin() + long(spriteIndex * 4);
        auto inputTextureCoordsIt = cornerTextureCoords.begin() + long(spriteIndex * 4);

        if(updatePositions)
        {
            outputPositions.insert(outputPositions.end(), inputPositionsIt, inputPositionsIt + 4);
            inputPositionsIt += 4;
        }

        if(updateColors)
        {
            outputColors.insert(outputColors.end(), inputColorsIt, inputColorsIt + 4);
            inputColorsIt += 4;
        }

        if(updateTextureCoords)
        {
            outputTextureCoords.insert(outputTextureCoords.end(), inputTextureCoordsIt, inputTextureCoordsIt + 4);
            inputTextureCoordsIt += 4;
        }

        ++spriteIndex;

        while(spriteIndex < numVisibleSprites)
        {
            const auto& sortInfo = sortInfos[spriteIndex];

            if(! sortInfo.outOfScreen)
            {
                auto newTextureGraphics = sortInfo.textureGraphics;
                int newAlpha = sortInfo.alpha;

                if(newTextureGraphics != textureGraphics || newAlpha != alpha)
                {
                    uploadAndDrawSprites<updatePositions, updateColors, updateTextureCoords>(
                                spriteGraphicsIndex, textureGraphics, alpha, spriteGraphicsVector, updateData);
                    ++spriteGraphicsIndex;
                    textureGraphics = newTextureGraphics;
                    alpha = newAlpha;
                }

                if(updatePositions)
                {
                    outputPositions.insert(outputPositions.end(), inputPositionsIt, inputPositionsIt + 4);
                    inputPositionsIt += 4;
                }

                if(updateColors)
                {
                    outputColors.insert(outputColors.end(), inputColorsIt, inputColorsIt + 4);
                    inputColorsIt += 4;
                }

                if(updateTextureCoords)
                {
                    outputTextureCoords.insert(outputTextureCoords.end(), inputTextureCoordsIt, inputTextureCoordsIt + 4);
                    inputTextureCoordsIt += 4;
                }
            }

            ++spriteIndex;
        }

        if(! outputPositions.empty())
        {
            uploadAndDrawSprites<updatePositions, updateColors, updateTextureCoords>(
                        spriteGraphicsIndex, textureGraphics, alpha, spriteGraphicsVector, updateData);
        }

        auto* graphics = gb.graphics;
        auto numSpriteGraphics = spriteGraphicsVector.size();
        auto numVisibleSpriteGraphics = spriteGraphicsIndex + 1;
        int numUnusedSpriteGraphics = int(numSpriteGraphics - numVisibleSpriteGraphics);

        while(numUnusedSpriteGraphics > 0)
        {
            graphics->destroySpriteGraphics(spriteGraphicsVector[numSpriteGraphics - 1]);
            spriteGraphicsVector.pop_back();
            --numUnusedSpriteGraphics;
            --numSpriteGraphics;
        }

        return true;
    }
}


void Sprites::update(UpdateData& updateData)
{
    if(_sort)
    {
        _sortData();
        _sort = false;
    }

    if(auto numVisibleSprites = _newIndex)
    {
        if(_updatePositions || _updateColors || _updateTextureCoords)
        {
            bool drawnSprites;

            if(_updatePositions)
            {
                _updateCornerPositions(updateData.parentTransform);

                if(_updateColors && _updateTextureCoords)
                {
                    drawnSprites = uploadAndDrawData<true, true, true>(numVisibleSprites, _cornerPositions,
                                                                       _cornerColors, _cornerTextureCoords,
                                                                       _sortInfos, _spriteGraphics, updateData);
                }
                else if(_updateColors)
                {
                    drawnSprites = uploadAndDrawData<true, true, false>(numVisibleSprites, _cornerPositions,
                                                                        _cornerColors, _cornerTextureCoords,
                                                                        _sortInfos, _spriteGraphics, updateData);
                }
                else if(_updateTextureCoords)
                {
                    drawnSprites = uploadAndDrawData<true, false, true>(numVisibleSprites, _cornerPositions,
                                                                        _cornerColors, _cornerTextureCoords,
                                                                        _sortInfos, _spriteGraphics, updateData);
                }
                else
                {
                    drawnSprites = uploadAndDrawData<true, false, false>(numVisibleSprites, _cornerPositions,
                                                                         _cornerColors, _cornerTextureCoords,
                                                                         _sortInfos, _spriteGraphics, updateData);
                }
            }
            else
            {
                if(_updateColors && _updateTextureCoords)
                {
                    drawnSprites = uploadAndDrawData<false, true, true>(numVisibleSprites, _cornerPositions,
                                                                        _cornerColors, _cornerTextureCoords,
                                                                        _sortInfos, _spriteGraphics, updateData);
                }
                else if(_updateColors)
                {
                    drawnSprites = uploadAndDrawData<false, true, false>(numVisibleSprites, _cornerPositions,
                                                                         _cornerColors, _cornerTextureCoords,
                                                                         _sortInfos, _spriteGraphics, updateData);
                }
                else if(_updateTextureCoords)
                {
                    drawnSprites = uploadAndDrawData<false, false, true>(numVisibleSprites, _cornerPositions,
                                                                         _cornerColors, _cornerTextureCoords,
                                                                         _sortInfos, _spriteGraphics, updateData);
                }
                else
                {
                    drawnSprites = uploadAndDrawData<false, false, false>(numVisibleSprites, _cornerPositions,
                                                                          _cornerColors, _cornerTextureCoords,
                                                                          _sortInfos, _spriteGraphics, updateData);
                }
            }

            _updatePositions = _updateColors = _updateTextureCoords = false;

            if(! drawnSprites)
            {
                destroyGraphics();
            }
        }
        else
        {
            _drawData();
        }
    }
    else
    {
        destroyGraphics();
    }
}

void Sprites::destroyGraphics() noexcept
{
    auto* graphics = gb.graphics;

    for(const SpriteGraphics& spriteGraphics : _spriteGraphics)
    {
        graphics->destroySpriteGraphics(spriteGraphics);
    }

    _spriteGraphics.clear();
}

namespace
{
    char getAlphaType(const Color& color) noexcept
    {
        if(color.getA() < epsilon)
        {
            return 2;
        }

        if(color.getA() < 1 - epsilon)
        {
            return 1;
        }

        return 0;
    }

    char getAlphaType(const TextureRegion& textureRegion) noexcept
    {
        return textureRegion.hasAlpha() ? 1 : 0;
    }
}

char Sprites::_getAlphaType(std::size_t index) const noexcept
{
    auto index4 = index * 4;
    const Color& a = _cornerColors[index4];
    const Color& b = _cornerColors[index4 + 1];
    const Color& c = _cornerColors[index4 + 2];
    const Color& d = _cornerColors[index4 + 3];
    char alphaType0 = getAlphaType(a);
    char alphaType1 = getAlphaType(b);
    char alphaType2 = getAlphaType(c);
    char alphaType3 = getAlphaType(d);

    if(alphaType0 == 2 && alphaType1 == 2 && alphaType2 == 2 && alphaType3 == 2)
    {
        return 2;
    }

    if(alphaType0 > 0 || alphaType1 > 0 || alphaType2 > 0 || alphaType3 > 0)
    {
        return 1;
    }

    return getAlphaType(_textureRegions[index]);
}

void Sprites::_updateAll() noexcept
{
    _sort = true;
    _updatePositions = true;
    _updateColors = true;
    _updateTextureCoords = true;
}

void Sprites::_sortData() noexcept
{
    auto count = _indexes.size();
    BTJ_ASSERT(count);

    Swap swap{ *this };
    SortInfoComparator<SortInfo> cmp{ _sortInfos };
    bool swapped = quicksort(0, int(count - 1), cmp, swap);

    while(count > 0 && ! _sortInfos[count - 1].show())
    {
        --count;
    }

    _newIndex = count;

    if(swapped)
    {
        _updateAll();
    }
}

void Sprites::_updateCornerPositions(const Mat44& parentTransform) noexcept
{
    auto outOfScreen = [](const Vec4& corner) noexcept
    {
        float x = corner.x;
        float y = corner.y;
        return (x < -1 || x > 1) && (y < -1 || y > 1);
    };

    std::size_t numVisibleSprites = _newIndex;
    std::size_t cornerIndex = 0;

    for(std::size_t spriteIndex = 0; spriteIndex < numVisibleSprites; ++spriteIndex)
    {
        const SizeI& size = _sizes[spriteIndex];
        float hw = size.getWidth() * 0.5f;
        float hh = size.getHeight() * 0.5f;
        auto transform = parentTransform * getTransform(_positions[spriteIndex], _rotations[spriteIndex],
                                                        _shears[spriteIndex], _scales[spriteIndex], _flips[spriteIndex]);
        Vec4 a = transform * Vec4(-hw, hh, 1, 1);
        Vec4 b = transform * Vec4(hw, hh, 1, 1);
        Vec4 c = transform * Vec4(hw, -hh, 1, 1);
        Vec4 d = transform * Vec4(-hw, -hh, 1, 1);
        _cornerPositions[cornerIndex] = PositionF(a[0], a[1]);
        _cornerPositions[cornerIndex + 1] = PositionF(b[0], b[1]);
        _cornerPositions[cornerIndex + 2] = PositionF(c[0], c[1]);
        _cornerPositions[cornerIndex + 3] = PositionF(d[0], d[1]);
        _sortInfos[spriteIndex].outOfScreen = outOfScreen(a) && outOfScreen(b) && outOfScreen(c) && outOfScreen(d);
        cornerIndex += 4;
    }
}

void Sprites::_drawData() const
{
    auto* graphics = gb.graphics;

    for(const SpriteGraphics& spriteGraphics : _spriteGraphics)
    {
        graphics->bindSpriteGraphics(spriteGraphics);
        graphics->drawSpriteGraphics(spriteGraphics);
    }
}

}
