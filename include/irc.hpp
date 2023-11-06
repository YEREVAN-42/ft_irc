#ifndef  __IRC_HPP__
# define __IRC_HPP__

# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h> // close
# include <sys/poll.h>
# include <netdb.h>
# include <poll.h>

# include <map>
# include <vector>
# include <string>

# include <ctime> // for Log function in line 122 
# include <cerrno>
# include <cstdio>
# include <cstdlib> // EXIT_FAILURE
# include <fcntl.h>
# include <cstring>
# include <unistd.h>

# include <iostream>
# include <stdexcept>
# include <algorithm>

# include "Messages.hpp"
# include "Colors.hpp"

namespace irc
{
	// Literal Definition Value
	const char CR = '\r';
	const char LF = '\n';
    
	// irc server Response

    /* Error Responses */

    inline const std::string  ERR_NOTREGISTERED(const std::string& source)
    { return std::string("451 " + source + " :You have not registered"); }

    inline const std::string  ERR_ALREADYREGISTERED(const std::string& source)
    { return std::string("462 " + source + " :You may not register"); }

    inline const std::string  ERR_PASSWDMISMATCH(const std::string& source)
    { return std::string("464 " + source + " :Password is incorrect"); }
 
    inline const std::string  ERR_NONICKNAMEGIVEN(const std::string& source)
    { return std::string("431 " + source + " :Nickname not given"); }

    inline const std::string  ERR_NICKNAMEINUSE(const std::string& source)
    { return std::string("433 " + source + " " + source  + " :Nickname is already in use"); }

    inline const std::string  ERR_UNKNOWNCOMMAND(const std::string& source, const std::string& command)
    { return std::string("421 " + source + " " + command + " :Unknown command"); }

    inline const std::string  ERR_NEEDMOREPARAMS(const std::string& source, const std::string& command)
    { return std::string("461 " + source + " " + command + " :Not enough parameters"); }

    inline const std::string  ERR_TOOMANYCHANNELS(const std::string& source, const std::string& channel)
    { return std::string("405 " + source + " " + channel + " :You have joined too many channels"); }

    inline const std::string  ERR_NOTONCHANNEL(const std::string& source, const std::string& channel)
    { return std::string("442 " + source + " " + channel + " :You're not on that channel"); }

    inline const std::string  ERR_NOSUCHCHANNEL(const std::string& source, const std::string& channel)
    { return std::string("403 " + source + " " + channel + " :No such channel"); }

    inline const std::string  ERR_BADCHANNELKEY(const std::string& source, const std::string& channel)
    { return std::string("475 " + source + " " + channel + " :Cannot join channel (+k)"); }

    inline const std::string  ERR_CHANNELISFULL(const std::string& source, const std::string& channel)
    { return std::string("471 " + source + " " + channel + " :Cannot join channel (+l)"); }

    inline const std::string  ERR_CANNOTSENDTOCHAN(const std::string& source, const std::string& channel)
    { return std::string("404 " + source + " " + channel + " :Cannot send to channel"); }

    inline const std::string  ERR_CHANOPRIVSNEEDED(const std::string& source, const std::string& channel)
    { return std::string("482 " + source + " " + channel + " :You're not channel operator"); }


    inline const std::string  ERR_NOSUCHNICK(const std::string& source, const std::string& nickname)
    { return std::string("401 " + source + " " + nickname + " :No such nick/channel"); }

    inline const std::string  ERR_USERNOTINCHANNEL(const std::string& source, const std::string& nickname, const std::string& channel)
    { return std::string("441 " + source + " " + nickname + " " + channel + " :They aren't on that channel"); }

    /* Numeric Responses */

    inline const std::string  RPL_WELCOME(const std::string& source)
    { return std::string("001 " + source + " :Welcome " + source + " to the ft_irc network"); }

    inline const std::string  RPL_NAMREPLY(const std::string& source, const std::string& channel, const std::string& users)
    { return std::string("353 " + source + " = " + channel + " :" + users); }

    inline const std::string  RPL_ENDOFNAMES(const std::string& source, const std::string& channel)
    { return std::string("366 " + source + " " + channel + " :End of /NAMES list."); }

    /* Command Responses */

    inline const std::string  RPL_JOIN(const std::string& source, const std::string& channel)
    { return std::string(":" + source + " JOIN :" + channel); }

    inline const std::string  RPL_PART(const std::string& source, const std::string& channel)
    { return std::string(":" + source + " PART :" + channel); }

    inline const std::string  RPL_PING(const std::string& source, const std::string& token)
    { return std::string(":" + source + " PONG :" + token); }

    inline const std::string  RPL_PRIVMSG(const std::string& source, const std::string& target, const std::string& message)
    { return std::string(":" + source + " PRIVMSG " + target + " :" + message); }

    inline const std::string  RPL_NOTICE(const std::string& source, const std::string& target, const std::string& message)
    { return std::string(":" + source + " NOTICE " + target + " :" + message); }

    inline const std::string  RPL_QUIT(const std::string& source, const std::string& message)
    { return std::string(":" + source + " QUIT :Quit: " + message); }

    inline const std::string  RPL_KICK(const std::string& source, const std::string& channel, const std::string& target, const std::string& reason)
    { return std::string(":" + source + " KICK " + channel + " " + target + " :" + reason); }

    inline const std::string  RPL_MODE(const std::string& source, const std::string& channel, const std::string& modes, const std::string& args)
    { return std::string(":" + source + " MODE " + channel + " " + modes + " " + args); }


    /* Log Response */

    inline void  Log(const std::string& message) 
    {
        char        buffer[80];
        time_t      rawtime;
        struct tm*  timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
        std::string str(buffer);

        std::cout << BOLDBLUE << str << RESET;
        std::cout << BOLDGREEN << message << RESET << std::endl;
    }

}

#endif // __IRC_HPP__
