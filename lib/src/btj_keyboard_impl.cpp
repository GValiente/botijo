/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_keyboard_impl.h"

#include "btj_keyboard_backend.h"
#include "btj_logger.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<KeyboardImpl>::value, "");
static_assert(! std::is_copy_constructible<KeyboardImpl>::value, "");
static_assert(! std::is_copy_assignable<KeyboardImpl>::value, "");
static_assert(std::is_nothrow_move_constructible<KeyboardImpl>::value, "");
static_assert(std::is_nothrow_move_assignable<KeyboardImpl>::value, "");

Optional<KeyboardImpl> KeyboardImpl::create()
{
    Optional<KeyboardImpl> result;

    if(KeyboardBackend::init())
    {
        result = KeyboardImpl();
    }
    else
    {
        BTJ_LOG_ERROR << "Backend init failed" << std::endl;
    }

    return result;
}

KeyboardImpl::~KeyboardImpl() noexcept
{
    if(_active)
    {
        KeyboardBackend::destroy();
        _active = false;
    }
}

KeyboardImpl::KeyboardImpl(KeyboardImpl&& other) noexcept :
    _active(false)
{
    *this = std::move(other);
}

KeyboardImpl& KeyboardImpl::operator=(KeyboardImpl&& other) noexcept
{
    std::swap(_pressedKeyEvent, other._pressedKeyEvent);
    std::swap(_releasedKeyEvent, other._releasedKeyEvent);
    std::swap(_active, other._active);
    return *this;
}

void KeyboardImpl::registerEvent(const Event& event)
{
    if(auto keyEvent = KeyboardBackend::getPressedKeyEvent(event))
    {
        _pressedKeyEvent = keyEvent;
    }

    if(auto keyEvent = KeyboardBackend::getReleasedKeyEvent(event))
    {
        _releasedKeyEvent = keyEvent;
    }
}

void KeyboardImpl::update()
{
    KeyboardBackend::update();
    _pressedKeyEvent.reset();
    _releasedKeyEvent.reset();
}

KeyboardImpl::KeyboardImpl() noexcept :
    _active(true)
{
}

}
