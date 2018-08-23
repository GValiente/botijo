/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "catch.hpp"

#include "btj_core.h"
#include "btj_color.h"
#include "btj_layer.h"
#include "btj_size_i.h"
#include "btj_sprite.h"
#include "btj_config.h"
#include "btj_graphics.h"
#include "btj_keyboard.h"
#include "btj_key_event.h"
#include "btj_position_f.h"
#include "btj_exception.h"
#include "btj_logger.h"

TEST_CASE("test 2")
{
    try
    {
        btj::Config config;
        config.window.setVsyncEnabled(false);

        auto core = btj::Core::create(config);
        REQUIRE(core);

        auto graphics = core->getGraphics();
        auto keyboard = core->getKeyboard();
        graphics.setBackgroundColor(btj::Color(0.25, 0.25, 0));

        btj::Optional<btj::Layer> layer1 = graphics.createLayer();
        REQUIRE(layer1->getZOrder() == 0);
        core->update();
        REQUIRE(layer1->getZOrder() == 0);

        btj::Optional<btj::Layer> layer2 = graphics.createLayer();
        REQUIRE(layer1->getZOrder() == 0);
        REQUIRE(layer2->getZOrder() == 0);
        core->update();
        REQUIRE(layer1->getZOrder() == 0);
        REQUIRE(layer2->getZOrder() == 0);

        layer2->setZOrder(2);
        REQUIRE(layer1->getZOrder() == 0);
        REQUIRE(layer2->getZOrder() == 2);
        core->update();
        REQUIRE(layer1->getZOrder() == 0);
        REQUIRE(layer2->getZOrder() == 2);

        layer1->setZOrder(3);
        REQUIRE(layer1->getZOrder() == 3);
        REQUIRE(layer2->getZOrder() == 2);
        core->update();
        REQUIRE(layer1->getZOrder() == 3);
        REQUIRE(layer2->getZOrder() == 2);

        layer1.reset();
        REQUIRE(layer2->getZOrder() == 2);
        core->update();
        REQUIRE(layer2->getZOrder() == 2);

        layer2->setZOrder(3);
        REQUIRE(layer2->getZOrder() == 3);
        core->update();
        REQUIRE(layer2->getZOrder() == 3);

        auto layer = graphics.createLayer();
        REQUIRE(layer.getZOrder() == 0);
        REQUIRE(layer2->getZOrder() == 3);
        core->update();
        REQUIRE(layer.getZOrder() == 0);
        REQUIRE(layer2->getZOrder() == 3);

        auto sprite1 = layer.createSprite(btj::SizeI(320, 240), 1);
        sprite1.setPosition(btj::PositionF(320, 240));
        sprite1.setColor(btj::Color(0.5, 0.5, 0.5));

        auto sprite2 = layer.createSprite(btj::SizeI(160, 120), 2);
        sprite2.setPosition(btj::PositionF(160, 240));
        sprite2.setColor(btj::Color(1, 1, 1, 0.5));

        auto sprite3 = layer.createSprite(btj::SizeI(160, 120), 3);
        sprite3.setPosition(btj::PositionF(320 - 32, 240 + 32));
        sprite3.setColors({ btj::Color(1, 0, 0), btj::Color(0, 1, 0), btj::Color(0, 0, 1), btj::Color(0, 0, 0) });

        while(true)
        {
            if(const auto& keyEvent = keyboard.getPressedKeyEvent())
            {
                auto key = keyEvent->getKey();

                if(key == btj::Key::LEFT)
                {
                    sprite1.setPosition(sprite1.getPosition() - btj::PositionF(4, 0));
                }
                else if(key == btj::Key::RIGHT)
                {
                    sprite1.setPosition(sprite1.getPosition() + btj::PositionF(4, 0));
                }
                else if(key == btj::Key::UP)
                {
                    sprite1.setPosition(sprite1.getPosition() + btj::PositionF(0, 4));
                }
                else if(key == btj::Key::DOWN)
                {
                    sprite1.setPosition(sprite1.getPosition() - btj::PositionF(0, 4));
                }
                else if(key == btj::Key::R)
                {
                    sprite1.setColor(btj::Color(1, 0, 0));
                }
                else if(key == btj::Key::G)
                {
                    sprite1.setColor(btj::Color(0, 1, 0));
                }
                else if(key == btj::Key::B)
                {
                    sprite1.setColor(btj::Color(0, 0, 1));
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
