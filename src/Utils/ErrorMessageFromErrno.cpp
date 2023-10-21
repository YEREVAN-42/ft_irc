#include "../include/Utils/Messages.hpp"

void irc::ErrorMessageFromErrno(const char* funcName, int errno)
{
	if (funcName != NULL)
	{
		std::cout
				<< BOLDRED
				<< "ERROR: in this function "
				<< funcName
				<< RESET
				<< std::endl;
	}

	std::cout
			<< BOLDYELLOW
			<< "ERROR TYPE:\n"
			<< std::strerror(errno)
			<< RESET
			<< std::endl;
}

