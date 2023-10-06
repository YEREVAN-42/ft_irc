#include "Message.hpp"

irc::Message::Message(const std::string& ircMsgFromStr) {  _parse(ircMsgFromStr); }
irc::Message::Message() {  }
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

irc::Message& irc::Message::operator<<(const std::string& param)
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

void irc::Message::_parse(const std::string& ircMsgFromStr)
{
	std::vector<std::string> splitedBySpace = Message::split(ircMsgFromStr, ' ');

	for (std::size_t i = 0; i < splitedBySpace.size(); ++i)
	{
		if (i == 0 && splitedBySpace[i][0] == ':')
		{
			this->_prefix = splitedBySpace[i].erase(0, 1);
			continue ;
		}

		if (this->_command.empty() == true)
		{
			this->_command = splitedBySpace[i];
			continue ;
		}

		if (splitedBySpace[i][0] == ':')
		{
			std::string line;
			splitedBySpace[i].erase(0, 1);
			while (i < splitedBySpace.size())
			{
				line += splitedBySpace[i];
				if (i != splitedBySpace.size() - 1)
				{
					line += ' ';
				}
			}
			this->_params.push_back(line);
		}
		else
		{
			this->_params.push_back(splitedBySpace[i]);
		}
	}
}

const std::string irc::Message::createReplyForm() const
{
	std::vector<std::string>::const_iterator c_it = _params.begin();
	std::string                              strReply;

	while (c_it != _params.end())
	{
		strReply += *c_it;

		if (*c_it != ":" && (c_it + 1) != _params.end())
		{
			strReply += " ";
		}
		++c_it;
	}
	strReply += "\r\n";
	return strReply;
}

// std::ostream& irc::operator<<(std::ostream& out, const irc::Message& msg)
// {
// 	for (std::size_t i = 0; i < msg.getParams().size(); ++i)
// 	{
// 		out << msg.getParams()[i] << std::endl;
// 	}
// 	return out;
// }
