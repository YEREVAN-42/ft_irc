#ifndef  __PARSER_HPP__
# define __PARSER_HPP__

# include <string>
# include <sstream>
# include <iostream>

# include <map>
// # include <vector>

# include "User.hpp"
# include "Server.hpp"

# include "Command.hpp"
# include "Invite.hpp"
# include "Join.hpp"
# include "Kick.hpp"

namespace irc
{
	class Parser
	{
		public:
			Parser(Server* server);
			~Parser();

			void	invoke(User*, const std::string&);

		private:
			static std::string	trim(const std::string&, const char* WHITESPACE = " \r\f\t\n\v");

		private:
			Server*									_server;
			std::map<const std::string, Command*>	_commands;
	};
}


#endif // __PARSER_HPP__