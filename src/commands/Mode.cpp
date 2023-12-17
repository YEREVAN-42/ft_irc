#include "Command.hpp"

irc::Mode::Mode(Server* server) : Command(server){}
irc::Mode::~Mode(){}

void	irc::Mode::execute(User* user, const std::vector<std::string>& args)
{
	if (args.empty())
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

	if (channel->getAdmin() != user)
    {
        user->reply(ERR_CHANOPRIVSNEEDED(user->getNickName(), channel_name));
        return;
    }

	if (args.empty())
    {
        user->reply(ERR_NEEDMOREPARAMS(user->getNickName(), "MODE"));
        return;
    }

	std::string	channel_name = args[1];

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

	// std::size_t found = args[2].find_first_not_of("itkol ");

	// if (found != std::string::npos)
	// 	user->reply(ERR_UNKNOWNMODE(m));

	//  while(args[2][i])
	//  {
	// 	if (args[2][i] == 'i')
	// 		channel->mode(INV_ONLY);
	// 	else if (args[2][i] == 't')
	// 		channel->mode(REST_TOPIC);
	// 	else if (args[2][i] == 'k')
	// 		channel->mode(PRIVATE_KEY);
	// 	else if (args[2][i] == 'o')
	// 		channel->mode(OPER_PRIVILEGE);
	// 	else if (args[2][i] == 'l')
	// 		channel->mode(USER_LIMIT);
	// 	i++;
	//  }
}