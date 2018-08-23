/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_KEYBOARD_BACKEND_H
#define BTJ_KEYBOARD_BACKEND_H

#include "btj_optional.h"

namespace btj
{

class Event;
class KeyEvent;

namespace KeyboardBackend
{

bool init();

void destroy() noexcept;

Optional<KeyEvent> getPressedKeyEvent(const Event& event);

Optional<KeyEvent> getReleasedKeyEvent(const Event& event);

void update();

}

}

#endif
