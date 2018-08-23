/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_GRAPHICS_IMPL_H
#define BTJ_GRAPHICS_IMPL_H

#include "btj_size_i.h"
#include "btj_color.h"
#include "btj_optional.h"
#include "btj_layers.h"
#include "btj_textures.h"

namespace btj
{

class GraphicsImpl
{

public:
    static Optional<GraphicsImpl> create(const SizeI& windowSize);

    ~GraphicsImpl() noexcept;

    GraphicsImpl(const GraphicsImpl& other) = delete;

    GraphicsImpl& operator=(const GraphicsImpl& other) = delete;

    GraphicsImpl(GraphicsImpl&& other) noexcept;

    GraphicsImpl& operator=(GraphicsImpl&& other) noexcept;

    const SizeI& getSize() const noexcept
    {
        return _size;
    }

    const Color& getBackgroundColor() const noexcept
    {
        return _backgroundColor;
    }

    void setBackgroundColor(const Color& color) noexcept;

    void reserveTextures(std::size_t count)
    {
        _textures->reserve(count);
    }

    Texture createTexture(const Image& image);

    TextureGraphics createTextureGraphics();

    void destroyTextureGraphics(const TextureGraphics& textureGraphics) noexcept;

    void bindTextureGraphics(const TextureGraphics& textureGraphics);

    void uploadTextureImage(const Image& image);

    void reserveLayers(std::size_t count)
    {
        _layers.reserve(count);
    }

    Layer createLayer(int zOrder);

    SpriteGraphics createSpriteGraphics();

    void destroySpriteGraphics(const SpriteGraphics& spriteGraphics) noexcept;

    void bindSpriteGraphics(const SpriteGraphics& spriteGraphics);

    void uploadSpritePositions(const SpriteGraphics& spriteGraphics, const Vector<PositionF>& positions);

    void uploadSpriteColors(const SpriteGraphics& spriteGraphics, const Vector<Color>& colors);

    void uploadSpriteTextureCoords(const SpriteGraphics& spriteGraphics, const Vector<PositionF>& textureCoords);

    void drawSpriteGraphics(const SpriteGraphics& spriteGraphics);

    void update();

private:
    friend class GlobalPointers;

    Optional<Textures> _textures;
    Optional<TextureGraphics> _bindedTextureGraphics;
    Layers _layers;
    SizeI _size;
    Color _backgroundColor;
    Sprites::UpdateData _spritesUpdateData;
    Vector<SpriteGraphics> _unusedSpriteGraphics;
    bool _alphaEnabled;
    bool _backgroundColorUpdated;

    GraphicsImpl(Optional<Textures>&& textures, const SizeI& size) noexcept;
};

}

#endif
