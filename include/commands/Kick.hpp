#ifndef __KICK_HPP__
# define __KICK_HPP__

#include "User.hpp"
#include "Server.hpp"
#include "Command.hpp"

namespace irc
{
	class Kick : public Command
	{
		public:
			Kick(/* args */);
			~Kick();

		void    execute(User* user, std::vector<std::string> args);
	};
}

#endif //__KICK_HPP__