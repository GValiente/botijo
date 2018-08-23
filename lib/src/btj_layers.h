/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_LAYERS_H
#define BTJ_LAYERS_H

#include "btj_sprites.h"
#include "btj_optional.h"

namespace btj
{

class Layer;

class Layers
{

public:
    Layers() noexcept;

    void clear() noexcept;

    void reserve(std::size_t count);

    Layer createLayer(int zOrder);

    std::size_t create(int zOrder);

    void destroy(std::size_t id) noexcept;

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

    int getZOrder(std::size_t id) const noexcept;

    void setZOrder(std::size_t id, int zOrder) noexcept;

    bool isVisible(std::size_t id) const noexcept;

    void setVisible(std::size_t id, bool visible) noexcept;

    Sprites& getSprites(std::size_t id);

    void update(Sprites::UpdateData& updateData);

    void destroyGraphics() noexcept;

private:
    class Swap;
    friend class Swap;

    struct SortInfo
    {
        int zOrder = 0;
        int hidden = 0;

        static SortInfo invalid() noexcept
        {
            return SortInfo(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
        }

        SortInfo(int zOrder, int hidden = 0) noexcept;

        bool show() const noexcept
        {
            return zOrder != std::numeric_limits<int>::max() && hidden == 0;
        }

        bool operator==(const SortInfo& other) const noexcept
        {
            return zOrder == other.zOrder && hidden == other.hidden;
        }

        bool operator<(const SortInfo& other) const noexcept;
    };

    Vector<std::size_t> _indexes;
    Vector<PositionF> _positions;
    Vector<SizeF> _scales;
    Vector<Rotation> _rotations;
    Vector<PositionF> _shears;
    Vector<Flip> _flips;
    Vector<Sprites> _sprites;
    Vector<SortInfo> _sortInfos;
    std::size_t _newIndex;
    bool _sort;
    bool _updateSpritesPositions;

    void _sortData() noexcept;
};

}

#endif
