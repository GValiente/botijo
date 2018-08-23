/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_IMAGE_H
#define BTJ_IMAGE_H

#include "btj_optional.h"
#include "btj_string_view.h"

namespace btj
{

class Color;

class Image
{

public:
    static Optional<Image> create(const StringView& filePath, bool removeAlpha = false);

    static Optional<Image> create(int width, int height, const Color& color);

    ~Image() noexcept;

    Image(Image&& other) noexcept;

    Image& operator=(Image&& other) noexcept;

    const void* getData() const noexcept
    {
        return _data;
    }

    int getWidth() const noexcept
    {
        return _width;
    }

    int getHeight() const noexcept
    {
        return _height;
    }

    bool hasAlpha() const noexcept
    {
        return _alpha;
    }

private:
    void* _data;
    int _width;
    int _height;
    bool _alpha;

    Image(void* data, int width, int height, bool alpha) noexcept;
};

}

#endif
