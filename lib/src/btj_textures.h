/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_TEXTURES_H
#define BTJ_TEXTURES_H

#include "btj_image.h"
#include "btj_vector.h"
#include "btj_texture.h"
#include "btj_texture_info.h"

namespace btj
{

class Image;

class Textures
{

public:
    static Optional<Textures> create();

    void clear() noexcept;

    void reserve(std::size_t count);

    const Texture& getDummyTexture();

    Texture createTexture(const Image& image);

    std::size_t create(const Image& image);

    void destroy(std::size_t id) noexcept;

    TextureInfo getTextureInfo(std::size_t id) const noexcept;

    void update();

    void destroyGraphics() noexcept;

private:
    class Swap;
    friend class Swap;

    struct SortInfo
    {
        int invalid = 0;

        SortInfo(int _invalid = 0) noexcept :
            invalid(_invalid)
        {
        }

        bool operator==(const SortInfo& other) const noexcept
        {
            return invalid == other.invalid;
        }

        bool operator<(const SortInfo& other) const noexcept
        {
            return invalid < other.invalid;
        }
    };

    Vector<std::size_t> _indexes;
    Vector<TextureInfo> _textureInfos;
    Vector<SortInfo> _sortInfos;
    Image _dummyImage;
    Optional<Texture> _dummyTexture;
    std::size_t _newIndex;
    bool _sort;

    explicit Textures(Image&& dummyImage) noexcept;

    void _sortData() noexcept;
};

}

#endif
