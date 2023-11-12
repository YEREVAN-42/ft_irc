#include "Server.hpp"

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
 * @return const pointer of the user whose nickname was passed as an argument
 */
const irc::User* irc::Server::getUser(const std::string& nickName) const
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
 * @return const pointer of the Channel whose name was passed as an argument.
 */
const  irc::Channel*	irc::Server::getChannel(const std::string& name) const
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

void	irc::Server::onUserMessage(int fd)
{
	try
	{
		User* user = _users.at(fd);

		_parser->invoke(user, this->readMessage(fd));
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}