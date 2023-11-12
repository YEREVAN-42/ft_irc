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
			Command(Server *server);
			virtual ~Command();

			virtual void execute(User* user, std::vector<std::string> args) = 0;

		protected:
			Server* _server;
	};

	class Invite : public Command
	{
		public:
			Invite(Server *server);
			~Invite();

		void    execute(User* user, std::vector<std::string> args);
	};

	class Join : public Command
	{
		public:
			Join(Server *server);
			~Join();

		void    execute(User* user, std::vector<std::string> args);
	};

	class Kick : public Command
	{
		public:
			Kick(Server *server);
			~Kick();

		void    execute(User* user, std::vector<std::string> args);
	};

	class Topic : public Command
	{
		public:
			Topic(Server *server);
			~Topic();

		// void    execute(User* user, std::vector<std::string> args);
	};
}


#endif // __COMMAND_HPP__