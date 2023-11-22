#include "Command.hpp"

irc::Pass::Pass(Server* server, bool auth)
	: Command(server, auth)
{	}
irc::Pass::~Pass()

// syntax: PASS <password>

void	irc::Pass::execute(User* user, std::verctor<std::string> args)
{
	if (args.empty())
	{
		user->reply(ERR_NEEDMOREPARAMS(user->getNikeName(), "PASS"));
		return ;
	}

	if (user->isRegistered())
	{
		
	}
}