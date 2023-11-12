#ifndef __COMMAND_HPP__
# define __COMMAND_HPP__

#include <iostream>
#include "Server.hpp"

class User;

namespace irc
{

	class Command
	{
		public:
			Command();
			~Command();

			virtual void execute(User* user, std::vector<std::string> args) = 0;

		protected:
			Server* _server;

	};
}


#endif // __COMMAND_HPP__