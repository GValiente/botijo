/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_KEYBOARD_IMPL_H
#define BTJ_KEYBOARD_IMPL_H

#include "btj_optional.h"
#include "btj_key_event.h"

namespace btj
{

class Event;
class KeyEvent;

class KeyboardImpl
{

public:
    static Optional<KeyboardImpl> create();

    ~KeyboardImpl() noexcept;

    KeyboardImpl(const KeyboardImpl& other) = delete;

    KeyboardImpl& operator=(const KeyboardImpl& other) = delete;

    KeyboardImpl(KeyboardImpl&& other) noexcept;

    KeyboardImpl& operator=(KeyboardImpl&& other) noexcept;

    const Optional<KeyEvent>& getPressedKeyEvent() const noexcept
    {
        return _pressedKeyEvent;
    }

    const Optional<KeyEvent>& getReleasedKeyEvent() const noexcept
    {
        return _releasedKeyEvent;
    }

    void registerEvent(const Event& event);

    void update();

private:
    Optional<KeyEvent> _pressedKeyEvent;
    Optional<KeyEvent> _releasedKeyEvent;
    bool _active;

    KeyboardImpl() noexcept;
};

}

#endif
