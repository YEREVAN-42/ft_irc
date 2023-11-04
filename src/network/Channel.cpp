#include "Channel.hpp"

irc::Channel::Channel(const std::string &n, const std::string &k, User* a) : _name(n), _key(k), _admin(a) {}

irc::Channel::~Channel(){}

const std::string&	irc::Channel::getName() const { return _name; }
const std::string&	irc::Channel::getKey() const { return _key; }
irc::User*          irc::Channel::getAdmin() const { return _admin; }
size_t              irc::Channel::getLimit() const { return _limitMember; }

/**
 * @brief By filtering the vectors of the users, find the nickname and fill them in other vector.
 * 
 * @param nothing
 * 
 * @return a vector containing the nicknames
 */
std::vector<std::string>    irc::Channel::getNickNames()
{
    std::vector<std::string>    nickVector;
    userIter                    it_b = _userVector.begin();
    userIter                    it_e = _userVector.end();

    for (User* user = *it_b; it_b != it_e; ++it_b)
    {
        std::string nickname = (user == _admin ? "@" : "") + user->getNickName();
        nickVector.push_back(nickname);
    }
    return nickVector;
}

/**
 * @brief Adds user to the vector
 * 
 * @param pointer of the user
 * 
 * @return nothing
 */
void    irc::Channel::addUser(User* puser)
{
    _userVector.push_back(puser);
}

/**
 * @brief Deletes the given user from the vector
 * 
 * @param pointer of the user
 * 
 * @return nothing
 */
void    irc::Channel::removeUser(User* puser)
{

}

/**
 * @brief Filtering the user vectors finds the user by name and forwards the missing user a message on the specified socket.
 * 
 * @param message that will be printed, excluded username of user.
 * 
 * @return nothing
 */
void    irc::Channel::broadcast(const std::string& mes, const std::string& userName)
{
    userIter it_b = _userVector.begin();
    userIter it_e = _userVector.end();

    while (it_b != it_e)
    {
        if ((*it_b)->getUserName() == userName)
        {
            it_b++;
            continue;
        }
        (*it_b)->write(mes);
        it_b++;
    }
}