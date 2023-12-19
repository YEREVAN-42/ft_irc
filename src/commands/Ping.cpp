#include "Command.hpp"

irc::Ping::Ping(Server* server) : Command(server) {	}
irc::Ping::~Ping() {	}

//	syntax: PING <server1> [<server2>]

void	irc::Ping::execute(User* user, const std::vector<std::string>& args)
{
	if (args.empty())
	{
		user->reply(ERR_NEEDMOREPARAMS(user->getNickName(), "PING"));
		return ;
	}
	user->write(RPL_PING(user->getPrefix(), args.at(0)));
}