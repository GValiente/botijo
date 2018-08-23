/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_WINDOW_CONFIG_H
#define BTJ_WINDOW_CONFIG_H

#include "btj_string.h"

namespace btj
{

class WindowConfig
{

public:
    enum class Mode
    {
        WINDOW,
        FULLSCREEN,
        FULLSCREEN_DESKTOP_RESOLUTION
    };

    WindowConfig();

    const String& getName() const noexcept
    {
        return _name;
    }

    void setName(String&& name) noexcept
    {
        _name = std::move(name);
    }

    Mode getMode() const noexcept
    {
        return _mode;
    }

    void setMode(Mode mode) noexcept
    {
        _mode = mode;
    }

    int getWidth() const noexcept
    {
        return _width;
    }

    bool setWidth(int width) noexcept;

    int getHeight() const noexcept
    {
        return _height;
    }

    bool setHeight(int height) noexcept;

    bool isVsyncEnabled() const noexcept
    {
        return _vsyncEnabled;
    }

    void setVsyncEnabled(bool enabled) noexcept
    {
        _vsyncEnabled = enabled;
    }

private:
    String _name;
    Mode _mode;
    int _width;
    int _height;
    bool _vsyncEnabled;
};

}

#endif
