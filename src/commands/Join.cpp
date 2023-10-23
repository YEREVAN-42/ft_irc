#include "Join.hpp"

irc::Join::Join(Server* server) : Command(server){}
irc::Join::~Join(){}

// syntax: JOIN <channels> [<keys>]

/** 
 * The JOIN command is used by a user to request to start listening to
   the specific channel.
 *
 * @param   <channel> *( "," <channel> ) <user> *( "," <user> )
               [<comment>]
 * @return   no
 */

void    Join::execute(User* user, std::vector<std::string> args)
{
    if (args.empty())
    {
        user->/*inchvoranun*/(ERR_NEEDMOREPARAMS(user->/* getNickname() */, "JOIN"));
        return;
    }

    std::string user_name = args[0];
	std::string pass;
	if (args.size() > 1)
		pass = args[1];
	else
		pass = "";

    Channel *channel = user->/* getChannel */;
	if (channel) 
    {
		user->/*inchvoranun*/(ERR_TOOMANYCHANNELS(user->/* getNickname() */, user_name));
		return;
	}

    channel = server->/* getChannel(user_name) */;
	if (!channel)
		channel = server->/* create_channel(user_name, pass, user) */;

    if (channel->/* getLimit */ > 0 && channel->/* getSize() */ >= channel->/* getLimit */)
    {
		user->/*inchvoranun*/(ERR_CHANNELISFULL(user->/* getNickname() */, user_name));
		return;
	}

    if (channel->get_key() != pass) 
    {
		user->/*inchvoranun*/(ERR_BADCHANNELKEY(user->/* getNickname() */, user_name));
		return;
	}

	user->/* join(channel) */;
}