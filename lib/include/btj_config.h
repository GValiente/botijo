/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_CONFIG_H
#define BTJ_CONFIG_H

#include "btj_window_config.h"

namespace btj
{

class Config
{

public:
    WindowConfig window;
};

static_assert(std::is_nothrow_destructible<Config>::value, "");
static_assert(std::is_copy_constructible<Config>::value, "");
static_assert(std::is_copy_assignable<Config>::value, "");
static_assert(std::is_nothrow_move_constructible<Config>::value, "");
static_assert(std::is_nothrow_move_assignable<Config>::value, "");

}

#endif
