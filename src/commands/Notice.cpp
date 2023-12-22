#include "Command.hpp"

irc::Notice::Notice(Server* server) : Command(server){}
irc::Notice::~Notice(){}

void	irc::Notice::execute(User* user, const std::vector<std::string>& args)
{
	 if (args.size() < 2 || args[0].empty() || args[1].empty())
    {
        user->reply(ERR_NEEDMOREPARAMS(user->getNickName(), "NOTICE"));
        return;
    }

	std::string channel_name = args[0];
    std::string message;

    std::vector<std::string>::const_iterator first = args.begin() + 1;
    std::vector<std::string>::const_iterator last = args.end();

	while (first != last)
    {
        message.append(*first + " ");
        first++;
    }

	if (message[0] == ':')
        message = message.substr(1);

	if (message.at(0) == '#')
	{
		Channel* channel = user->getChannel();

		if(!channel)
		{
			user->reply(ERR_NOSUCHCHANNEL(user->getNickName(), channel_name));
			return;
		}

		if (!channel->getExtMsg())
		{
			std::vector<std::string> nicknames = channel->getNickNames();

			std::vector<std::string>::iterator first = nicknames.begin();
			std::vector<std::string>::iterator last = nicknames.end();

			while (first != last)
			{
				if (*first == user->getNickName())
					break;
				first++;
			}

			if (first == last)
			{
				user->reply(ERR_CANNOTSENDTOCHAN(user->getNickName(), channel_name));
				return;
			}
		}
		channel->broadcast(RPL_PRIVMSG(user->getPrefix(), channel_name, message), user->getNickName());
		return;
	}

	User  *dest = _server->getUser(channel_name);
    if (!dest)
    {
      user->reply(ERR_NOSUCHNICK(user->getNickName(), channel_name));
			return;
    }

    dest->write(RPL_PRIVMSG(user->getPrefix(), channel_name, message));
}