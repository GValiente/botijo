/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "catch.hpp"

#include "btj_core.h"
#include "btj_color.h"
#include "btj_config.h"
#include "btj_graphics.h"
#include "btj_keyboard.h"
#include "btj_key_event.h"
#include "btj_exception.h"
#include "btj_logger.h"

TEST_CASE("test 1")
{
    try
    {
        btj::Config config;
        config.window.setVsyncEnabled(false);

        auto core = btj::Core::create(config);
        REQUIRE(core);

        auto graphics = core->getGraphics();
        auto keyboard = core->getKeyboard();
        graphics.setBackgroundColor(btj::Color(1, 1, 0));

        while(true)
        {
            if(const auto& keyEvent = keyboard.getPressedKeyEvent())
            {
                auto key = keyEvent->getKey();

                if(key == btj::Key::R)
                {
                    graphics.setBackgroundColor(btj::Color(1, 0, 0));
                }
                else if(key == btj::Key::G)
                {
                    graphics.setBackgroundColor(btj::Color(0, 1, 0));
                }
                else if(key == btj::Key::B)
                {
                    graphics.setBackgroundColor(btj::Color(0, 0, 1));
                }
                else if(key == btj::Key::ESCAPE)
                {
                    throw btj::QuitException();
                }
            }

            float elapsedTime = core->update();
            BTJ_LOG_MESSAGE << "FPS: " << 1 / elapsedTime << std::endl;
        }
    }
    catch(const btj::QuitException&)
    {
    }
}
