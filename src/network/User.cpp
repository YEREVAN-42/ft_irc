#include "User.hpp"

irc::User::~User() {	}
irc::User::User(int fd, int port, const std::string& host)
	: _fd(fd), _port(port), _hostName(host), _privilege(false), _channel(NULL)
{	}

int	irc::User::getFd()   const { return _fd; }
int	irc::User::getPort() const { return _port; }

const irc::User::UserState&	irc::User::getState() const { return _state; }

bool irc::User::getPrivilege() const { return _privilege; }

const std::string&	irc::User::getUserName() const { return _userName; }
const std::string&	irc::User::getNickName() const { return _nickName; }
const std::string&	irc::User::getRealName() const { return _realName; }
const std::string&	irc::User::getHostName() const { return _hostName; }

irc::Channel*	irc::User::getChannel()  const { return _channel;  }

bool				irc::User::isRegistered() const { return _state == REGISTERED; }

/**
 * @brief	By following the special irc-syntax,
 * 			give the _nickName, _userName, _hostName
 * 
 * @param	nothing
 * 
 * @return	a string which represents the user
 */
const std::string	irc::User::getPrefix()   const
{
	std::string userName = _userName.empty() ? "" : "!" + _userName;
	std::string hostName = _hostName.empty() ? "" : "@" + _hostName;

	return _nickName + userName + hostName;
}



void	irc::User::setFd(int fd)     { _fd = fd; }
void	irc::User::setPort(int port) { _port = port; }

void	irc::User::setState(const UserState& state) { _state = state; }
void	irc::User::setChannel(Channel* channel)     { _channel = channel; }

void	irc::User::setPrivilege(bool state) { _privilege = state; }

void	irc::User::setUserName(const std::string& userName) { _userName = userName; }
void	irc::User::setNickName(const std::string& nickName) { _nickName = nickName; }
void	irc::User::setRealName(const std::string& realName) { _realName = realName; }
void	irc::User::setHostName(const std::string& hostName) { _hostName = hostName; }


/**
 * @brief	By following the special irc-syntax,
 * 			reply and this->getPrefix are sent this->write
 * 
 * @param	reply that will be sent to a user
 * 
 * @return	nothing
 */
void	irc::User::reply(const std::string& reply) const
{
	this->write(":" + this->getPrefix() + " " + reply);
}

/**
 * @brief	By following the special irc-syntax,
 * 			send the message to the user
 * 
 * @param	message that will be sent to a user
 * 
 * @return	nothing
 */
void	irc::User::write(const std::string& message) const
{
	std::string buffer = message + CR + LF;

	if (send(_fd, buffer.c_str(), buffer.size(), 0) == -1)
	{
		throw std::runtime_error("Error while sending a message to a client(User)!");
	}
}

/**
 * @brief	changes user state,
 * 			sends a welcome message to the user,
 * 			and print when he connect the network
 * 
 * @param	nothing
 * 
 * @return	nothing
 * */
void	irc::User::welcome()
{
	if (_state != LOGIN)
	{
		ErrorMessage(NULL, "The user isn't logged!");
		return ;
	}

	if (_userName.empty())
	{
		ErrorMessage(NULL, "The user Doesn't have userName!");
		return ;
	}

	if (_realName.empty())
	{
		ErrorMessage(NULL, "The user Doesn't have realName!");
		return ;
	}

	if (_nickName.empty())
	{
		ErrorMessage(NULL, "The user Doesn't have nickName!");
		return ;
	}

	_state = REGISTERED;
	this->reply(RPL_WELCOME(_nickName));

	char message[512];
	sprintf(message, "%s:%d is now known as %s,", _hostName.c_str(), _port, _nickName.c_str());
	Log(message);
}

/**
 * @brief	the user must join th group
 * 			and send a message to all users that he has joineed the group,
 * 			and print when he joined the group 
 * 
 * @param	pointer of the channel , wherw the user should connect
 * 
 * @return nothing
 */
void	irc::User::join(Channel* channel)
{
	channel->setModeChar('o');
	channel->addUser(this);
	_channel = channel;

	std::string users = "";
	std::vector<std::string> nickNames = channel->getNickNames();
	std::vector<std::string>::iterator c_it_b = nickNames.begin();
	std::vector<std::string>::iterator c_it_e = nickNames.end();

	while (c_it_b != c_it_e)
	{
		users += *c_it_b + " ";
		++c_it_b;
	}

	// Send replies

	reply(RPL_NAMREPLY(_nickName, channel->getName(), users));
	reply(RPL_ENDOFNAMES(_nickName, channel->getName()));
	channel->broadcast(RPL_JOIN(getPrefix(), channel->getName()));

	const std::string message = _nickName + " has joined to the channel " + channel->getName();
	Log(message);
}

/**
 * @brief	the user must leave the group
 * 			and send a message to all users that he is leaving
 * 			and print when he left the group
 * 
 * @param	nothing
 * 
 * @return	nothing
 */
void	irc::User::leave()
{
	if (!_channel)
	{
		return ;
	}

	const std::string name = _channel->getName();

	_channel->broadcast(RPL_PART(getPrefix(), _channel->getName()));
	_channel->removeUser(this);

	const std::string message = _nickName + " has left the channel " + name;
	Log(message);
}
