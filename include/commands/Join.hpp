#ifndef __JOIN_HPP__
# define __JOIN_HPP__

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "Command.hpp"

namespace irc
{
	class Join : public Command
	{
		public:
			Join(Server *server);
			~Join();

		void    execute(User* user, std::vector<std::string> args);
	};
}

#endif //__JOIN_HPP__