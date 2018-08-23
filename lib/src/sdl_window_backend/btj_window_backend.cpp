/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "../btj_window_backend.h"

#include <cstring>
#include "SDL.h"
#include "btj_size_i.h"
#include "btj_window_config.h"
#include "btj_assert.h"
#include "btj_logger.h"
#include "../btj_event.h"

namespace btj
{
namespace WindowBackend
{

static_assert(sizeof(SDL_Event) <= sizeof(Event), "");

namespace
{
    bool openGLSetup() noexcept
    {
        // Set OpenGL version 3.3:
        if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
        {
            BTJ_LOG_ERROR << "SDL_GL_CONTEXT_PROFILE_MASK setup failed: " << SDL_GetError() << std::endl;
            return false;
        }

        if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3))
        {
            BTJ_LOG_ERROR << "SDL_GL_CONTEXT_MAJOR_VERSION setup failed: " << SDL_GetError() << std::endl;
            return false;
        }

        if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3))
        {
            BTJ_LOG_ERROR << "SDL_GL_CONTEXT_MINOR_VERSION setup failed: " << SDL_GetError() << std::endl;
            return false;
        }

        if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG))
        {
            BTJ_LOG_ERROR << "SDL_GL_CONTEXT_FLAGS setup failed: " << SDL_GetError() << std::endl;
            return false;
        }

        // Turn on double buffering with a 24bit Z buffer:
        if(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1))
        {
            BTJ_LOG_ERROR << "SDL_GL_DOUBLEBUFFER setup failed: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }
}

bool init()
{
    if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        BTJ_LOG_ERROR << "SDL video sub system init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    if(! openGLSetup())
    {
        BTJ_LOG_ERROR << "SDL OpenGL setup failed" << std::endl;
    }

    return true;
}

void destroy() noexcept
{
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void* createHandle(const WindowConfig& config)
{
    std::uint32_t flags = SDL_WINDOW_OPENGL;

    switch(config.getMode())
    {

    case WindowConfig::Mode::WINDOW:
        break;

    case WindowConfig::Mode::FULLSCREEN:
        flags |= SDL_WINDOW_FULLSCREEN;
        break;

    case WindowConfig::Mode::FULLSCREEN_DESKTOP_RESOLUTION:
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        break;
    }

    auto handle = SDL_CreateWindow(config.getName().c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   config.getWidth(), config.getHeight(), flags);

    if(! handle)
    {
        BTJ_LOG_ERROR << "SDL window handle create failed: " << SDL_GetError() << std::endl;
    }

    return handle;
}

void destroyHandle(void* handle) noexcept
{
    BTJ_ASSERT(handle);

    SDL_DestroyWindow(static_cast<SDL_Window*>(handle));
}

void updateHandle(void* handle)
{
    BTJ_ASSERT(handle);

    SDL_GL_SwapWindow(static_cast<SDL_Window*>(handle));
}

void* createContext(const WindowConfig& config, void* handle)
{
    BTJ_ASSERT(handle);

    auto context = SDL_GL_CreateContext(static_cast<SDL_Window*>(handle));

    if(context)
    {
        if(SDL_GL_SetSwapInterval(config.isVsyncEnabled() ? 1 : 0))
        {
            BTJ_LOG_ERROR << "SDL GL swap interval setup failed: " << SDL_GetError() << std::endl;
            destroyContext(context);
            context = nullptr;
        }
    }
    else
    {
        BTJ_LOG_ERROR << "SDL OpenGL context create failed: " << SDL_GetError() << std::endl;
    }

    return context;
}

void destroyContext(void* context) noexcept
{
    BTJ_ASSERT(context);

    SDL_GL_DeleteContext(context);
}

Optional<SizeI> getDesktopSize()
{
    SDL_DisplayMode displayMode;
    Optional<SizeI> result;

    if(SDL_GetCurrentDisplayMode(0, &displayMode))
    {
        BTJ_LOG_ERROR << "SDL display mode retrieve failed: " << SDL_GetError() << std::endl;
    }
    else if(displayMode.w <= 0)
    {
        BTJ_LOG_ERROR << "Invalid SDL display mode width: " << displayMode.w << std::endl;
    }
    else if(displayMode.h <= 0)
    {
        BTJ_LOG_ERROR << "Invalid SDL display mode height: " << displayMode.h << std::endl;
    }
    else
    {
        result = SizeI(displayMode.w, displayMode.h);
    }

    return result;
}

bool isMinimizedEvent(const Event& event)
{
    SDL_Event sdlEvent;
    std::memcpy(&sdlEvent, &event, sizeof(SDL_Event));
    return sdlEvent.type == SDL_WINDOWEVENT && sdlEvent.window.event == SDL_WINDOWEVENT_MINIMIZED;
}

bool isRestoredEvent(const Event& event)
{
    SDL_Event sdlEvent;
    std::memcpy(&sdlEvent, &event, sizeof(SDL_Event));
    return sdlEvent.type == SDL_WINDOWEVENT && sdlEvent.window.event == SDL_WINDOWEVENT_RESTORED;
}

}
}
