/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_image.h"

#include "stb_image_interface.h"
#include "btj_color.h"
#include "btj_logger.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<Image>::value, "");
static_assert(! std::is_copy_constructible<Image>::value, "");
static_assert(! std::is_copy_assignable<Image>::value, "");
static_assert(std::is_nothrow_move_constructible<Image>::value, "");
static_assert(std::is_nothrow_move_assignable<Image>::value, "");

Optional<Image> Image::create(const StringView& filePath, bool removeAlpha)
{
    int width, height, channels;
    auto data = stbi_load(filePath.data(), &width, &height, &channels, removeAlpha ? 3 : 0);
    Optional<Image> result;

    if(data)
    {
        result = Image(data, width, height, ! removeAlpha && channels == 4);

        if(width <= 0)
        {
            BTJ_LOG_ERROR << "Invalid image width: " << width << std::endl;
            result.reset();
        }
        else if(height <= 0)
        {
            BTJ_LOG_ERROR << "Invalid image height: " << height << std::endl;
            result.reset();
        }
        else if(channels != 3 && channels != 4)
        {
            BTJ_LOG_ERROR << "Unsupported image channels: " << channels << std::endl;
            result.reset();
        }
        else
        {
            if(result->hasAlpha())
            {
                auto* array = static_cast<std::uint8_t*>(result->_data);
                bool hasAlpha = false;

                for(int index = 3, limit = width * height * channels; index < limit; index += 4)
                {
                    if(array[index] < 255)
                    {
                        hasAlpha = true;
                        break;
                    }
                }

                if(! hasAlpha)
                {
                    result = create(filePath, true);
                }
            }
        }
    }
    else
    {
        BTJ_LOG_ERROR << "Image load failed: " << filePath << std::endl;
    }

    return result;
}

Optional<Image> Image::create(int width, int height, const Color& color)
{
    Optional<Image> result;

    if(width <= 0)
    {
        BTJ_LOG_ERROR << "Invalid image width: " << width << std::endl;
    }
    else if(height <= 0)
    {
        BTJ_LOG_ERROR << "Invalid image height: " << height << std::endl;
    }
    else
    {
        int channels;

        if(equals(color.getA(), 1))
        {
            channels = 4;
        }
        else
        {
            channels = 3;
        }

        auto dataSize = width * height * channels;

        if(auto data = std::malloc(std::size_t(dataSize)))
        {
            auto dataArray = static_cast<std::uint8_t*>(data);
            auto r = std::uint8_t(std::round(color.getR() * 255));
            auto g = std::uint8_t(std::round(color.getG() * 255));
            auto b = std::uint8_t(std::round(color.getB() * 255));

            if(channels == 4)
            {
                auto a = std::uint8_t(std::round(color.getA() * 255));

                for(int index = 0; index < dataSize; index += 4)
                {
                    dataArray[index] = r;
                    dataArray[index + 1] = g;
                    dataArray[index + 2] = b;
                    dataArray[index + 3] = a;
                }
            }
            else
            {
                for(int index = 0; index < dataSize; index += 3)
                {
                    dataArray[index] = r;
                    dataArray[index + 1] = g;
                    dataArray[index + 2] = b;
                }
            }

            result = Image(data, width, height, channels);
        }
        else
        {
            BTJ_LOG_ERROR << "malloc call failed: " << width << " - " << height << " - " << channels << std::endl;
        }
    }

    return result;
}

Image::~Image() noexcept
{
    stbi_image_free(_data);
    _data = nullptr;
}

Image::Image(Image&& other) noexcept :
    Image(nullptr, 0, 0, 0)
{
    *this = std::move(other);
}

Image& Image::operator=(Image&& other) noexcept
{
    std::swap(_data, other._data);
    std::swap(_width, other._width);
    std::swap(_height, other._height);
    std::swap(_alpha, other._alpha);
    return *this;
}

Image::Image(void* data, int width, int height, bool alpha) noexcept :
    _data(data),
    _width(width),
    _height(height),
    _alpha(alpha)
{
}

}
