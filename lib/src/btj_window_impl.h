/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_WINDOW_IMPL_H
#define BTJ_WINDOW_IMPL_H

#include "btj_size_i.h"
#include "btj_optional.h"

namespace btj
{

class SizeI;
class Event;
class WindowConfig;

class WindowImpl
{

public:
    static Optional<WindowImpl> create(const WindowConfig& config);

    ~WindowImpl() noexcept;

    WindowImpl(const WindowImpl& other) = delete;

    WindowImpl& operator=(const WindowImpl& other) = delete;

    WindowImpl(WindowImpl&& other) noexcept;

    WindowImpl& operator=(WindowImpl&& other) noexcept;

    const SizeI& getSize() const noexcept
    {
        return _size;
    }

    bool isMinimizedEvent(const Event& event) const;

    bool isRestoredEvent(const Event& event) const;

    void update();

private:
    SizeI _size;
    void* _handle;
    void* _context;

    WindowImpl(const SizeI& size, void* handle, void* context) noexcept;
};

}

#endif
