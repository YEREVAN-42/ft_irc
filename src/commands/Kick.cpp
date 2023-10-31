#include "Kick.hpp"
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
irc::Kick::execute(User* user, std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		user->/* reply */(ERR_NEEDMOREPARAMS(client->/* getNickname() */, "KICK"))
	}

	std::string channel_name = args[0];
	std::string user_name = args[1];
	std::string reason = "No reason specified!";

	if (args.size() >= 3 && (args[2][0] != ':' || args[2].size() > 1))
	{
		reason = "";

		std::vector<std::string>::iterator it = args.begin();
		std::vector<std::string>::iterator end = args.end();

		while (it != end)
		{
			reason.append(*it + " ");
			it++
		}
	}

	Channel *channel = user->/* getChannel() */;
    if (!channel || channel->/* getName() */ != channel_name)
    {
        user->/* reply */(ERR_NOTONCHANNEL(user->/* getNickname() */, channel_name));
        return;
    }

	if (channel->/* get_admin() */ != user_name)
    {
        user->/* reply */(ERR_CHANOPRIVSNEEDED(user->/* get_nickname() */, channel_name));
        return;
    }

	User *dest = _server->/* get_client */(user_name);
    if (!dest)
    {
        user->/* reply */(ERR_NOSUCHNICK(user->/* get_nickname() */, user_name));
        return;
    }

    if (!dest->/* get_channel() */ || dest->/* get_channel() */ != channel)
    {
        user->/* reply */(ERR_USERNOTINCHANNEL(user->/* get_nickname() */, dest->/* get_nickname() */, user_name));
        return;
    }

	channel->/* kick */(user, dest, reason);
}