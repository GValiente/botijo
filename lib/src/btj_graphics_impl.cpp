/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_graphics_impl.h"

#include "btj_layer.h"
#include "btj_texture.h"
#include "btj_logger.h"
#include "btj_sprite_graphics.h"
#include "btj_graphics_backend.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<GraphicsImpl>::value, "");
static_assert(! std::is_copy_constructible<GraphicsImpl>::value, "");
static_assert(! std::is_copy_assignable<GraphicsImpl>::value, "");
static_assert(std::is_nothrow_move_constructible<GraphicsImpl>::value, "");
static_assert(std::is_nothrow_move_assignable<GraphicsImpl>::value, "");

Optional<GraphicsImpl> GraphicsImpl::create(const SizeI& windowSize)
{
    Optional<GraphicsImpl> result;

    if(GraphicsBackend::init())
    {
        if(auto textures = Textures::create())
        {
            result = GraphicsImpl(std::move(textures), windowSize);
            result->_spritesUpdateData.parentTransform =
                    glm::ortho(0.0f, float(windowSize.getWidth()), 0.0f, float(windowSize.getHeight()),
                               -1000.f, 1000.f);
        }
        else
        {
            BTJ_LOG_ERROR << "Textures create failed" << std::endl;
            GraphicsBackend::destroy();
        }
    }
    else
    {
        BTJ_LOG_ERROR << "Backend init failed" << std::endl;
    }

    return result;
}

GraphicsImpl::~GraphicsImpl() noexcept
{
    if(_textures)
    {
        _bindedTextureGraphics.reset();
        _layers.destroyGraphics();
        _textures->destroyGraphics();

        for(const SpriteGraphics& unusedSpriteGraphics : _unusedSpriteGraphics)
        {
            GraphicsBackend::destroySpriteGraphics(unusedSpriteGraphics);
        }

        _unusedSpriteGraphics.clear();
        GraphicsBackend::destroy();
        _textures.reset();
    }
}

GraphicsImpl::GraphicsImpl(GraphicsImpl&& other) noexcept :
    GraphicsImpl(Optional<Textures>(), SizeI())
{
    *this = std::move(other);
}

GraphicsImpl& GraphicsImpl::operator=(GraphicsImpl&& other) noexcept
{
    std::swap(_textures, other._textures);
    std::swap(_bindedTextureGraphics, other._bindedTextureGraphics);
    std::swap(_layers, other._layers);
    std::swap(_size, other._size);
    std::swap(_backgroundColor, other._backgroundColor);
    std::swap(_spritesUpdateData, other._spritesUpdateData);
    std::swap(_alphaEnabled, other._alphaEnabled);
    std::swap(_backgroundColorUpdated, other._backgroundColorUpdated);
    return *this;
}

void GraphicsImpl::setBackgroundColor(const Color& color) noexcept
{
    if(_backgroundColor != color)
    {
        _backgroundColor = color;
        _backgroundColorUpdated = false;
    }
}

Texture GraphicsImpl::createTexture(const Image& image)
{
    return _textures->createTexture(image);
}

TextureGraphics GraphicsImpl::createTextureGraphics()
{
    TextureGraphics textureGraphics = GraphicsBackend::createTextureGraphics();
    _bindedTextureGraphics = textureGraphics;
    return textureGraphics;
}

void GraphicsImpl::destroyTextureGraphics(const TextureGraphics& textureGraphics) noexcept
{
    GraphicsBackend::destroyTextureGraphics(textureGraphics);
}

void GraphicsImpl::bindTextureGraphics(const TextureGraphics& textureGraphics)
{
    if(! _bindedTextureGraphics || *_bindedTextureGraphics != textureGraphics)
    {
        GraphicsBackend::bindTextureGraphics(textureGraphics);
        _bindedTextureGraphics = textureGraphics;
    }
}

void GraphicsImpl::uploadTextureImage(const Image& image)
{
    GraphicsBackend::uploadTextureImage(image);
}

Layer GraphicsImpl::createLayer(int zOrder)
{
    return _layers.createLayer(zOrder);
}

SpriteGraphics GraphicsImpl::createSpriteGraphics()
{
    auto numUnusedSpriteGraphics = _unusedSpriteGraphics.size();
    SpriteGraphics spriteGraphics;

    if(numUnusedSpriteGraphics)
    {
        spriteGraphics = _unusedSpriteGraphics[numUnusedSpriteGraphics - 1];
        _unusedSpriteGraphics.pop_back();
    }
    else
    {
        spriteGraphics = GraphicsBackend::createSpriteGraphics();
    }

    return spriteGraphics;
}

void GraphicsImpl::destroySpriteGraphics(const SpriteGraphics& spriteGraphics) noexcept
{
    _unusedSpriteGraphics.push_back(spriteGraphics);
}

void GraphicsImpl::bindSpriteGraphics(const SpriteGraphics& spriteGraphics)
{
    GraphicsBackend::bindSpriteGraphics(spriteGraphics);
}

void GraphicsImpl::uploadSpritePositions(const SpriteGraphics& spriteGraphics, const Vector<PositionF>& positions)
{
    GraphicsBackend::uploadSpritePositions(spriteGraphics, positions);
}

void GraphicsImpl::uploadSpriteColors(const SpriteGraphics& spriteGraphics, const Vector<Color>& colors)
{
    GraphicsBackend::uploadSpriteColors(spriteGraphics, colors);
}

void GraphicsImpl::uploadSpriteTextureCoords(const SpriteGraphics& spriteGraphics, const Vector<PositionF>& textureCoords)
{
    GraphicsBackend::uploadSpriteTextureCoords(spriteGraphics, textureCoords);
}

void GraphicsImpl::drawSpriteGraphics(const SpriteGraphics& spriteGraphics)
{
    bool alpha = spriteGraphics.publicData.alpha;

    if(_alphaEnabled != alpha)
    {
        GraphicsBackend::setAlphaEnabled(alpha);
        _alphaEnabled = alpha;
    }

    bindTextureGraphics(spriteGraphics.publicData.textureGraphics);
    GraphicsBackend::drawSpriteGraphics(spriteGraphics);
}

void GraphicsImpl::update()
{
    _textures->update();

    if(! _backgroundColorUpdated)
    {
        GraphicsBackend::setBackgroundColor(_backgroundColor);
        _backgroundColorUpdated = true;
    }

    GraphicsBackend::update();
    _spritesUpdateData.cornerPositions.clear();
    _spritesUpdateData.cornerColors.clear();
    _spritesUpdateData.cornerTextureCoords.clear();
    _layers.update(_spritesUpdateData);
}

GraphicsImpl::GraphicsImpl(Optional<Textures>&& textures, const SizeI& size) noexcept :
    _textures(std::move(textures)),
    _size(size),
    _alphaEnabled(false),
    _backgroundColorUpdated(false)
{
}

}
