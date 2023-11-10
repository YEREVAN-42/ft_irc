#include "Messages.hpp"

void	irc::ErrorMessageFromErrno(const char* funcName, const char* message, int erno)
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

	if (message != NULL)
	{
		std::cerr
				<< BOLDYELLOW
				<< message
				<< RESET
				<< std::endl;
	}

	std::cerr
			<< BOLDYELLOW
			<< "ERROR TYPE:\n"
			<< std::strerror(erno)
			<< RESET
			<< std::endl;

	exit(EXIT_FAILURE);
}

