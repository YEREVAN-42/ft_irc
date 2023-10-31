#include "Invite.hpp"

irc::Invite::Invite(Server* server) : Command(server){}
irc::Invite::~Invite(){}

// syntax: INVITE <nickname> <channel>

/** 
 * The INVITE command is used to invite a user to a channel.
 *
 * @param   <nickname> <channel>
 * @return   nothing
 */

void	irc::Invite::execute(User* user, std::vector<std::string> args)
{
	if (args.empty())
    {
        user->/*inchvoranun*/(ERR_NEEDMOREPARAMS(user->/* getNickname() */, "INVITE"));
        return;
    }

	std::string user_name = args[0];
	std::string channel_name = args[1];
	
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

	//there will be called channel member function for inviting user to channel
}