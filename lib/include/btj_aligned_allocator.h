/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_ALIGNED_ALLOCATOR_H
#define BTJ_ALIGNED_ALLOCATOR_H

#include <new>
#include <memory>

namespace btj
{

// https://stackoverflow.com/questions/12942548/making-stdvector-allocate-aligned-memory
// https://stackoverflow.com/questions/12504776/aligned-malloc-in-c

void* alignedMalloc(std::size_t alignment, std::size_t size);

void alignedFree(void* ptr) noexcept;


enum class Alignment : std::size_t
{
    Normal = sizeof(void*),
    SSE    = 16,
    AVX    = 32,
};


template<typename T, Alignment Align = Alignment::AVX>
class AlignedAllocator;


template<Alignment Align>
class AlignedAllocator<void, Align>
{

public:
    typedef void* pointer;
    typedef const void* const_pointer;
    typedef void value_type;

    template<class U> struct rebind
    {
        typedef AlignedAllocator<U, Align> other;
    };
};


template<typename T, Alignment Align>
class AlignedAllocator
{

public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef std::true_type propagate_on_container_move_assignment;

    template<class U>
    struct rebind
    {
        typedef AlignedAllocator<U, Align> other;
    };

public:
    AlignedAllocator() noexcept
    {
    }

    template<class U>
    AlignedAllocator(const AlignedAllocator<U, Align>&) noexcept
    {
    }

    size_type max_size() const noexcept
    {
        return (size_type(~0) - size_type(Align)) / sizeof(T);
    }

    pointer address(reference x) const noexcept
    {
        return std::addressof(x);
    }

    const_pointer address(const_reference x) const noexcept
    {
        return std::addressof(x);
    }

    pointer allocate(size_type n, typename AlignedAllocator<void, Align>::const_pointer = nullptr)
    {
        auto alignment = static_cast<size_type>(Align);
        auto ptr = alignedMalloc(alignment, n * sizeof(T));

        if(! ptr)
        {
            throw std::bad_alloc();
        }

        return reinterpret_cast<pointer>(ptr);
    }

    void deallocate(pointer p, size_type) noexcept
    {
        alignedFree(p);
    }

    template<class U, class ...Args>
    void construct(U* p, Args&&... args)
    {
        ::new(reinterpret_cast<void*>(p)) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p)
    {
        p->~T();
    }
};


template<typename T, Alignment TAlign, typename U, Alignment UAlign>
bool operator==(const AlignedAllocator<T, TAlign>&, const AlignedAllocator<U, UAlign>&) noexcept
{
    return TAlign == UAlign;
}

template<typename T, Alignment TAlign, typename U, Alignment UAlign>
bool operator!=(const AlignedAllocator<T, TAlign>&, const AlignedAllocator<U, UAlign>&) noexcept
{
    return TAlign != UAlign;
}

}

#endif
