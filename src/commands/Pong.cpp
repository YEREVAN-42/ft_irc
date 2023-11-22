#include "Command.hpp"

irc::Pong::Pong(Server* server) : Command(server) {	}
irc::Pong::~Pong() {	}

//	syntax: PONG <server1> [<server2>]

void	irc::Pong::execute(User* user, std::vector<std::string> args)
{
	if (args.empty())
	{
		user->reply(ERR_NEEDMOREPARAMS(user->getNickName(), "PONG"));
		return ;
	}
	user->write(RPL_PING(user->getPrefix(), args.at(0)));
}