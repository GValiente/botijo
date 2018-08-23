/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_SHADERS_H
#define BTJ_SHADERS_H

#include <string>

#define GLEW_STATIC
#include "GL/glew.h"

#include "btj_optional.h"
#include "btj_logger.h"

namespace btj
{

class Shaders
{

public:
    static Optional<Shaders> create()
    {
        Optional<Shaders> result = Shaders();
        result->_program = glCreateProgram();

        if(result->_program)
        {
            glBindAttribLocation(result->_program, 0, "inPosition");
            glBindAttribLocation(result->_program, 1, "inColor");

            if(result->_loadVertexShader())
            {
                if(result->_loadFragmentShader())
                {
                    if(result->_programLink())
                    {
                        glUseProgram(result->_program);
                        glUniform1i(glGetUniformLocation(result->_program, "texture1"), 0);
                    }
                    else
                    {
                        BTJ_LOG_ERROR << "Program link failed" << std::endl;
                        result.reset();
                    }
                }
                else
                {
                    BTJ_LOG_ERROR << "Fragment shader load failed" << std::endl;
                    result.reset();
                }
            }
            else
            {
                BTJ_LOG_ERROR << "Vertex shader load failed" << std::endl;
                result.reset();
            }
        }
        else
        {
            BTJ_LOG_ERROR << "Program create failed" << std::endl;
            result.reset();
        }

        return result;
    }

    Shaders(Shaders&& other) noexcept :
        Shaders()
    {
        *this = std::move(other);
    }

    Shaders& operator=(Shaders&& other) noexcept
    {
        std::swap(_program, other._program);
        std::swap(_vertexShader, other._vertexShader);
        std::swap(_fragmentShader, other._fragmentShader);
        return *this;
    }

    ~Shaders() noexcept
    {
        if(_program)
        {
            glUseProgram(0);

            if(_vertexShader)
            {
                glDetachShader(_program, _vertexShader);
                glDeleteShader(_vertexShader);
                _vertexShader = 0;
            }

            if(_fragmentShader)
            {
                glDetachShader(_program, _fragmentShader);
                glDeleteShader(_fragmentShader);
                _fragmentShader = 0;
            }

            glDeleteProgram(_program);
            _program = 0;
        }
    }

private:
    GLuint _program;
    GLuint _vertexShader;
    GLuint _fragmentShader;

    Shaders() noexcept :
        _program(0),
        _vertexShader(0),
        _fragmentShader(0)
    {
    }

    static std::string _getErrorMessage(GLuint shaderId)
    {
        GLint maxLength;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        std::string errorMessage;
        errorMessage.resize(std::size_t(maxLength));

        auto errorMessagePtr = const_cast<GLchar*>(errorMessage.data());
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, errorMessagePtr);
        return errorMessage;
    }

    bool _loadShader(GLuint shaderId, const GLchar* source, GLint sourceSize)
    {
        glShaderSource(shaderId, 1, &source, &sourceSize);
        glCompileShader(shaderId);

        GLint success = false;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

        if(! success)
        {
            BTJ_LOG_ERROR << "Shader compilation failed: " << _getErrorMessage(shaderId) << std::endl;
            return false;
        }

        glAttachShader(_program, shaderId);
        return true;
    }

    bool _loadVertexShader()
    {
        _vertexShader = glCreateShader(GL_VERTEX_SHADER);

        if(! _vertexShader)
        {
            BTJ_LOG_ERROR << "Shader create failed";
            return false;
        }

        constexpr GLchar source[] = R"glsl(
                #version 330 core

                in vec2 inPosition;
                in vec4 inColor;
                in vec2 inTextureCoord;

                out vec4 exColor;
                out vec2 exTextureCoord;

                void main(void)
                {
                    gl_Position = vec4(inPosition, 1, 1);
                    exColor = inColor;
                    exTextureCoord = inTextureCoord;
                }
                )glsl";

        if(! _loadShader(_vertexShader, source, sizeof(source)))
        {
            BTJ_LOG_ERROR << "Shader load failed";
            return false;
        }

        return true;
    }

    bool _loadFragmentShader()
    {
        _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        if(! _fragmentShader)
        {
            BTJ_LOG_ERROR << "Shader create failed";
            return false;
        }

        constexpr GLchar source[] = R"glsl(
                #version 330 core

                // Some drivers required this next line to function properly:
                precision highp float;

                in vec4 exColor;
                in vec2 exTextureCoord;

                out vec4 outColor;

                uniform sampler2D texture1;

                void main(void)
                {
                    // Alpha test:
                    if(exColor.a < 0.01f)
                    {
                        discard;
                    }

                    outColor = texture(texture1, exTextureCoord) * exColor;
                }
                )glsl";

        if(! _loadShader(_fragmentShader, source, sizeof(source)))
        {
            BTJ_LOG_ERROR << "Shader load failed";
            return false;
        }

        return true;
    }

    bool _programLink()
    {
        glLinkProgram(_program);

        GLint success = 0;
        glGetProgramiv(_program, GL_LINK_STATUS, &success);

        if(! success)
        {
            BTJ_LOG_ERROR << "Link failed: " << _getErrorMessage(_program) << std::endl;
            return false;
        }

        return true;
    }
};

static_assert(std::is_nothrow_destructible<Shaders>::value, "");
static_assert(! std::is_copy_constructible<Shaders>::value, "");
static_assert(! std::is_copy_assignable<Shaders>::value, "");
static_assert(std::is_nothrow_move_constructible<Shaders>::value, "");
static_assert(std::is_nothrow_move_assignable<Shaders>::value, "");

}

#endif
