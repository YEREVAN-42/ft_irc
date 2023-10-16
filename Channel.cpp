#include "Channel.hpp"

 irc::Channel::Channel(){}
 irc::Channel::~Channel(){}

 const std::string& irc::Channel::getName() const
 {
	return _name
 }

 void	irc::Channel::addUser(const User& user)
 {
	if (_users.empty())
	{
		_admin = user;
	}
	_user.push_back(user);	
 }