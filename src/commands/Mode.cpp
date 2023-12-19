#include "Command.hpp"

irc::Mode::Mode(Server* server) : Command(server){}
irc::Mode::~Mode(){}

void	irc::Mode::execute(User* user, const std::vector<std::string>& args)
{
	
	if (args.size() < 2)
	{
		user->reply(ERR_NEEDMOREPARAMS(user->getNickName(), "MODE"));
		return;
	}

	if (args.size() > 2)
	{
		user->reply(ERR_TOOMENYPARAMS(user->getNickName(), "MODE"));
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

	std::size_t found = args[1].find_first_not_of("-itkol");

	if (found != std::string::npos || args[1][0] != '-')
		user->reply(ERR_UNKNOWNMODE(args[2]));

	std::string flags = "";

	for (size_t i = 1; i < args[1].size(); ++i)
	{
		if (flags.find(args[1][i]) == std::string::npos)
		{
			flags += args[1][i];
		}
	}

	int i = 0;
	while(flags[i])
	{
		switch (flags[i])
		{
			case 'i':
				channel->mode(Channel::INV_ONLY);
				break ;
			case 't':
				channel->mode(Channel::REST_TOPIC);
				break ;
			case 'k':
				channel->mode(Channel::PRIVATE_KEY);
				break ;
			case 'o':
				channel->mode(Channel::OPER_PRIVILEGE);
				break ;
			case 'l':
				channel->mode(Channel::USER_LIMIT);
				break ;
		}
		++i;
	}
}
