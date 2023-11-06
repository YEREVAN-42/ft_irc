#include "Server.hpp"

irc::Server::Server(int port, const std::string& password)
	: _port(port), _password(password), _host("127.0.0.1")
{
	_sock = createSocket()
	_parser = new Parser(this);
}

irc::Server::~Server()
{
	if (_parser != NULL)
	{
		delete _parser;
	}

	for (std::size_t i = 0; i < _channel.size(); ++i)
	{
		if (_channel[i] != NULL)
		{
			delete _channel[i];
		}
	}
}