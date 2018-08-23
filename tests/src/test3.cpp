/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "catch.hpp"

#include "btj_core.h"
#include "btj_flip.h"
#include "btj_color.h"
#include "btj_layer.h"
#include "btj_size_i.h"
#include "btj_size_f.h"
#include "btj_sprite.h"
#include "btj_config.h"
#include "btj_graphics.h"
#include "btj_keyboard.h"
#include "btj_key_event.h"
#include "btj_position_f.h"
#include "btj_exception.h"
#include "btj_logger.h"

TEST_CASE("test 3")
{
    try
    {
        btj::Config config;
        config.window.setVsyncEnabled(false);

        auto core = btj::Core::create(config);
        REQUIRE(core);

        auto graphics = core->getGraphics();
        auto keyboard = core->getKeyboard();
        graphics.setBackgroundColor(btj::Color(0, 0.25, 0.25));

        auto size = graphics.getSize();
        auto w = size.getWidth();
        auto h = size.getHeight();
        auto layer = graphics.createLayer();
        layer.setPosition(btj::PositionF(w * 0.5f, h * 0.5f));

        auto sprite1 = layer.createSprite(btj::SizeI(320, 240));
        sprite1.setColor(btj::Color(0.5, 0.5, 0.5));

        auto sprite2 = layer.createSprite(btj::SizeI(160, 120));
        sprite2.setPosition(btj::PositionF(-w * 0.25f, 0));
        sprite2.setColor(btj::Color(1, 1, 1, 0.5));

        auto sprite3 = layer.createSprite(btj::SizeI(w / 2, h / 2));
        sprite3.setPosition(btj::PositionF(-w * 0.25f, -h * 0.25f));
        sprite3.setFlip(btj::Flip::HORIZONTAL);
        sprite3.setColors({ btj::Color(1, 0, 0), btj::Color(0, 1, 0), btj::Color(0, 0, 1), btj::Color(0, 0, 0) });

        auto sprite4 = layer.createSprite(btj::SizeI(w / 2, h / 2));
        sprite4.setPosition(btj::PositionF(-w * 0.25f, -h * 0.25f));
        sprite4.setScale(btj::SizeF(0.5, 0.5));
        sprite4.setRotationDegrees(45);
        sprite4.setFlip(btj::Flip::HORIZONTAL);
        sprite4.setColors({ btj::Color(1, 0, 0), btj::Color(0, 1, 0), btj::Color(0, 0, 1), btj::Color(0, 0, 0) });

        while(true)
        {
            if(const auto& keyEvent = keyboard.getPressedKeyEvent())
            {
                auto key = keyEvent->getKey();

                if(key == btj::Key::LEFT)
                {
                    layer.setRotationDegrees(layer.getRotationDegrees() - 1);
                }
                else if(key == btj::Key::RIGHT)
                {
                    layer.setRotationDegrees(layer.getRotationDegrees() + 1);
                }
                else if(key == btj::Key::UP)
                {
                    layer.setPosition(layer.getPosition() + btj::PositionF(0, 0.1f * h));
                }
                else if(key == btj::Key::DOWN)
                {
                    layer.setPosition(layer.getPosition() - btj::PositionF(0, 0.1f * h));
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
