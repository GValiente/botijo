/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_textures.h"

#include "btj_image.h"
#include "btj_assert.h"
#include "btj_logger.h"
#include "btj_quicksort.h"
#include "btj_graphics_impl.h"
#include "btj_global_pointers.h"
#include "btj_sort_info_comparator.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<Textures>::value, "");
static_assert(! std::is_copy_constructible<Textures>::value, "");
static_assert(! std::is_copy_assignable<Textures>::value, "");
static_assert(std::is_nothrow_move_constructible<Textures>::value, "");
static_assert(std::is_nothrow_move_assignable<Textures>::value, "");

class Textures::Swap
{

public:
    Textures& textures;

    void operator()(std::size_t a, std::size_t b) noexcept
    {
        std::swap(textures._indexes[a], textures._indexes[b]);
        std::swap(textures._textureInfos[a], textures._textureInfos[b]);
        std::swap(textures._sortInfos[a], textures._sortInfos[b]);
    }
};

Optional<Textures> Textures::create()
{
    Optional<Textures> result;

    if(auto dummyImage = Image::create(1, 1, Color(1, 1, 1)))
    {
        result = Textures(std::move(*dummyImage));
    }
    else
    {
        BTJ_LOG_ERROR << "Dummy image create failed" << std::endl;
    }

    return result;
}

void Textures::clear() noexcept
{
    if(! _sortInfos.empty())
    {
        _dummyTexture.reset();

        for(SortInfo& sortInfo : _sortInfos)
        {
            sortInfo.invalid = 1;
        }

        _sort = true;
    }
}

void Textures::reserve(std::size_t count)
{
    _indexes.reserve(count);
    _textureInfos.reserve(count);
    _sortInfos.reserve(count);
}

const Texture& Textures::getDummyTexture()
{
    if(! _dummyTexture)
    {
        _dummyTexture = createTexture(_dummyImage);
    }

    return *_dummyTexture;
}

Texture Textures::createTexture(const Image& image)
{
    return Texture(create(image));
}

std::size_t Textures::create(const Image& image)
{
    auto newIndex = _newIndex;
    std::size_t newId;

    if(newIndex == _indexes.size())
    {
        TextureInfo textureInfo;
        textureInfo.graphics = gb.graphics->createTextureGraphics();
        _indexes.push_back(newIndex);
        _textureInfos.push_back(textureInfo);
        _sortInfos.push_back(SortInfo());
        newId = _newIndex;
    }
    else
    {
        _sortInfos[newIndex] = SortInfo();
        newId = _indexes[newIndex];
    }

    TextureInfo& textureInfo = _textureInfos[newIndex];
    textureInfo.width = image.getWidth();
    textureInfo.height = image.getHeight();
    textureInfo.alpha = image.hasAlpha();
    gb.graphics->bindTextureGraphics(textureInfo.graphics);
    gb.graphics->uploadTextureImage(image);

    ++_newIndex;
    _sort = true;
    return newId;
}

void Textures::destroy(std::size_t id) noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    _sortInfos[index].invalid = 1;
    _sort = true;
}

TextureInfo Textures::getTextureInfo(std::size_t id) const noexcept
{
    BTJ_ASSERT(id < _indexes.size());

    auto index = _indexes[id];
    return _textureInfos[index];
}

void Textures::update()
{
    if(_sort)
    {
        _sortData();
        _sort = false;
    }
}

void Textures::destroyGraphics() noexcept
{
    auto* graphics = gb.graphics;
    _dummyTexture.reset();

    for(auto& textureInfo : _textureInfos)
    {
        graphics->destroyTextureGraphics(textureInfo.graphics);
    }
}

Textures::Textures(Image&& dummyImage) noexcept :
    _dummyImage(std::move(dummyImage)),
    _newIndex(0),
    _sort(false)
{
}

void Textures::_sortData() noexcept
{
    auto count = _indexes.size();
    BTJ_ASSERT(count);

    Swap swap{ *this };
    SortInfoComparator<SortInfo> cmp{ _sortInfos };
    quicksort(0, int(count - 1), cmp, swap);

    while(count > 0 && _sortInfos[count - 1].invalid)
    {
        --count;
    }

    _newIndex = count;
}

}
