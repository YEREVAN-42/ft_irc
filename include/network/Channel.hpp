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
            void    broadcast(const std::string&, const std::string&);

            const std::string&          getName() const;
            User*                       getAdmin() const;
            const std::string&          getKey() const;
            size_t                      getLimit() const;
            std::vector<std::string>    getNickNames();
            void                        setKey(const std::string&);
            void                        setLimit(size_t);

        private:
            std::string         _name;
            User*               _admin;
            std::vector<User *> _userVector;
            std::string         _key;
            size_t              _limitMember;
    }; 
}

#endif // __CHANNEL_HPP__