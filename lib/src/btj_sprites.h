/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_SPRITES_H
#define BTJ_SPRITES_H

#include <array>
#include "btj_flip.h"
#include "btj_color.h"
#include "btj_size_f.h"
#include "btj_vector.h"
#include "btj_rotation.h"
#include "btj_position_f.h"
#include "btj_sprite_graphics.h"
#include "btj_texture_region.h"

namespace btj
{

class Sprite;
class SpriteGraphics;

class Sprites
{

public:
    struct UpdateData
    {
        Mat44 parentTransform;
        Vector<PositionF> cornerPositions;
        Vector<Color> cornerColors;
        Vector<PositionF> cornerTextureCoords;
    };

    struct SortInfo
    {
        TextureGraphics textureGraphics;
        int zOrder;
        char alpha;
        char hidden;
        char outOfScreen;

        static SortInfo invalid() noexcept;

        SortInfo(const TextureGraphics& textureGraphics, int zOrder, char alpha = 0, char hidden = 0,
                 char outOfScreen = 0) noexcept;

        bool show() const noexcept
        {
            return zOrder != std::numeric_limits<int>::max() && hidden == 0 && alpha < 2 && ! outOfScreen;
        }

        bool operator==(const SortInfo& other) const noexcept
        {
            return textureGraphics == other.textureGraphics && zOrder == other.zOrder && hidden == other.hidden &&
                    alpha == other.alpha;
        }

        bool operator<(const SortInfo& other) const noexcept;
    };

    Sprites() noexcept;

    void clear() noexcept;

    void reserve(std::size_t count);

    Sprite createSprite(std::size_t layerId, const SizeI& size, const TextureRegion& textureRegion, int zOrder);

    std::size_t create(const SizeI& size, const TextureRegion& textureRegion, int zOrder);

    void destroy(std::size_t id) noexcept;

    SizeI getSize(std::size_t id) const noexcept;

    void setSize(std::size_t id, const SizeI& size) noexcept;

    TextureRegion getTextureRegion(std::size_t id) const noexcept;

    void setTextureRegion(std::size_t id, const TextureRegion& textureRegion) noexcept;

    PositionF getPosition(std::size_t id) const noexcept;

    void setPosition(std::size_t id, const PositionF& position) noexcept;

    SizeF getScale(std::size_t id) const noexcept;

    void setScale(std::size_t id, const SizeF& scale) noexcept;

    float getRotation(std::size_t id) const noexcept;

    void setRotation(std::size_t id, float angle) noexcept;

    PositionF getShear(std::size_t id) const noexcept;

    void setShear(std::size_t id, const PositionF& shear) noexcept;

    Flip getFlip(std::size_t id) const noexcept;

    void setFlip(std::size_t id, Flip flip) noexcept;

    Color getColor(std::size_t id) const noexcept;

    void setColor(std::size_t id, const Color& color) noexcept;

    std::array<Color, 4> getColors(std::size_t id) const noexcept;

    void setColors(std::size_t id, const std::array<Color, 4>& colors) noexcept;

    int getZOrder(std::size_t id) const noexcept;

    void setZOrder(std::size_t id, int zOrder) noexcept;

    bool isVisible(std::size_t id) const noexcept;

    void setVisible(std::size_t id, bool visible) noexcept;

    void update(UpdateData& updateData);

    void updatePositions() noexcept
    {
        _updatePositions = true;
    }

    void destroyGraphics() noexcept;

private:
    class Swap;
    friend class Swap;

    Vector<std::size_t> _indexes;
    Vector<PositionF> _positions;
    Vector<SizeI> _sizes;
    Vector<TextureRegion> _textureRegions;
    Vector<SizeF> _scales;
    Vector<Rotation> _rotations;
    Vector<PositionF> _shears;
    Vector<Flip> _flips;
    Vector<PositionF> _cornerPositions;
    Vector<Color> _cornerColors;
    Vector<PositionF> _cornerTextureCoords;
    Vector<SortInfo> _sortInfos;
    Vector<SpriteGraphics> _spriteGraphics;
    std::size_t _newIndex;
    bool _sort;
    bool _updatePositions;
    bool _updateColors;
    bool _updateTextureCoords;

    char _getAlphaType(std::size_t index) const noexcept;

    void _updateAll() noexcept;

    void _sortData() noexcept;

    void _updateCornerPositions(const Mat44& parentTransform) noexcept;

    void _drawData() const;
};

}

#endif
