#ifndef  __IRC_HPP__
# define __IRC_HPP__

# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h> // close

# include <map>
# include <vector>
# include <string>

# include <cerrno>
# include <cstdio>
# include <cstdlib> // EXIT_FAILURE
# include <fcntl.h>
# include <cstring>
# include <unistd.h>

# include <iostream>

# include "Utils/CommonValue.hpp"
# include "Utils/Messages.hpp"
# include "Color/Colors.hpp"

namespace irc
{
    // irc server Response

    /* Error Responses */

    inline const char*  ERR_NOTREGISTERED(const char* source)
    { return "451 " + source + " :You have not registered"; }

    inline const char*  ERR_ALREADYREGISTERED(const char* source)
    { return "462 " + source + " :You may not register"; }

    inline const char*  ERR_PASSWDMISMATCH(const char* source)
    { return "464 " + source + " :Password is incorrect"; }
 
    inline const char*  ERR_NONICKNAMEGIVEN(const char* source)
    { return "431 " + source + " :Nickname not given"; }

    inline const char*  ERR_NICKNAMEINUSE(const char* source)
    { return "433 " + source + " " + source  + " :Nickname is already in use"; }

    inline const char*  ERR_UNKNOWNCOMMAND(const char* source, const char* command)
    { return "421 " + source + " " + command + " :Unknown command"; }

    inline const char*  ERR_NEEDMOREPARAMS(const char* source, const char* command)
    { return "461 " + source + " " + command + " :Not enough parameters"; }

    inline const char*  ERR_TOOMANYCHANNELS(const char* source, const char* channel)
    { return "405 " + source + " " + channel + " :You have joined too many channels"; }

    inline const char*  ERR_NOTONCHANNEL(const char* source, const char* channel)
    { return "442 " + source + " " + channel + " :You're not on that channel"; }

    inline const char*  ERR_NOSUCHCHANNEL(const char* source, const char* channel)
    { return "403 " + source + " " + channel + " :No such channel"; }

    inline const char*  ERR_BADCHANNELKEY(const char* source, const char* channel)
    { return "475 " + source + " " + channel + " :Cannot join channel (+k)"; }

    inline const char*  ERR_CHANNELISFULL(const char* source, const char* channel)
    { return "471 " + source + " " + channel + " :Cannot join channel (+l)"; }

    inline const char*  ERR_CANNOTSENDTOCHAN(const char* source, const char* channel)
    { return "404 " + source + " " + channel + " :Cannot send to channel"; }

    inline const char*  ERR_CHANOPRIVSNEEDED(const char* source, const char* channel)
    { return "482 " + source + " " + channel + " :You're not channel operator"; }


    inline const char*  ERR_NOSUCHNICK(const char* source, const char* nickname)
    { return "401 " + source + " " + nickname + " :No such nick/channel"; }

    inline const char*  ERR_USERNOTINCHANNEL(const char* source, const char* nickname, const char* channel)
    { return "441 " + source + " " + nickname + " " + channel + " :They aren't on that channel"; }

    /* Numeric Responses */

    inline const char*  RPL_WELCOME(const char* source)
    { return "001 " + source + " :Welcome " + source + " to the ft_irc network"; }

    inline const char*  RPL_NAMREPLY(const char* source, const char* channel, const char* users)
    { return "353 " + source + " = " + channel + " :" + users; }

    inline const char*  RPL_ENDOFNAMES(const char* source, const char* channel)
    { return "366 " + source + " " + channel + " :End of /NAMES list."; }

    /* Command Responses */

    inline const char*  RPL_JOIN(const char* source, const char* channel)
    { return ":" + source + " JOIN :" + channel; }

    inline const char*  RPL_PART(const char* source, const char* channel)
    { return ":" + source + " PART :" + channel; }

    inline const char*  RPL_PING(const char* source, const char* token)
    { return ":" + source + " PONG :" + token; }

    inline const char*  RPL_PRIVMSG(const char* source, const char* target, const char* message)
    { return ":" + source + " PRIVMSG " + target + " :" + message; }

    inline const char*  RPL_NOTICE(const char* source, const char* target, const char* message)
    { return ":" + source + " NOTICE " + target + " :" + message; }

    inline const char*  RPL_QUIT(const char* source, const char* message)
    { return ":" + source + " QUIT :Quit: " + message; }

    inline const char*  RPL_KICK(const char* source, const char* channel, const char* target, const char* reason)
    { return ":" + source + " KICK " + channel + " " + target + " :" + reason; }

    inline const char*  RPL_MODE(const char* source, const char* channel, const char* modes, const char* args)
    { return ":" + source + " MODE " + channel + " " + modes + " " + args; }


    /* Log Response */

    static inline void  Log(const std::string& message) 
    {
        char        buffer[80];
        time_t      rawtime;
        struct tm*  timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
        std::string str(buffer);

        std::cout << BOLDBLUE << str << RESET;
        std::cout << message << std::endl;
    }

}

#endif // __IRC_HPP__
