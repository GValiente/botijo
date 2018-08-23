/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "../btj_graphics_backend.h"

#include <array>
#include "btj_color.h"
#include "btj_image.h"
#include "btj_position_f.h"
#include "btj_logger.h"
#include "btj_shaders.h"
#include "../btj_sprite_graphics.h"
#include "../btj_texture_graphics.h"

namespace btj
{
namespace GraphicsBackend
{

namespace
{
    struct Sprite
    {
        SpriteGraphics::PublicData publicData;
        std::array<GLuint, 3> vbo;
        std::array<GLuint, 1> vao;
        std::array<GLuint, 1> ebo;

        Sprite() = default;

        explicit Sprite(const SpriteGraphics& spriteGraphics) noexcept
        {
            std::memcpy(this, &spriteGraphics, sizeof(Sprite));
        }

        SpriteGraphics getSpriteGraphics() const noexcept
        {
            SpriteGraphics spriteGraphics;
            std::memcpy(&spriteGraphics, this, sizeof(Sprite));
            return spriteGraphics;
        }
    };

    static_assert(sizeof(Sprite) <= sizeof(SpriteGraphics), "");

    Optional<Shaders> shaders;
    Optional<GLuint> ebo;
    std::vector<GLuint> elements;
    int currentFrame = 0;

    bool checkGlError()
    {
        if(currentFrame > 60)
        {
            return true;
        }

        GLenum error = glGetError();
        bool success = true;

        while(error != GL_NO_ERROR)
        {
            StringView errorMessage;

            switch(error)
            {
                case GL_INVALID_OPERATION:
                    errorMessage = "invalid operation";
                    break;

                case GL_INVALID_ENUM:
                    errorMessage = "invalid enum";
                    break;

                case GL_INVALID_VALUE:
                    errorMessage = "invalid value";
                    break;

                case GL_OUT_OF_MEMORY:
                    errorMessage = "out of memory";
                    break;

                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    errorMessage = "invalid framebuffer operation";
                    break;
            }

            BTJ_LOG_ERROR << "OpenGL error: " << errorMessage << std::endl;
            error = glGetError();
            success = false;
        }

        return success;
    }

    void uploadVBO(const std::array<GLuint, 3>& vbo, GLuint index, const void* data, GLsizei dataSize,
                   GLsizei numElements)
    {
        // Bind VBO:
        glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);

        // Upload the data to the VBO:
        glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);

        // Indicate were in the VAO the data from the current VBO should be stored:
        glVertexAttribPointer(index, numElements, GL_FLOAT, GL_FALSE, 0, nullptr);

        // Enable our attribute within the current VAO:
        glEnableVertexAttribArray(index);
    }
}

bool init()
{
    auto output = glewInit();

    if(output != GLEW_OK)
    {
        BTJ_LOG_ERROR << "GLEW init failed: " << glewGetErrorString(output) << std::endl;
        return false;
    }

    shaders = Shaders::create();

    if(! shaders || ! checkGlError())
    {
        BTJ_LOG_ERROR << "Shaders create failed" << std::endl;
        destroy();
        return false;
    }

    if(! checkGlError())
    {
        BTJ_LOG_ERROR << "OpenGL error when creating shaders" << std::endl;
        destroy();
        return false;
    }

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTexture(GL_TEXTURE0);

    if(! checkGlError())
    {
        BTJ_LOG_ERROR << "State setup failed" << std::endl;
        destroy();
        return false;
    }

    ebo = GLuint(0);
    glGenBuffers(1, &*ebo);

    if(! checkGlError())
    {
        BTJ_LOG_ERROR << "Ebo generation failed" << std::endl;
        destroy();
        return false;
    }

    return true;
}

void destroy() noexcept
{
    if(ebo)
    {
        glDeleteBuffers(1, &*ebo);
        ebo.reset();
    }

    shaders.reset();
    elements.clear();
    currentFrame = 0;
}

TextureGraphics createTextureGraphics()
{
    GLuint id;
    glGenTextures(1, &id);

    TextureGraphics textureGraphics(id);
    bindTextureGraphics(textureGraphics);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return textureGraphics;
}

void destroyTextureGraphics(const TextureGraphics& textureGraphics) noexcept
{
    auto id = GLuint(textureGraphics.getId());
    glDeleteTextures(1, &id);
}

void bindTextureGraphics(const TextureGraphics& textureGraphics)
{
    glBindTexture(GL_TEXTURE_2D, GLuint(textureGraphics.getId()));
}

void uploadTextureImage(const Image& image)
{
    GLsizei width = image.getWidth();
    GLsizei height = image.getHeight();
    auto data = image.getData();

    if(image.hasAlpha())
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
}

SpriteGraphics createSpriteGraphics()
{
    Sprite sprite;
    glGenBuffers(GLsizei(sprite.vbo.size()), sprite.vbo.data());
    glGenBuffers(GLsizei(sprite.ebo.size()), sprite.ebo.data());
    glGenVertexArrays(GLsizei(sprite.vao.size()), sprite.vao.data());
    glBindVertexArray(sprite.vao[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    return sprite.getSpriteGraphics();
}

void destroySpriteGraphics(const SpriteGraphics& spriteGraphics) noexcept
{
    Sprite sprite(spriteGraphics);
    glDeleteVertexArrays(GLsizei(sprite.vao.size()), sprite.vao.data());
    glDeleteBuffers(GLsizei(sprite.ebo.size()), sprite.ebo.data());
    glDeleteBuffers(GLsizei(sprite.vbo.size()), sprite.vbo.data());
}

void bindSpriteGraphics(const SpriteGraphics& spriteGraphics)
{
    Sprite sprite(spriteGraphics);
    glBindVertexArray(sprite.vao[0]);
}

void uploadSpritePositions(const SpriteGraphics& spriteGraphics, const Vector<PositionF>& positions)
{
    Sprite sprite(spriteGraphics);
    auto numCorners = positions.size();
    uploadVBO(sprite.vbo, 0, positions.data(), GLsizei(numCorners * sizeof(PositionF)), 2);
}

void uploadSpriteColors(const SpriteGraphics& spriteGraphics, const Vector<Color>& colors)
{
    Sprite sprite(spriteGraphics);
    auto numCorners = colors.size();
    uploadVBO(sprite.vbo, 1, colors.data(), GLsizei(numCorners * sizeof(Color)), 4);
}

void uploadSpriteTextureCoords(const SpriteGraphics& spriteGraphics, const Vector<PositionF>& textureCoords)
{
    Sprite sprite(spriteGraphics);
    auto numCorners = textureCoords.size();
    uploadVBO(sprite.vbo, 2, textureCoords.data(), GLsizei(numCorners * sizeof(PositionF)), 2);
}

void drawSpriteGraphics(const SpriteGraphics& spriteGraphics)
{
    Sprite sprite(spriteGraphics);
    auto numSprites = spriteGraphics.publicData.numSprites;
    auto numElements = numSprites * 6;

    if(numElements > elements.size())
    {
        elements.resize(numElements * 2);

        for(std::size_t index = 0, limit = numSprites * 2; index < limit; ++index)
        {
            std::size_t elementIndex = index * 6;
            GLuint refElement = GLuint(index * 4);
            elements[elementIndex + 0] = refElement + 0;
            elements[elementIndex + 1] = refElement + 1;
            elements[elementIndex + 2] = refElement + 2;
            elements[elementIndex + 3] = refElement + 2;
            elements[elementIndex + 4] = refElement + 3;
            elements[elementIndex + 5] = refElement + 0;
        }

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLsizei(elements.size() * sizeof(GLuint)), elements.data(), GL_STATIC_DRAW);
    }

    glDrawElements(GL_TRIANGLES, GLsizei(numElements), GL_UNSIGNED_INT, nullptr);
}

void setAlphaEnabled(bool enabled)
{
    if(enabled)
    {
        glEnable(GL_BLEND);
    }
    else
    {
        glDisable(GL_BLEND);
    }
}

void setBackgroundColor(const Color& color)
{
    glClearColor(color.getR(), color.getG(), color.getB(), color.getA());
}

void update()
{
    glClear(GL_COLOR_BUFFER_BIT);
    checkGlError();
}

}
}
