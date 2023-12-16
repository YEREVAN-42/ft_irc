#include "Command.hpp"

irc::Pass::Pass(Server* server, bool auth)
	: Command(server, auth)
{	}
irc::Pass::~Pass()
{	}

// syntax: PASS <password>

void	irc::Pass::execute(User* user, const std::vector<std::string>& args)
{
	if (args.empty())
	{
		user->reply(ERR_NEEDMOREPARAMS(user->getNickName(), "PASS"));
		return ;
	}

	if (user->isRegistered())
	{
		user->reply(ERR_ALREADYREGISTERED(user->getNickName()));
		return ;
	}

	if (this->_server->getPassword() == args[0].substr((args[0][0] == ':') ? 1 : 0))
	{
		user->reply(ERR_PASSWDMISMATCH(user->getNickName()));
		return ;
	}
	user->setState(User::LOGIN);
}