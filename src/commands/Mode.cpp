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
	//kam daje senc------ MODE #42 +k oulu(es depqum el channel-i passwordy darcni oulu)
	User *dest;
	if (args.size() == 3 && args[1][1] == 'o')
	{
		_user_name = args[2];

		dest = _server->getUser(_user_name);
		if (!dest)
		{
			user->reply(ERR_NOSUCHNICK(user->getNickName(), _user_name));
			return;
		}

		if (!dest->getChannel() || dest->getChannel() != channel)
		{
			user->reply(ERR_USERNOTINCHANNEL(user->getNickName(), dest->getNickName(), _user_name));
			return;
		}
	}

	if (args.size() == 3 && args[1][1] == 'l')
	{
		int	pass = 0;
		std::istringstream(args[2]) >> pass;
		if (pass > 0 && pass < MAX_LIMIT)
			_limit = pass;
	}


	// if (args[1][0] == '+')
	// {
	// 	int i = 0;
	// 	while(flags[i])
	// 	{
	// 		switch (flags[i])
	// 		{
	// 			case 'i':
	// 				channel->mode(Channel::INV_ONLY);
	// 				break ;
	// 			case 't':
	// 				channel->mode(Channel::REST_TOPIC);
	// 				break ;
	// 			case 'k':
	// 				channel->mode(Channel::PRIVATE_KEY);
	// 				break ;
	// 			case 'o':
	// 				channel->mode(Channel::OPER_PRIVILEGE);
	// 				break ;
	// 			case 'l':
	// 				channel->mode(Channel::USER_LIMIT);
	// 				break ;
	// 		}
	// 		++i;
	// 	} 
	// }
	if (args[1][0] == '+')
	{
		if (flags[0] == 'i')
			channel->mode(Channel::INV_ONLY);
		else if (flags[0] == 't')
			channel->mode(Channel::REST_TOPIC);
		else if (flags[0] == 'k')
		{
			channel->mode(Channel::PRIVATE_KEY);
			channel->setKey(args[2]);
		}
		else if (flags[0] == 'o')
		{
			channel->mode(Channel::OPER_PRIVILEGE);
			channel->giveOperator(dest);
		}
		else if (flags[0] == 'l')
		{
			channel->mode(Channel::USER_LIMIT);
			channel->setLimit(_limit);
		}
	}
	else if (args[1][0] == '-')
	{
		if (flags[0] == 'i')
		{
			// 	channel->removeInvMode();
		}
		else if (flags[0] == 't')
			channel->removeTopic();
		else if (flags[0] == 'k')
			channel->removeKey();
		else if (flags[0] == 'o')
			channel->takeOperator(dest);
		else if (flags[0] == 'l')
			channel->removeLimit();
	} 

}
