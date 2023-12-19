#include "Command.hpp"

irc::Quit::Quit(Server* server, bool auth) : Command(server, auth) {}

irc::Quit::~Quit() {}

// syntax: QUIT [<message>]

void    irc::Quit::execute(User* user, const std::vector<std::string>& args)
{
	std::string reason;

	if (args.empty())
    	reason = "Leaving...";
	else
		reason = args[0];

	if (reason[0] == ':')
		reason = reason.substr(1);

  user->write(RPL_QUIT(user->getPrefix(), reason));
	_server->onUserDisconnect(user->getFd());
}