#ifndef  __PARSER_HPP__
# define __PARSER_HPP__

# include <string>
# include <sstream>
# include <iostream>

# include <map>
# include <vector>

# include "Command.hpp"

namespace irc
{
	class Server;
	class Command;

	class Parser
	{
		public:
			Parser(Server* server);
			~Parser();

			void	invoke(User*, const std::string&);
			// std::ostream& operator<<(std::ostream& out)
			// {
			// 	std::map<const std::string, Command*>::const_iterator begin = _commands.begin();
			// 	std::map<const std::string, Command*>::const_iterator end = _commands.end();

			// 	while (begin != end) {
			// 		out << begin->first << std::endl;
			// 		++begin;
			// 	}

			// 	return out;
			// }

		private:
			static std::string	trim(const std::string&, const char*);

		private:
			Server*                               _server;
			std::map<const std::string, Command*>	_commands;
	};
}


#endif // __PARSER_HPP__