/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_VECTOR_H
#define BTJ_VECTOR_H

#include <vector>
#include "btj_aligned_allocator.h"

namespace btj
{

template<typename T>
using Vector = std::vector<T, AlignedAllocator<T>>;

}

#endif
