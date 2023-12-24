#include "Command.hpp"

irc::PrivMsg::PrivMsg(Server* server) : Command(server) { }
irc::PrivMsg::~PrivMsg() { }

//syntax: PRIVMSG <receiver>: <text to be sent>

void	irc::PrivMsg::execute(User* user, const std::vector<std::string>& args)
{
	if (args.size() < 2 || args[0].empty() || args[1].empty())
  {
		user->reply(ERR_NEEDMOREPARAMS(user->getNickName(), "PRIVMSG"));
		return;
	}

	if (user->isRegistered() == false)
	{
		user->reply(ERR_NOTREGISTERED("Current user"));
		return;
	}

	std::string receiver = args.at(0);
	std::string message = "";

	std::vector<std::string>::const_iterator first = args.begin() + 1;
	std::vector<std::string>::const_iterator last = args.end();

	while (first != last)
	{
		message.append(*first + ' ');
		++first;
	}

	if (message.at(0) == ':')
    message = message.substr(1);

	if (receiver.at(0) == '#')
	{
		Channel* channel = user->getChannel();

		if(!channel)
		{
			user->reply(ERR_NOSUCHCHANNEL(user->getNickName(), receiver));
			return;
		}
		
		if (!channel->getExtMsg() && channel->getAdmin() != user)
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
				user->reply(ERR_CANNOTSENDTOCHAN(user->getNickName(), receiver));
				return;
			}
		}
		channel->broadcast(RPL_PRIVMSG(user->getPrefix(), receiver, message), user->getNickName());
    return;
	}
	
	User  *dest = _server->getUser(receiver);
  if (!dest)
  {
    user->reply(ERR_NOSUCHNICK(user->getNickName(), receiver));
		return;
  }

  dest->write(RPL_PRIVMSG(user->getPrefix(), receiver, message));
}