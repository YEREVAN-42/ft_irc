#ifndef  __PARSER_HPP__
# define __PARSER_HPP__

# include <string>
# include <sstream>
# include <iostream>

# include <map>
// # include <vector>


# include "Command.hpp"

namespace irc
{
	class Command;
	class Server;

	class Parser
	{
		public:
			Parser(Server* server);
			~Parser();

			void	invoke(User*, const std::string&);

		private:
			static std::string	trim(const std::string&, const char*);

		private:
			std::map<const std::string, Command*>	_commands;
	};
}


#endif // __PARSER_HPP__