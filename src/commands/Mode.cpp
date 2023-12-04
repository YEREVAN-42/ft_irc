#include "Command.hpp"

irc::Mode::Mode(Server* server) : Command(server){}
irc::Mode::~Mode(){}

void	irc::Mode::execute(User* user, std::vector<std::string> args)
{
	if (args.empty())
    {
        user->reply(ERR_NEEDMOREPARAMS(user->getNickName(), "MODE"));
        return;
    }

	std::string	channel_name = args[0];

	Channel* channel = _server->getChannel(channel_name);

	if (!channel)
    {
        user->reply(ERR_NOSUCHCHANNEL(user->getNickName(), channel_name));
        return;
    }

	if (channel->getAdmin() != user)
    {
        user->reply(ERR_CHANOPRIVSNEEDED(user->getNickName(), channel_name));
        return;
    }

	//to be continued
}