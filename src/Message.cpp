#include "Message.hpp"

irc::Message::Message(const std::string& ircMsgFromStr) { _parse(ircMsgFromStr); }
irc::Message::~Message()
{
	this->_prefix.clear();
	this->_command.clear();
	this->_params.clear();
}

const std::string& irc::Message::getPrefix()  const { return this->_prefix;  }
const std::string& irc::Message::getCommand() const { return this->_command; }
const std::vector<std::string>& irc::Message::getParams() const
{ return this->_params; }

std::size_t irc::Message::paramSize() const { return this->_params.size(); }

Message& irc::Message::operator<<(const std::string& param)
{
	if (!param.empty())
	{
		_params.push_back(param);
	}
	return *this;
}

std::vector<std::string>
irc::Message::split(const std::string& str, const char delimiter)
{
	std::vector<std::string> splited;
	std::size_t cursorPos = 0;
	std::size_t delimiterPos;

	while ((delimiterPos = str.find(delimiter, cursorPos)) != std::string::npos)
	{
		splited.push_back(str.substr(cursorPos, delimiter - cursorPos));
		while(str[delimiterPos] == delimiter)
		{
			if (++delimiterPos == str.size())
			{
				return splited;
			}
		}
		cursorPos = delimiterPos;
	}
	splited.push_back(str.substr(cursorPos));
	return splited;
}

//_parse()

