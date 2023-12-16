#include "Server.hpp"

int MAX_USER_NUMBER = 10;

irc::Server::Server(int port, const std::string& password)
	: _port(port), _password(password), _host("127.0.0.1")
{
	_sock = createSocket();
	_parser = new Parser(this);
}

irc::Server::~Server()
{
	if (_parser != NULL)
	{
		delete _parser;
	}

	for (std::size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i] != NULL)
		{
			delete _channels[i];
		}
	}
}

const std::string&	irc::Server::getPassword() const { return _password; }

/**
 * @brief  By filtering the map of the users,
 *         find the user whose nickname was passed as an argument.
 *
 * @param  the user nickname 
 * 
 * @return pointer of the user whose nickname was passed as an argument
 */
irc::User* irc::Server::getUser(const std::string& nickName) const
{
	user_const_iterator	begin = _users.begin();
	user_const_iterator	end   = _users.end();

	while (begin != end)
	{
		if (nickName.compare(begin->second->getNickName()) == 0)
		{
			return begin->second;
		}

		++begin;
	}

	return NULL;
}

/**
 * @brief  By filtering the vector of the channels,
 *         find the Channel whose name was passed as an argument.
 *
 * @param  the channel name
 * 
 * @return pointer of the Channel whose name was passed as an argument.
 */
irc::Channel*	irc::Server::getChannel(const std::string& name) const
{
	channel_const_iterator	begin = _channels.begin();
	channel_const_iterator	end   = _channels.end();

	while (begin != end)
	{
		if (name.compare((*begin)->getName()) == 0)
		{
			return (*begin);
		}

		++begin;
	}

	return NULL; 
}

/**
 * @brief  create a new Channel and Adds Channel to the vector 
 *
 * @param  the channel name, the channel key, the admin of this channel
 * 
 * @return pointer of the Channel that just created
 */
irc::Channel*	irc::Server::createChannel(const std::string& name, const std::string& key, User* admin)
{
	Channel*	channel = new Channel(name, key, admin);
	_channels.push_back(channel);

	return channel;
}

/**
 * @brief Reads a message from the specified file descriptor.
 * 
 * @param fd file descriptor from which to read the message.
 * 
 * @return A std::string containing the complete message read from the file descriptor.
 */
const std::string	irc::Server::readMessage(int fd) const
{
	std::string	message;
	char		buffer[100];

	bzero(buffer, 100);

	while (strstr(buffer, "\n") != NULL)
	{
		bzero(buffer, 100);

		if (recv(fd, buffer, 100, 0) == -1 && \
			errno != EWOULDBLOCK)
		{
			throw std::runtime_error("Error while reading buffer from a user!");
		}

		message.append(buffer);
	}

	return message;
}

/**
 * @brief Handles incoming messages from a connected user.
 * 
 * @param fd file descriptor associated with the connected user.
 * 
 * @return nothing
 */
void	irc::Server::onUserMessage(int fd)
{
	try
	{
		User* user = _users.at(fd);

		_parser->invoke(user, this->readMessage(fd));
	}
	catch(const std::exception& e)
	{
		std::cout << "Error while handling the client message! " << e.what() << std::endl;
	}
	
}

/**
 * @brief Handles the disconnection of a user.
 * 
 * @param fd file descriptor associated with the user to be disconnected.
 * 
 * @return nothing
 */
void	irc::Server::onUserDisconnect(int fd)
{
	try
	{
		User*	user = _users.at(fd);

		user->leave();

		char	message[1024];
		sprintf(message, "%s:%d has disconnected!", user->getHostName().c_str(), user->getPort());
		Log(message);

		_users.erase(fd);

		pfd_iterator	begin = _pfds.begin();
		pfd_iterator	end   = _pfds.end();

		while (begin != end)
		{
			if (begin->fd == fd)
			{
				_pfds.erase(begin);
				close(fd);
				break ;
			}
			++begin;
		}

		delete user;
	}
	catch(const std::exception& e)
	{
		std::cout << "Error while disconnecting! " << e.what() << std::endl;
	}
}

/**
 * @brief Handles the connection of a new user.
 * 
 * @param nothing
 * 
 * @return nothing
 */
void	irc::Server::onUserConnect()
{
	struct sockaddr_in	addr = {};
	socklen_t			size = sizeof(addr);
	int					fd;

	fd = accept(_sock, reinterpret_cast<sockaddr*>(&addr), &size);
	if (fd == -1)
	{
		throw std::runtime_error("Error while accepting a new user!");
	}

	pollfd	pfd = {fd, POLLIN, 0};
	_pfds.push_back(pfd);

	char	hostName[NI_MAXHOST];
	int		res = getnameinfo(reinterpret_cast<const sockaddr*>(&addr), size,\
					hostName, NI_MAXHOST, NULL, 0, NI_NUMERICSERV);
	if (res != 0)
	{
		throw std::runtime_error("Error while getting a hostname on a new user!");
	}

	User*	user = new User(fd, ntohs(addr.sin_port), hostName);
	_users.insert(std::make_pair(fd, user));

	char	message[1024];
	sprintf(message, "%s:%d has connected.", user->getHostName().c_str(), user->getPort());
	Log(message);
}

/**
 * @brief Creates and configures a socket for the IRC server.
 * 
 * @param nothing
 * 
 * @return file descriptor of the created and configured socket.
 */
int	irc::Server::createSocket()
{
	int	sockFd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockFd == -1)
	{
		throw std::runtime_error("Error while opening a socket file!");
	}

	int	optval = 1;
	if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
	{
		throw std::runtime_error("Error while setting socket options!");
	}

	if (fcntl(sockFd, F_SETFL, O_NONBLOCK) == -1)
	{
		throw std::runtime_error("Error while setting socket to NON-BLOCKING!");
	}

	struct sockaddr_in servAddr = {};

	bzero(reinterpret_cast<void*>(&servAddr), sizeof(servAddr));

	servAddr.sin_addr.s_addr = INADDR_ANY;
	servAddr.sin_family      = AF_INET;
	servAddr.sin_port        = htons(_port);

	if (bind(sockFd, reinterpret_cast<const sockaddr*>(&servAddr), sizeof(servAddr)) == -1)
	{
		throw std::runtime_error("Error while binding a socket!");
	}

	if (listen(sockFd, MAX_USER_NUMBER) == -1)
	{
		throw std::runtime_error("Error while listening on a socket!");
	}

	return sockFd;
}

/**
 * @brief Starts the IRC server and enters the main event loop.
 * 
 * @param nothing
 * 
 * @return nothing
 */
void	irc::Server::start()
{
	pollfd srv = {_sock, POLLIN, 0};
	_pfds.push_back(srv);

	Log("Server is listening...");

	while (true)
	{
		if (poll(_pfds.begin().base(), _pfds.size(), -1) == -1)
		{
			throw std::runtime_error("Error while polling from fd!");
		}

		for (pfd_const_iterator c_it = _pfds.begin(); c_it != _pfds.end(); ++c_it)
		{
			if (c_it->revents == 0)
			{
				std::cout << 1 << std::endl;
				continue ;
			}

			if ((c_it->revents & POLLHUP) == POLLHUP)
			{
				std::cout << 1 << std::endl;
				this->onUserDisconnect(c_it->fd);
				break ;
			}

			if (((c_it->revents & POLLIN) == POLLIN) &&\
				_sock == c_it->fd)
			{
				std::cout << 1 << std::endl;
				this->onUserConnect();
				break ;
			}
			std::cout << 1 << std::endl;
			this->onUserMessage(c_it->fd);

		}
	}
	
}

