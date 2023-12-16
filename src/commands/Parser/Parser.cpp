#include "Parser.hpp"

irc::Parser::Parser(Server* server)
{
	_commands["PASS"]   = new Pass(server, false);
	_commands["NICK"]   = new Nick(server, false);
	_commands["USER"]   = new UserCom(server, false);

	_commands["PING"]    = new Ping(server);
	_commands["PONG"]    = new Pong(server);
	_commands["JOIN"]    = new Join(server);
	_commands["KICK"]    = new Kick(server);
	_commands["MODE"]    = new Mode(server);
	_commands["TOPIC"]   = new Topic(server);
	_commands["INVITE"]  = new Invite(server);
	_commands["NOTICE"]  = new Notice(server);
	_commands["PRIVMSG"] = new PrivMsg(server);
}

irc::Parser::~Parser()
{
	std::map<const std::string, Command*>::iterator	begin = _commands.begin();
	std::map<const std::string, Command*>::iterator	end   = _commands.end();

	while (begin != end)
	{
		if (begin->second)
		{
			delete begin->second;
		}
	}
}

/**
 * @brief	trims from the beginning and end of a str with WHITESPACE
 * 
 * @param	string which must be trimmed from start and
 *          end by WHITESPACE 
 * 
 * @return	a string, with the given WHITESPACE removed from
 *          the start and end of the original string 
 */

std::string	irc::Parser::trim(const std::string& str, const char* WHITESPACE = " \r\f\t\n\v")
{
	std::size_t first = str.find_first_not_of(WHITESPACE);
	if (first == std::string::npos)
	{
		return std::string();
	}

	std::size_t last = str.find_last_not_of(WHITESPACE);

	return str.substr(first, last - first + 1);
}

/**
 * @brief	executes th command after parsing	
 * 
 * @param	pointer of User, string message
 * 
 * @return	nothing
*/

void	irc::Parser::invoke(User* user, const std::string& message)
{
	if (user->isRegistered() == false)
	{
		user->reply(ERR_NOTREGISTERED(user->getNickName()));
		return ;
	}

	std::stringstream	ss(message);
	std::string 		syntax;

	while (std::getline(ss, syntax))
	{
		std::string trimedSyntax = Parser::trim(syntax);
		std::string	command      = trimedSyntax.substr(0, trimedSyntax.find(" "));

		try
		{
			std::vector<std::string>	args;
			std::stringstream			line(trimedSyntax.substr(command.size(), trimedSyntax.size()));

			Command*	cmd = _commands.at(command);
			std::string	buffer;

			while (line >> buffer)
			{
				args.push_back(buffer);
			}

			if (!user->isRegistered() && cmd->authRequired())
			{
				user->reply(ERR_NOTREGISTERED(user->getNickName()));
				return ;
			}

			cmd->execute(user, args);
		}
		catch(const std::exception& e)
		{
			(void)e;
			user->reply(ERR_UNKNOWNCOMMAND(user->getNickName(), command));
		}
	}
}