#include "Topic.hpp"

irc::Topic::Topic(Server* server) : Command(server){}
irc::Topic::~Topic(){}

// syntax: TOPIC <channel> [ <topic> ] :<another topic>

/** 
 * The TOPIC command is used to change or view the topic of a channel.
 *
 * @param   <channel> [ <topic> ]
 * @return   nothing
 */
void	irc::Topic::execute(User* user, std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		user->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "Topic"))
	}

	std::string channel_name = args[0];
	std::string topic = args[1];
	std::string second_topic = args[2];

	Channel *channel = user->getChannel();
    if (!channel || channel->getName() != channel_name)
    {
        user->reply(ERR_NOTONCHANNEL(user->getNickName(), channel_name));
        return;
    }

	if (channel->getAdmin() != user_name)
    {
        user->reply(ERR_CHANOPRIVSNEEDED(user->getNickName(), channel_name));
        return;
    }
	channel->topic(user, dest, second_topic);
}