#ifndef __KICK_HPP__
# define __KICK_HPP__

#include "User.hpp"
#include "Server.hpp"
#include "Command.hpp"
#include "Channel.hpp"

namespace irc
{
	class Kick : public Command
	{
		public:
			Kick(Server *server);
			~Kick();

		void    execute(User* user, std::vector<std::string> args);
	};
}

#endif //__KICK_HPP__