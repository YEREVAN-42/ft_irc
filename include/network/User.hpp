#ifndef  __USER_HPP__
# define __USER_HPP__

# include "irc.hpp"

# include "Channel.hpp"

namespace irc
{
	class Channel;

	class User
	{
		public:
			enum UserState
			{
				HANDSHAKE		= 1,
				LOGIN			= 2,
				REGISTERED		= 3,
				DISCONNECTED	= 4
			};

		public:
			User(int fd, int port, const std::string& host);
			~User();

			int	getFd()   const;
			int	getPort() const;

			const std::string&	getUserName() const;
			const std::string&	getNickName() const;
			const std::string&	getRealName() const;
			const std::string&	getHostName() const;
			const std::string	getPrefix()   const;

			bool getPrivilege() const;

			Channel*	getChannel() const;

			const UserState&	getState() const;

			bool	isRegistered() const;

			void	setFd(int fd);
			void	setPort(int port);
			void	setChannel(Channel* channel);
			void	setState(const UserState& state);
			void	setUserName(const std::string& userName);
			void	setNickName(const std::string& nickName);
			void	setRealName(const std::string& realName);
			void	setHostName(const std::string& hostName);
			void	setPrivilege(bool state);

			//	-------------------------------------------

			/* Send/Recieve Actions */
			void	write(const std::string& message) const;
			void	reply(const std::string& reply)   const;
			void	welcome();

			/* Client Actions */
			void	join(Channel* channel);
			void	leave();

		private:
			int					_fd;
			int					_port;

			std::string	_hostName;
			std::string	_userName;
			std::string	_nickName;
			std::string	_realName;

			bool		_privilege;

			UserState		_state;
			Channel*		_channel;

			User();
			User(const User& other);

	};
}

#endif // __USER_HPP__
