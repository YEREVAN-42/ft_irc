#ifndef __Channel_hpp__
# define __Channel_hpp__

# define    MAX_LIMIT 65535

# include "irc.hpp"
# include "User.hpp"

namespace irc
{
	class User;

    class Channel
    {
        public:
            enum ChannelMode_t
            {
                INV_ONLY        = 1, //DONE
                REST_TOPIC      = 2, //DONE
                PRIVATE_KEY     = 4, //DONE
                OPER_PRIVILEGE  = 8, //DONE
                USER_LIMIT      = 16 //DONE
            };

        typedef std::vector<User *>::iterator userIter;
        typedef std::vector<User *>::const_iterator userConstIter;

        public:
            Channel(const std::string &name, const std::string &key, User* admin);
			~Channel();
            void    addUser(User*);
            void    removeUser(User*);
            void    kick(User*, User*, const std::string&);
            void    broadcast(const std::string&);
            void    broadcast(const std::string&, const std::string&);
            void    mode(ChannelMode_t); // use mode(inv_only | rest_topic)

            void    setKey(const std::string&);
            void    setLimit(size_t);
            void    setExtMsg(bool);
            void    setModeChar(const char);
            void    setTopic(const std::string&);
            void    reSetTopic(const std::string&);

            const std::string&          getName() const;
            User*                       getAdmin() const;
            size_t                      getLimit() const;
            bool                        getExtMsg() const;
            size_t                      getSize() const;
            std::vector<std::string>    getNickNames() const;
            int                         getMode() const;
            const std::string&          getKey() const;

            void removeTopic();
            void removeKey();
            void removeLimit();
            void invite(User*);
            void giveOperator(User*);

            void removeInvMode();
            void removeTopicMode();
            void removeKeyMode();
            void takeOperator(User*);
            void removeLimitMode();

        private:
            void setMode(ChannelMode_t);
            bool checkMode(ChannelMode_t);

        private:
            std::string         _name;
            std::string         _key;
            std::string         _topic;
            User*               _admin;
            std::vector<User *> _userVector;
            size_t              _limitMember;
            bool                _flag;       // yes/no for external messages
            int                 _modes;
    }; 
}

#endif // __CHANNEL_HPP__