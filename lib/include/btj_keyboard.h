/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_KEYBOARD_H
#define BTJ_KEYBOARD_H

#include "btj_optional.h"

namespace btj
{

class KeyEvent;
class KeyboardImpl;

class Keyboard
{

public:
    const Optional<KeyEvent>& getPressedKeyEvent() const noexcept;

    const Optional<KeyEvent>& getReleasedKeyEvent() const noexcept;
};

}

#endif
