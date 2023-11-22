#include "Command.hpp"

irc::Command::Command(Server *server, bool auth)
	: _server(server), _auth(auth)
{	}
irc::Command::~Command(){}

irc::Command::authRequired() const { return _auth; }