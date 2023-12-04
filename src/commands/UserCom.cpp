#include "Command.hpp"

irc::UserCom::UserCom(Server* server, bool auth)
	: Command(server, auth)
{	}
irc::UserCom::~UserCom()
{	}

// syntax: USER <username> <hostname> <servername> <realname>

void irc::UserCom::execute(User* user, std::vector<std::string> args)
{
	if (args.size() < 4)
	{
		user->reply(ERR_NEEDMOREPARAMS(user->getNickName(), "USER"));
		return ;
	}

	if (user->isRegistered())
	{
		user->reply(ERR_ALREADYREGISTERED(user->getNickName()));
		return ;
	}

	user->setUserName(args[0]);
	user->setHostName(args[1]);
	user->setRealName(args[3]);
	user->welcome();
}