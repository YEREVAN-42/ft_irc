#include "Command.hpp"

irc::Kick::Kick(Server* server) : Command(server){}
irc::Kick::~Kick(){}

// syntax: KICK <channel> <client> :[<message>]

/** 
 * The KICK command can be used to request the forced removal of a user
   from a channel.
 *
 * @param   <channel> *( "," <channel> ) <user> *( "," <user> )
               [<comment>]
 * @return   nothing
 */
void	irc::Kick::execute(User* user, const std::vector<std::string>& args)
{
	if (args.size() < 2)
	{
		user->reply(ERR_NEEDMOREPARAMS(user->getNickName(), "KICK"));
		return ;
	}

	std::string channel_name = args[0];
	std::string user_name = args[1];
	std::string reason = "No reason specified!";

	if (args.size() >= 3 && (args[2][0] != ':' || args[2].size() > 1))
	{
		reason = "";

		std::vector<std::string>::const_iterator it = args.begin();
		std::vector<std::string>::const_iterator end = args.end();

		while (it != end)
		{
			reason.append(*it + " ");
			it++;
		}
	}

	Channel *channel = user->getChannel();
    if (!channel || channel->getName() != channel_name)
    {
        user->reply(ERR_NOTONCHANNEL(user->getNickName(), channel_name));
        return;
    }

	if (channel->getAdmin() != user && user->getPrivilege() == false)
    {
        user->reply(ERR_CHANOPRIVSNEEDED(user->getNickName(), channel_name));
        return;
    }

	User *dest = _server->getUser(user_name);
    if (!dest)
    {
        user->reply(ERR_NOSUCHNICK(user->getNickName(), user_name));
        return;
    }

    if (!dest->getChannel() || dest->getChannel() != channel)
    {
        user->reply(ERR_USERNOTINCHANNEL(user->getNickName(), dest->getNickName(), user_name));
        return;
    }

	channel->kick(user, dest, reason);
}