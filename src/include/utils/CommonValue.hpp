#ifndef  __COMMONVALUE_HPP__
# define __COMMONVALUE_HPP__

namespace irc
{
		// Server settings value
	int MAX_NICKNAME_LEN    = 10;
	int MAX_CHANNELNAME_LEN = 31;
	int MAX_USER_NUM        = 30;
	int MAX_CHANNEL_NUM     = 30;

		// Function return value
	int ERR_RETURN = -1;

		// Literal Definition Value
	const char CR = '\r';
	const char LF = '\n';

	int UNDEFINED_FD = -1;

	const char* DEFAULT_PART_MESSAGE = " leaved channel.";
	const char* NEW_OPERATOR_MESSAGE = " is new channel operator.";
}

#endif // __COMMONVALUE_HPP__
