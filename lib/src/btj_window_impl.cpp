/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_window_impl.h"

#include "btj_window_config.h"
#include "btj_window_backend.h"
#include "btj_logger.h"

namespace btj
{

static_assert(std::is_nothrow_destructible<WindowImpl>::value, "");
static_assert(! std::is_copy_constructible<WindowImpl>::value, "");
static_assert(! std::is_copy_assignable<WindowImpl>::value, "");
static_assert(std::is_nothrow_move_constructible<WindowImpl>::value, "");
static_assert(std::is_nothrow_move_assignable<WindowImpl>::value, "");

Optional<WindowImpl> WindowImpl::create(const WindowConfig& config)
{
    Optional<WindowImpl> result;

    if(WindowBackend::init())
    {
        if(auto handle = WindowBackend::createHandle(config))
        {
            if(auto context = WindowBackend::createContext(config, handle))
            {
                Optional<SizeI> size;

                switch(config.getMode())
                {

                case WindowConfig::Mode::WINDOW:
                case WindowConfig::Mode::FULLSCREEN:
                    size = SizeI(config.getWidth(), config.getHeight());
                    break;

                case WindowConfig::Mode::FULLSCREEN_DESKTOP_RESOLUTION:
                    size = WindowBackend::getDesktopSize();
                    break;
                }

                if(size)
                {
                    result = WindowImpl(*size, handle, context);
                }
                else
                {
                    BTJ_LOG_ERROR << "Size retrieve failed" << std::endl;
                    WindowBackend::destroy();
                }
            }
            else
            {
                BTJ_LOG_ERROR << "Context create failed" << std::endl;
                WindowBackend::destroy();
            }
        }
        else
        {
            BTJ_LOG_ERROR << "Handle create failed" << std::endl;
            WindowBackend::destroy();
        }
    }
    else
    {
        BTJ_LOG_ERROR << "Backend init failed" << std::endl;
    }

    return result;
}

WindowImpl::~WindowImpl() noexcept
{
    if(_handle)
    {
        WindowBackend::destroyContext(_context);
        WindowBackend::destroyHandle(_handle);
        WindowBackend::destroy();
        _handle = nullptr;
        _context = nullptr;
    }
}

WindowImpl::WindowImpl(WindowImpl&& other) noexcept :
    _handle(nullptr),
    _context(nullptr)
{
    *this = std::move(other);
}

WindowImpl& WindowImpl::operator=(WindowImpl&& other) noexcept
{
    std::swap(_size, other._size);
    std::swap(_handle, other._handle);
    std::swap(_context, other._context);
    return *this;
}

bool WindowImpl::isMinimizedEvent(const Event& event) const
{
    return WindowBackend::isMinimizedEvent(event);
}

bool WindowImpl::isRestoredEvent(const Event& event) const
{
    return WindowBackend::isRestoredEvent(event);
}

void WindowImpl::update()
{
    WindowBackend::updateHandle(_handle);
}

WindowImpl::WindowImpl(const SizeI& size, void* handle, void* context) noexcept :
    _size(size),
    _handle(handle),
    _context(context)
{
}

}
