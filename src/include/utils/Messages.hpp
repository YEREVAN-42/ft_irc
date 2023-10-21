#ifndef  __MESSAGES_HPP__
# define __MESSAGES_HPP__

# include <cstring>
# include <iostream>

# include "../color/Colors.hpp"

namespace irc
{
	void ErrorMessage(const char* errType, const char* message);
	void ErrorMessageFromErrno(const char* funcName, int errno);
}

#endif // __MESSAGES_HPP__
