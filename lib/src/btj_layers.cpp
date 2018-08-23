/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_layers.h"

#include "btj_layer.h"
#include "btj_sprite.h"
#include "btj_assert.h"
#include "btj_logger.h"
#include "btj_transform.h"
#include "btj_quicksort.h"
#include "btj_sort_info_comparator.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<Layers>::value, "");
static_assert(std::is_copy_constructible<Layers>::value, "");
static_assert(std::is_copy_assignable<Layers>::value, "");
static_assert(std::is_nothrow_move_constructible<Layers>::value, "");
static_assert(std::is_nothrow_move_assignable<Layers>::value, "");

class Layers::Swap
{

public:
    Layers& layers;

    void operator()(std::size_t a, std::size_t b) noexcept
    {
        std::swap(layers._indexes[a], layers._indexes[b]);
        std::swap(layers._positions[a], layers._positions[b]);
        std::swap(layers._scales[a], layers._scales[b]);
        std::swap(layers._rotations[a], layers._rotations[b]);
        std::swap(layers._shears[a], layers._shears[b]);
        std::swap(layers._flips[a], layers._flips[b]);
        std::swap(layers._sprites[a], layers._sprites[b]);
        std::swap(layers._sortInfos[a], layers._sortInfos[b]);
    }
};

Layers::SortInfo::SortInfo(int _zOrder, int _hidden) noexcept :
    zOrder(_zOrder),
    hidden(_hidden)
{
}

bool Layers::SortInfo::operator<(const SortInfo& other) const noexcept
{
    if(hidden == other.hidden)
    {
        return zOrder < other.zOrder;
    }

    return hidden < other.hidden;
}

Layers::Layers() noexcept :
    _newIndex(0),
    _sort(false),
    _updateSpritesPositions(false)
{
}

void Layers::clear() noexcept
{
    if(! _sortInfos.empty())
    {
        for(SortInfo& sortInfo : _sortInfos)
        {
            sortInfo = SortInfo::invalid();
        }

        _sort = true;
    }
}

void Layers::reserve(std::size_t count)
{
    _indexes.reserve(count);
    _positions.reserve(count);
    _scales.reserve(count);
    _rotations.reserve(count);
    _shears.reserve(count);
    _flips.reserve(count);
    _sprites.reserve(count);
    _sortInfos.reserve(count);
}

Layer Layers::createLayer(int zOrder)
{
    return Layer(create(zOrder));
}

std::size_t Layers::create(int zOrder)
{
    auto newIndex = _newIndex;
    std::size_t newId;

    if(newIndex == _indexes.size())
    {
        _indexes.push_back(newIndex);
        _positions.push_back(PositionF());
        _scales.push_back(SizeF(1, 1));
        _rotations.push_back(Rotation(0));
        _shears.push_back(PositionF());
        _flips.push_back(Flip());
        _sprites.push_back(Sprites());
        _sortInfos.push_back(SortInfo(zOrder));
        newId = _newIndex;
    }
    else
    {
        _positions[newIndex] = PositionF();
        _scales[newIndex] = SizeF(1, 1);
        _rotations[newIndex] = Rotation(0);
        _shears[newIndex] = PositionF();
        _flips[newIndex] = Flip();
        _sprites[newIndex].clear();
        _sortInfos[newIndex] = SortInfo(zOrder);
        newId = _indexes[newIndex];
    }

    ++_newIndex;
    _sort = true;
    return newId;
}

void Layers::destroy(std::size_t id) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    _sortInfos[index] = SortInfo::invalid();
    _sort = true;
}

PositionF Layers::getPosition(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _positions[index];
}

void Layers::setPosition(std::size_t id, const PositionF& position) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];

    if(_positions[index] != position)
    {
        _positions[index] = position;
        _updateSpritesPositions = true;
    }
}

SizeF Layers::getScale(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _scales[index];
}

void Layers::setScale(std::size_t id, const SizeF& scale) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];

    if(_scales[index] != scale)
    {
        _scales[index] = scale;
        _updateSpritesPositions = true;
    }
}

float Layers::getRotation(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _rotations[index].getAngle();
}

void Layers::setRotation(std::size_t id, float angle) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];

    if(! equals(_rotations[index].getAngle(), angle))
    {
        _rotations[index] = Rotation(angle);
        _updateSpritesPositions = true;
    }
}

PositionF Layers::getShear(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _shears[index];
}

void Layers::setShear(std::size_t id, const PositionF& shear) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];

    if(_shears[index] != shear)
    {
        _shears[index] = shear;
        _updateSpritesPositions = true;
    }
}

Flip Layers::getFlip(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _flips[index];
}

void Layers::setFlip(std::size_t id, Flip flip) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];

    if(_flips[index] != flip)
    {
        _flips[index] = flip;
        _updateSpritesPositions = true;
    }
}

int Layers::getZOrder(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _sortInfos[index].zOrder;
}

void Layers::setZOrder(std::size_t id, int zOrder) noexcept
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

bool Layers::isVisible(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return ! _sortInfos[index].hidden;
}

void Layers::setVisible(std::size_t id, bool visible) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    bool hidden = ! visible;

    if(hidden != bool(_sortInfos[index].hidden))
    {
        _sortInfos[index].hidden = hidden;
        _sort = true;
    }
}

Sprites& Layers::getSprites(std::size_t id)
{
    BTJ_ASSERT(id < _indexes.size());

    return _sprites[id];
}

void Layers::update(Sprites::UpdateData& updateData)
{
    if(_sort)
    {
        _sortData();
        _sort = false;
    }

    if(auto numVisibleLayers = _newIndex)
    {
        if(_updateSpritesPositions)
        {
            for(std::size_t index = 0; index < numVisibleLayers; ++index)
            {
                _sprites[index].updatePositions();
            }

            _updateSpritesPositions = false;
        }

        for(std::size_t index = 0; index < numVisibleLayers; ++index)
        {
            auto parentTransform = updateData.parentTransform;
            updateData.parentTransform = parentTransform * getTransform(_positions[index], _rotations[index],
                                                                        _shears[index], _scales[index], _flips[index]);
            _sprites[index].update(updateData);
            updateData.parentTransform = parentTransform;
        }
    }
}

void Layers::destroyGraphics() noexcept
{
    for(auto& sprites : _sprites)
    {
        sprites.destroyGraphics();
    }
}

void Layers::_sortData() noexcept
{
    auto count = _indexes.size();
    BTJ_ASSERT(count);

    Swap swap{ *this };
    SortInfoComparator<SortInfo> cmp{ _sortInfos };
    quicksort(0, int(count - 1), cmp, swap);

    while(count > 0 && ! _sortInfos[count - 1].show())
    {
        --count;
    }

    _newIndex = count;
}

}
