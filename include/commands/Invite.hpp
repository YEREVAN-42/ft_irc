#ifndef __INVITE_HPP__
# define __INVITE_HPP__

#include "User.hpp"
#include "Server.hpp"
#include "Command.hpp"

namespace irc
{
	class Invite : public Command
	{
		public:
			Invite(/* args */);
			~Invite();

		void    execute(User* user, std::vector<std::string> args);
	};
}

#endif //__INVITE_HPP__