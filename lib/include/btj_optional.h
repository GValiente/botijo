/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_OPTIONAL_H
#define BTJ_OPTIONAL_H

#include "tl/optional.hpp"

namespace btj
{

template<typename T>
using Optional = tl::optional<T>;

}

#endif
