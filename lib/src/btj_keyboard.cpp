/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_keyboard.h"

#include "btj_keyboard_impl.h"
#include "btj_global_pointers.h"


namespace btj
{

static_assert(std::is_nothrow_destructible<Keyboard>::value, "");
static_assert(std::is_copy_constructible<Keyboard>::value, "");
static_assert(std::is_copy_assignable<Keyboard>::value, "");
static_assert(std::is_nothrow_move_constructible<Keyboard>::value, "");
static_assert(std::is_nothrow_move_assignable<Keyboard>::value, "");

const Optional<KeyEvent>& Keyboard::getPressedKeyEvent() const noexcept
{
    return gb.keyboard->getPressedKeyEvent();
}

const Optional<KeyEvent>& Keyboard::getReleasedKeyEvent() const noexcept
{
    return gb.keyboard->getReleasedKeyEvent();
}

}
