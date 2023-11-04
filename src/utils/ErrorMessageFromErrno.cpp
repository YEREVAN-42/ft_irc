#include "Messages.hpp"

void	irc::ErrorMessageFromErrno(const char* funcName, int errno)
{
	if (funcName != NULL)
	{
		std::cerr
				<< BOLDRED
				<< "ERROR: in this function "
				<< funcName
				<< RESET
				<< std::endl;
	}

	std::cerr
			<< BOLDYELLOW
			<< "ERROR TYPE:\n"
			<< std::strerror(errno)
			<< RESET
			<< std::endl;
}

