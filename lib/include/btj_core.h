/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_CORE_H
#define BTJ_CORE_H

#include <memory>
#include "btj_optional.h"

namespace btj
{

class Config;
class Graphics;
class Keyboard;

class Core
{

public:
    static Optional<Core> create(const Config& config);

    ~Core() noexcept;

    Core(Core&& other) noexcept;

    Core& operator=(Core&& other) noexcept;

    Graphics getGraphics() noexcept;

    Keyboard getKeyboard() noexcept;

    float update();

    float update(float time);

    void sleep(float time);

private:
    class Impl;
    std::unique_ptr<Impl> _impl;

    explicit Core(std::unique_ptr<Impl>&& impl) noexcept;

    void _updateScreen();
};

}

#endif
