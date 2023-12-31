#ifndef  __SERVER_HPP__
# define __SERVER_HPP__

# include "irc.hpp"


# include "User.hpp"
# include "Parser.hpp"
# include "Channel.hpp"

namespace irc
{
	class Parser;

	class Server
	{
		private:
			Server();
			Server(const Server& other);

			typedef std::vector<pollfd>::iterator			pfd_iterator;
			typedef std::vector<pollfd>::const_iterator		pfd_const_iterator;

			typedef std::vector<Channel*>::iterator			channel_iterator;
			typedef std::vector<Channel*>::const_iterator	channel_const_iterator;

			typedef std::map<int, User*>::iterator			user_iterator;
			typedef std::map<int, User*>::const_iterator	user_const_iterator;

		public:
			Server(int port, const std::string& password);
			~Server();

		//	Initialize and listen
			void	start();

		//	getters
			const std::string&	getPassword()                  const;
			User*				getUser(const std::string&)    const;
			Channel*			getChannel(const std::string&) const;

		//	Handle User
			void	onUserConnect();
			void	onUserDisconnect(int);
			void	onUserMessage(int);

			const std::string	readMessage(int) const;

        //	Create Channel
			Channel*	createChannel(const std::string&, const std::string&, User*);

        //	Create Socket
			int	createSocket();

		private:
			int						_port;
			int						_sock;

			const std::string		_password;
			const std::string		_host;

			std::vector<pollfd>		_pfds;
			std::vector<Channel*>	_channels;
			std::map<int, User*>	_users;

			Parser*					_parser;
	};
}

#endif // __SERVER_HPP__