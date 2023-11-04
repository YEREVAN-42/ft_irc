#include "Channel.hpp"

irc::Channel::Channel(const std::string &n, const std::string &k, User* a) : _name(n), _key(k), _admin(a) {}

irc::Channel::~Channel(){}

const std::string&	irc::Channel::getName() const { return _name; }
const std::string&	irc::Channel::getKey() const { return _key; }
irc::User*          irc::Channel::getAdmin() const { return _admin; }
size_t              irc::Channel::getLimit() const { return _limitMember; }
bool                irc::Channel::getExtMsg() const { return _flag; }
size_t              irc::Channel::getSize() const { return _limitMember; }

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

void    irc::Channel::setKey(const std::string& key) { _key = key; }
void    irc::Channel::setLimit(size_t limit) { _limitMember = limit; }
void    irc::Channel::setExtMsg(bool flag) { _flag = flag; }

/**
 * @brief Eject a user from the channel
 * 
 * @param user-the user to remove, target-the user from whose channel user should be removed, the reason for removal
 * 
 * @return nothing
 */
void    irc::Channel::kick(User* user, User* target, const std::string& reason)
{
    this->broadcast(RPL_KICK(user->getPrefix(), _name, target->getNickName(), reason));
    this->removeUser(target);

    std::string message = user->getNickName() + " kicked " + target->getNickName() + " from channel " + _name;
    Log(message);
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
    userIter it_b = _userVector.begin();
    userIter it_e = _userVector.end();

    while (it_b != it_e)
    {
        if (*it_b == puser)
            _userVector.erase(it_b);
        
        it_b++;
    }

    puser->setChannel(NULL);

    if (puser == _admin)
    {
        _admin = *(_userVector.begin());

        std::string message = puser->getNickName() + " is already an admin of this channel " + _name;
        Log(message);
    }
}

/**
 * @brief All users are sent a message from the specified socket.
 * 
 * @param message that will be printed
 * 
 * @return nothing
 */
void    irc::Channel::broadcast(const std::string& mes)
{
    userIter it_b = _userVector.begin();
    userIter it_e = _userVector.end();

    while (it_b != it_e)
    {
        (*it_b)->write(mes);
        it_b++;
    }
}

/**
 * @brief By filtering the user vectors to all users except the excluded user are sent message to the specified socket.
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