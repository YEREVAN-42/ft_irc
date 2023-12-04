#include "Command.hpp"

irc::Nick::Nick(Server* server, bool auth)
	: Command(server, auth)
{	}
irc::Nick::~Nick()
{	}

// syntax: NICK <nickname>

void irc::Nick::execute(User* user, std::vector<std::string> args)
{
	if (args.empty() || args[0].empty())
	{
		user->reply(ERR_NONICKNAMEGIVEN(user->getNickName()));
		return ;
	}

	std::string nick(args[0]);

	if (_server->getUser(nick))
	{
		user->reply(ERR_NICKNAMEINUSE(user->getNickName()));
		return ;
	}

	user->setNickName(nick);
	user->welcome();
}
