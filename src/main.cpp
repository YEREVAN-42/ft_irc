#include "irc.hpp"
#include "Colors.hpp"
// #include "Server.hpp"

void ValidInput(int argNum, const char* argVal[])
{
	if (argNum != 3)
	{
		std::cout
				<< BOLDRED
				<< "Wrong number of arguments!!!" << std::endl
				<< BOLDYELLOW
				<< "Try again like:\t ./ircserv <port> <password>" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (std::string(argVal[1]).find_first_not_of("0123456789") != std::string::npos)
	{
		std::cout
				<< BOLDRED
				<< "Invalid input for <port>!!!" << std::endl
				<< BOLDYELLOW
				<< "Try again:" << std::endl;
		exit(EXIT_FAILURE);
	}
	int port = std::atoi(argVal[1]);
	if (port < 0 || port > 65535)
	{
		std::cout
				<< BOLDRED
				<< "Wrong PORT specified!!!" << std::endl
				<< BOLDYELLOW
				<< "Please input a valid PORT." << std::endl
				<< "It must be a number in the range [0, 65535]." << std::endl;
		exit(EXIT_FAILURE);
	}
}

int main(int arg, const char* argv[])
{
	ValidInput(arg, argv);

	return 0;
}
