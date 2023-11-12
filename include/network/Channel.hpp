#ifndef __CHANNEL_HPP__
# define __CHANNEL_HPP__

# include "irc.hpp"

# include "User.hpp"

namespace irc
{
	class User;

    class Channel
    {
        public:
            typedef std::vector<User *>::iterator userIter;

        public:
            Channel(const std::string &name, const std::string &key, User* admin);
			~Channel();
            void    addUser(User*);
            void    removeUser(User*);
            void    kick(User*, User*, const std::string&);
            void    broadcast(const std::string&);
            void    broadcast(const std::string&, const std::string&);

            void    setKey(const std::string&);
            void    setLimit(size_t);
            void    setExtMsg(bool);

            const std::string&          getName() const;
            User*                       getAdmin() const;
            const std::string&          getKey() const;
            size_t                      getLimit() const;
            bool                        getExtMsg() const;
            size_t                      getSize() const;
            std::vector<std::string>    getNickNames();

        private:
            std::string         _name;
            std::string         _key;
            User*               _admin;
            std::vector<User *> _userVector;
            size_t              _limitMember;
            bool                _flag;       // yes/no for external messages
    }; 
}

#endif // __CHANNEL_HPP__