/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "btj_aligned_allocator.h"

#include "btj_assert.h"
#include "btj_logger.h"

namespace btj
{

void* alignedMalloc(std::size_t alignment, std::size_t size)
{
    BTJ_ASSERT(alignment >= sizeof(void*));

    auto offset = alignment - 1 + sizeof(void*);
    auto p1 = std::malloc(size + offset);

    if(! p1)
    {
        BTJ_LOG_ERROR << "std::malloc call failed: " << alignment << " - " << size << std::endl;
        return nullptr;
    }

    auto p2 = reinterpret_cast<void**>((std::size_t(p1) + offset) &~ (alignment - 1));
    p2[-1] = p1;
    return p2;
}

void alignedFree(void* ptr) noexcept
{
    if(ptr)
    {
        ptr = (static_cast<void**>(ptr))[-1];
    }
}

}
