/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_CORE_BACKEND_H
#define BTJ_CORE_BACKEND_H

#include "btj_optional.h"

namespace btj
{

class Event;

namespace CoreBackend
{

bool init();

void destroy() noexcept;

std::uint64_t getCurrentTicks();

std::uint64_t getTicksPerSecond();

Optional<Event> pollEvent();

bool isQuitEvent(const Event& event);

void sleep(float time);

}

}

#endif
