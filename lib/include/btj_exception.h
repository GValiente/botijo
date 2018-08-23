/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_EXCEPTION_H
#define BTJ_EXCEPTION_H

#include <stdexcept>

namespace btj
{

using Exception = std::exception;

class QuitException : public Exception
{

public:
    const char* what() const noexcept override
    {
	return "Application has closed";
    }
};

}

#endif
