/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "../btj_core_backend.h"

#include <cstring>
#include <algorithm>
#include "SDL.h"
#include "btj_logger.h"
#include "../btj_event.h"

namespace btj
{
namespace CoreBackend
{

static_assert(sizeof(SDL_Event) <= sizeof(Event), "");

bool init()
{
    if(SDL_Init(SDL_INIT_TIMER) < 0)
    {
        BTJ_LOG_ERROR << "SDL init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void destroy() noexcept
{
    SDL_Quit();
}

std::uint64_t getCurrentTicks()
{
    return SDL_GetPerformanceCounter();
}

std::uint64_t getTicksPerSecond()
{
    return SDL_GetPerformanceFrequency();
}

Optional<Event> pollEvent()
{
    SDL_Event sdlEvent;
    Optional<Event> result;

    if(SDL_PollEvent(&sdlEvent))
    {
        result = Event();
        std::memcpy(&*result, &sdlEvent, sizeof(SDL_Event));
    }

    return result;
}

bool isQuitEvent(const Event& event)
{
    SDL_Event sdlEvent;
    std::memcpy(&sdlEvent, &event, sizeof(SDL_Event));
    return sdlEvent.type == SDL_QUIT;
}

void sleep(float time)
{
    std::uint32_t ms = std::max(std::uint32_t(1), std::uint32_t(time * 1000));
    SDL_Delay(ms);
}

}
}
