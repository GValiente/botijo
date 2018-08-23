/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_window_config.h"

#include "btj_logger.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<WindowConfig>::value, "");
static_assert(std::is_copy_constructible<WindowConfig>::value, "");
static_assert(std::is_copy_assignable<WindowConfig>::value, "");
static_assert(std::is_nothrow_move_constructible<WindowConfig>::value, "");
static_assert(std::is_nothrow_move_assignable<WindowConfig>::value, "");

WindowConfig::WindowConfig() :
    _name("Botijo"),
    _mode(Mode::WINDOW),
    _width(640),
    _height(480),
    _vsyncEnabled(true)
{
}

bool WindowConfig::setWidth(int width) noexcept
{
    if(width < 1)
    {
        BTJ_LOG_ERROR << "Invalid width: " << width;
        return false;
    }

    _width = width;
    return true;
}

bool WindowConfig::setHeight(int height) noexcept
{
    if(height < 1)
    {
        BTJ_LOG_ERROR << "Invalid height: " << height;
        return false;
    }

    _height = height;
    return true;
}

}
