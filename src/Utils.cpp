#include "Utils.hpp"

void ErrorMessage(const char* errorType, const char* message)
{
	if (errorType != NULL)
	{
		std::cout
				<< BOLDRED
				<< errorType 
				<< RESET
				<< std::endl;
	}

	if (message != NULL)
	{
		std::cout
				<< BOLDYELLOW
				<< message
				<< RESET
				<< std::endl;
	}
}
