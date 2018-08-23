/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_core.h"

#include "btj_config.h"
#include "btj_key_event.h"
#include "btj_exception.h"
#include "btj_window_impl.h"
#include "btj_graphics.h"
#include "btj_graphics_impl.h"
#include "btj_keyboard.h"
#include "btj_keyboard_impl.h"
#include "btj_event.h"
#include "btj_global_pointers.h"
#include "btj_core_backend.h"
#include "btj_logger.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<Core>::value, "");
static_assert(! std::is_copy_constructible<Core>::value, "");
static_assert(! std::is_copy_assignable<Core>::value, "");
static_assert(std::is_nothrow_move_constructible<Core>::value, "");
static_assert(std::is_nothrow_move_assignable<Core>::value, "");

class Core::Impl
{

public:
    WindowImpl window;
    GraphicsImpl graphics;
    KeyboardImpl keyboard;
    std::uint64_t prevTicks;
    float ticksPerSecond;

    Impl(WindowImpl&& _window, GraphicsImpl&& _graphics, KeyboardImpl&& _keyboard) noexcept :
        window(std::move(_window)),
        graphics(std::move(_graphics)),
        keyboard(std::move(_keyboard)),
        prevTicks(CoreBackend::getCurrentTicks()),
        ticksPerSecond(float(CoreBackend::getTicksPerSecond()))
    {
    }

    ~Impl() noexcept
    {
        CoreBackend::destroy();
    }
};

Core::~Core() noexcept
{
    _impl.reset();

    if(this == gb.core)
    {
        gb = GlobalPointers();
    }
}

Core::Core(Core&& other) noexcept :
    _impl(std::move(other._impl))
{
    if(_impl)
    {
        gb.setup(this, &_impl->graphics, &_impl->keyboard);
    }
}

Core& Core::operator=(Core&& other) noexcept
{
    _impl = std::move(other._impl);

    if(_impl)
    {
        gb.setup(this, &_impl->graphics, &_impl->keyboard);
    }

    return *this;
}

Optional<Core> Core::create(const Config& config)
{
    Optional<Core> result;

    if(gb.core)
    {
        BTJ_LOG_ERROR << "There's already an instanced core" << std::endl;
    }
    else
    {
        if(CoreBackend::init())
        {
            if(auto window = WindowImpl::create(config.window))
            {
                if(auto graphics = GraphicsImpl::create(window->getSize()))
                {
                    if(auto keyboard = KeyboardImpl::create())
                    {
                        std::unique_ptr<Impl> impl(new Impl(std::move(*window), std::move(*graphics),
                                                            std::move(*keyboard)));
                        result = Core(std::move(impl));
                        result->_updateScreen();
                    }
                    else
                    {
                        BTJ_LOG_ERROR << "Keyboard create failed" << std::endl;
                        CoreBackend::destroy();
                    }
                }
                else
                {
                    BTJ_LOG_ERROR << "Graphics create failed" << std::endl;
                    CoreBackend::destroy();
                }
            }
            else
            {
                BTJ_LOG_ERROR << "Window create failed" << std::endl;
                CoreBackend::destroy();
            }
        }
        else
        {
            BTJ_LOG_ERROR << "Backend init failed" << std::endl;
        }
    }

    return result;
}

Graphics Core::getGraphics() noexcept
{
    return Graphics();
}

Keyboard Core::getKeyboard() noexcept
{
    return Keyboard();
}

float Core::update()
{
    _updateScreen();

    std::uint64_t nowTicks = CoreBackend::getCurrentTicks();
    std::uint64_t elapsedTicks = nowTicks - _impl->prevTicks;
    float elapsedTime = elapsedTicks / _impl->ticksPerSecond;
    _impl->prevTicks = nowTicks;

    auto event = CoreBackend::pollEvent();
    bool minimized = false;
    _impl->keyboard.update();

    while(event || minimized)
    {
        if(event)
        {
            if(CoreBackend::isQuitEvent(*event))
            {
                throw QuitException();
            }
            else if(_impl->window.isMinimizedEvent(*event))
            {
                minimized = true;
            }
            else if(_impl->window.isRestoredEvent(*event))
            {
                minimized = false;
            }
            else
            {
                _impl->keyboard.registerEvent(*event);
            }
        }
        else
        {
            CoreBackend::sleep(0.1f);
        }

        event = CoreBackend::pollEvent();
    }

    return elapsedTime;
}

float Core::update(float time)
{
    BTJ_ASSERT(time > 0);

    float elapsedTime = 0;

    while(elapsedTime < time)
    {
        elapsedTime += update();
    }

    return elapsedTime;
}

void Core::sleep(float time)
{
    BTJ_ASSERT(time > 0);

    CoreBackend::sleep(time);
}

Core::Core(std::unique_ptr<Impl>&& impl) noexcept :
    _impl(std::move(impl))
{
    gb.setup(this, &_impl->graphics, &_impl->keyboard);
}

void Core::_updateScreen()
{
    _impl->graphics.update();
    _impl->window.update();
}

}
