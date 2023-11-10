#ifndef __JOIN_HPP__
# define __JOIN_HPP__

#include "Server.hpp"

namespace irc
{
	class Join : public Command
	{
		public:
			Join(/* args */);
			~Join();

		void    execute(User* user, std::vector<std::string> args);
	};
}

#endif //__JOIN_HPP__