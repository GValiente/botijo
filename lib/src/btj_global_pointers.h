/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_GLOBAL_POINTERS_H
#define BTJ_GLOBAL_POINTERS_H

namespace btj
{

class Core;
class GraphicsImpl;
class Layers;
class Textures;
class KeyboardImpl;

class GlobalPointers
{

public:
    Core* core = nullptr;
    GraphicsImpl* graphics = nullptr;
    Layers* layers = nullptr;
    Textures* textures = nullptr;
    KeyboardImpl* keyboard = nullptr;

    void setup(Core* core, GraphicsImpl* graphics, KeyboardImpl* keyboard) noexcept;
};

extern GlobalPointers gb;

}

#endif
