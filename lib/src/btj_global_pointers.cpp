/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_global_pointers.h"

#include "btj_graphics_impl.h"

namespace btj
{

GlobalPointers gb;

void GlobalPointers::setup(Core* _core, GraphicsImpl* _graphics, KeyboardImpl* _keyboard) noexcept
{
    core = _core;
    graphics = _graphics;
    layers = &_graphics->_layers;
    textures = &*_graphics->_textures;
    keyboard = _keyboard;
}

}
