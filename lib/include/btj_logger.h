/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_LOGGER_H
#define BTJ_LOGGER_H

#include <iostream>

namespace btj
{

#define BTJ_LOG_MESSAGE std::cout << '[' << btj::detail::baseName(__FILE__) << "::" << __LINE__ << "] "

#define BTJ_LOG_ERROR std::cerr << '[' << btj::detail::baseName(__FILE__) << "::" << __LINE__ << "] "

namespace detail
{
    template<unsigned int Size>
    constexpr const char* baseNameImpl(const char (&charArray)[Size], unsigned int index) noexcept
    {
        return index >= Size ?
                    charArray :
                    charArray[Size - index] == '/' ?
                        charArray + Size - index + 1 :
                        baseNameImpl(charArray, index + 1);
    }

    template<unsigned int Size>
    constexpr const char* baseName(const char (&charArray)[Size]) noexcept
    {
        return baseNameImpl(charArray, 2);
    }
}

}

#endif
