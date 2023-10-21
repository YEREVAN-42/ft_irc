#include "../include/utils/Messages.hpp"

void	irc::ErrorMessage(const char* errorType, const char* message)
{
	if (errorType != NULL)
	{
		std::cerr
				<< BOLDRED
				<< errorType 
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
}
