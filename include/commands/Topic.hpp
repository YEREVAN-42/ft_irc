#ifndef __TOPIC_HPP__
# define __TOPIC_HPP__

#include "User.hpp"
#include "Server.hpp"
#include "Command.hpp"
#include "Channel.hpp"

namespace irc
{
	class Topic : public Command
	{
		public:
			Topic(Server *server);
			~Topic();

		void    execute(User* user, std::vector<std::string> args);
	};
}

#endif //__TOPIC_HPP__