/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_STRING_H
#define BTJ_STRING_H

#include <string>
#include "btj_string_view.h"

namespace btj
{

class String : public std::string
{

public:
    String() noexcept
    {
    }

    String(const char* charArray) :
        std::string(charArray)
    {
    }

    String(const StringView& stringView) :
        std::string(stringView.data(), stringView.size())
    {
    }

    String(const std::string& other) :
        std::string(other)
    {
    }

    String(std::string&& other) noexcept :
        std::string(std::move(other))
    {
    }

    String(const String& other) :
        std::string(other)
    {
    }

    String& operator=(const String& other)
    {
        static_cast<std::string&>(*this) = other;
        return *this;
    }

    String(String&& other) noexcept :
        std::string(std::move(other))
    {
    }

    String& operator=(String&& other) noexcept
    {
        static_cast<std::string&>(*this) = std::move(other);
        return *this;
    }
};

static_assert(std::is_copy_constructible<String>::value, "");
static_assert(std::is_copy_assignable<String>::value, "");
static_assert(std::is_nothrow_move_constructible<String>::value, "");
static_assert(std::is_nothrow_move_assignable<String>::value, "");

}


namespace std
{
    template<>
    struct hash<btj::String>
    {
        std::size_t operator()(const btj::String& idsString) const
        {
            return hash<std::string>()(idsString);
        }
    };
}

#endif
