/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_WINDOW_BACKEND_H
#define BTJ_WINDOW_BACKEND_H

#include "btj_optional.h"

namespace btj
{

class SizeI;
class Event;
class WindowConfig;

namespace WindowBackend
{

bool init();

void destroy() noexcept;

void* createHandle(const WindowConfig& config);

void destroyHandle(void* handle) noexcept;

void updateHandle(void* handle);

void* createContext(const WindowConfig& config, void* handle);

void destroyContext(void* context) noexcept;

Optional<SizeI> getDesktopSize();

bool isMinimizedEvent(const Event& event);

bool isRestoredEvent(const Event& event);

}

}

#endif
