#include "irc.hpp"

void ValidInput(int argNum, const char* argVal[])
{
	if (argNum != 3)
	{
		irc::ErrorMessage("Wrong number of arguments!!!",
				"Try again like:\t ./ircserv <port> <password>" );
		exit(EXIT_FAILURE);
	}

	if (std::string(argVal[1]).find_first_not_of("0123456789")
				!= std::string::npos)
	{
		irc::ErrorMessage("Invalid input for <port>!!!", "Try again:");
		exit(EXIT_FAILURE);
	}

	int port = std::atoi(argVal[1]);

	if (port > 65535)
	{
		irc::ErrorMessage("Wrong PORT specified!!!", "Please input a valid PORT.\n"\
				"It must be a number in the range [0, 65535].");
		exit(EXIT_FAILURE);
	}
}

int main(int arg, const char* argv[])
{
	ValidInput(arg, argv);

	// irc::Server server(std::atoi(argv[1]), argv[2]);

	std::cout << BOLDGREEN << "Server are creating." << RESET << std::endl;


	return 0;
}
