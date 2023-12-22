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

	std::string	channel_name = args[0];

	Channel* channel = _server->getChannel(channel_name);

	if (!channel)
	{
		user->reply(ERR_NOSUCHCHANNEL(user->getNickName(), channel_name));
		return;
	}

	if (channel->getAdmin() != user && user->getPrivilege() == false)
	{
		user->reply(ERR_CHANOPRIVSNEEDED(user->getNickName(), channel_name));
		return;
	}

	
	std::size_t found = args[1].find_first_not_of("+-itkol");

	if ((found != std::string::npos) || (args[1].size() != 2)\
			|| (args[1][1] == '-') || (args[1][1] == '+'))
	{
		user->reply(ERR_UNKNOWNMODE(args[1]));
		return ;
	}

	const char mode          = args[1][0];
	const char flag          = args[1][1];

	//stexic heto petq a stugel ka errord argument te che u ete ka vor flagi het a vorovhetev kaxvac dranic tarber baner petq a ani
	//orinak senc------ MODE #Finnish +o Kilroy(es depqum petq a es Kilroy-in admini privilegia ta, minusi depqum el de hakaraky)
	//kam senc------ MODE #eu-opers +l 10(es depqum vonc haskanum em petq a limity darcni 10)
	//kam daje senc------ MODE #42 +k oulu(es depqum el channel-i passwordy darcni oulu)

	User* _user = NULL;

	if (mode == '+')
	{
		switch (flag)
		{
			case 'i':
				if (args.size() != 2)
				{
					user->reply("Wrong count of parameters.");
					return ;
				}

				channel->mode(Channel::INV_ONLY);
				break ;
			case 't':
				if (args.size() != 2)
				{
					user->reply("Wrong count of parameters.");
					return ;
				}

				channel->mode(Channel::REST_TOPIC);
				break ;
			case 'k':
				if (args.size() != 3)
				{
					user->reply("Wrong count of parameters.");
					return ;
				}

				channel->mode(Channel::PRIVATE_KEY);
				channel->setKey(args[2]);
				break ;
			case 'o':
				if (args.size() != 3)
				{
					user->reply("Wrong count of parameters.");
					return ;
				}

				_user = _server->getUser(args[2]);

				if (!_user)
				{
					user->reply(ERR_NOSUCHNICK(user->getNickName(), args[2]));
					return;
				}

				if (!_user->getChannel() || _user->getChannel() != channel)
				{
					user->reply(ERR_USERNOTINCHANNEL(user->getNickName(), _user->getNickName(), args[2]));
					return;
				}

				channel->mode(Channel::OPER_PRIVILEGE);
				channel->giveOperator(_user);
				break ;
			case 'l':
				if (args.size() != 3)
				{
					user->reply("Wrong count of parameters.");
					return ;
				}

				if ((args[2].find_first_not_of("1234567890") != std::string::npos)\
						|| (std::atoi(args[2].c_str()) > MAX_LIMIT) || (std::atoi(args[2].c_str()) == 0))
				{
					user->reply("Please input a valid limit for channel.\n It must be a number in the range (0, 65535].");
					return ;
				}
				size_t _limit = std::atoi(args[2].c_str());
				channel->mode(Channel::USER_LIMIT);
				channel->setLimit(_limit);
				break ;
		}
	}
	else
	{
		switch (flag)
		{
			case 'i':
				// channel->removeInvMode();	
				break ;
			case 't':
				// channel->removeTopicMode();
				break ;
			case 'k':
				// channel->removeKeyMode();
				break ;
			case 'o':
				// channel->takeOperator(dest);
				break ;
			case 'l':
				// channel->removeLimitMode();
				break ;
		}
	}

}
