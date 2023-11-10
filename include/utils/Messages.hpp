#ifndef  __MESSAGES_HPP__
# define __MESSAGES_HPP__

# include <cstring>
# include <iostream>

# include "Colors.hpp"

namespace irc
{
	void	ErrorMessage(const char* errType, const char* message);
	void	ErrorMessageFromErrno(const char* funcName, const char* message, int erno);
}

#endif // __MESSAGES_HPP__
