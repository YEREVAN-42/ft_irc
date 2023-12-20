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

	if (args.size() > 3)
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

	
	std::size_t found = args[1].find_first_not_of("+-itkol");

	if (found != std::string::npos || (args[1][0] != '-' && args[1][0] != '+'))
		user->reply(ERR_UNKNOWNMODE(args[1]));

	std::string flags = "";

	for (size_t i = 1; i < args[1].size(); ++i)
	{
		if (flags.find(args[1][i]) == std::string::npos)
		{
			flags += args[1][i];
		}
	}

	//stexic heto petq a stugel ka errord argument te che u ete ka vor flagi het a vorovhetev kaxvac dranic tarber baner petq a ani
	//orinak senc------ MODE #Finnish +o Kilroy(es depqum petq a es Kilroy-in admini privilegia ta, minusi depqum el de hakaraky)
	//kam senc------ MODE #eu-opers +l 10(es depqum vonc haskanum em petq a limity darcni 10)
	//kam daje senc------ MODE #42 +k oulu(es depqum el channel-i passwordy darncni oulu)
	// std::string	user_name;
	// if (args.size() == 3)
	// 	user_name = args[2];

	// User *dest = _server->getUser(user_name);
    // if (!dest)
    // {
    //     user->reply(ERR_NOSUCHNICK(user->getNickName(), user_name));
    //     return;
    // }

    // if (!dest->getChannel() || dest->getChannel() != channel)
    // {
    //     user->reply(ERR_USERNOTINCHANNEL(user->getNickName(), dest->getNickName(), user_name));
    //     return;
    // }

	if (args[1][0] == '+')
	{
		int i = 0;
		while(flags[i])
		{
			std::cout << flags[i] << std::endl;
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
	else if (args[1][0] == '-')
	{
		int i = 0;
		while(flags[i])
		{
			switch (flags[i])
			{
				// case 'i':
				// 	channel->removeInvMode();
				// 	break ;
				case 't':
					channel->removeTopic();
					break ;
				case 'k':
					channel->removeKey();
					break ;
				case 'o':
					channel->takeOperator(user);
					break ;
				case 'l':
					channel->removeLimit();
					break ;
			}
			++i;
		} 
	}
}
