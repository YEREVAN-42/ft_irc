#include "Command.hpp"

irc::UserCom::UserCom(Server* server, bool auth)
	: Command(server, auth)
{	}
irc::UserCom::~UserComm()
{	}

void irc::UserCom::execute(User* user, std::vector<std::string> args)
{
	if (args.)
}