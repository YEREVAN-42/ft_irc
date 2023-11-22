#ifndef __COMMAND_HPP__
# define __COMMAND_HPP__

#include <iostream>

# include "irc.hpp"

#include "User.hpp"
#include "Server.hpp"
#include "Channel.hpp"



namespace irc
{

	class Server;

	class Command
	{
		public:
			Command(Server *server, bool auth = false);
			virtual ~Command();

			virtual void execute(User* user, std::vector<std::string> args) = 0;
		public:
			bool	authRequired() const;

		protected:
			Server* _server;
			bool	_auth;
	};

	class Invite : public Command
	{
		public:
			Invite(Server *server);
			virtual ~Invite();

			virtual void    execute(User* user, std::vector<std::string> args);
	};

	class Join : public Command
	{
		public:
			Join(Server *server);
			virtual ~Join();

			virtual void    execute(User* user, std::vector<std::string> args);
	};

	class Kick : public Command
	{
		public:
			Kick(Server *server);
			virtual ~Kick();

			virtual void    execute(User* user, std::vector<std::string> args);
	};

	class Topic : public Command
	{
		public:
			Topic(Server *server);
			virtual ~Topic();

			// virtual void    execute(User* user, std::vector<std::string> args);
	};

	class Ping : public Command
	{
		public:
			Ping(Server *server);
			virtual ~Ping();

			virtual void	execute(User* user, std::vector<std::string> args);
	};

	class Pong : public Command
	{
		public:
			Pong(Server *server);
			virtual ~Pong();

			virtual void	execute(User* user, std::vector<std::string> args);
	};
















	class Pass : public Command
	{
		public:
			Pass(Server *server, bool auth);
			virtual ~Pass();

			virtual void	execute(User* user, std::vector<std::string> args);
	};

	class User : public Command
	{
		public:
			User(Server *server, bool auth);
			virtual ~User();

			virtual void	execute(User* user, std::vector<std::string> args);
	};

	class Nick : public Command
	{
		public:
			Nick(Server *server, bool auth);
			virtual ~Nick();

			virtual void	execute(User* user, std::vector<std::string> args);
	};
}


#endif // __COMMAND_HPP__