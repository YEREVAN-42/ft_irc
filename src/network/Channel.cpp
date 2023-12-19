#include "Channel.hpp"

irc::Channel::Channel(const std::string &n, const std::string &k, irc::User* a)
: _name(n), _key(k), _admin(a)
{	}

irc::Channel::~Channel(){}

const std::string&  irc::Channel::getKey()    const { return _key; }
const std::string&	irc::Channel::getName()   const { return _name; }
bool                irc::Channel::getExtMsg() const { return _flag; }
irc::User*          irc::Channel::getAdmin()  const { return _admin; }
int                 irc::Channel::getMode()   const { return _modes; }
size_t              irc::Channel::getLimit()  const { return _limitMember; }
size_t              irc::Channel::getSize()   const { return _userVector.size(); }

/**
 * @brief By filtering the vectors of the users, find the nickname and fill them in other vector.
 * 
 * @param nothing
 * 
 * @return a vector containing the nicknames
 */
std::vector<std::string>    irc::Channel::getNickNames() const
{
    std::vector<std::string> nickVector;

    for (userConstIter it = _userVector.begin(); it != _userVector.end(); ++it)
    {
        const irc::User* user = *it;
        std::string nickname = (user == _admin ? "@" : "") + user->getNickName();
        nickVector.push_back(nickname);
    }

    return nickVector;
}

void    irc::Channel::setExtMsg(bool flag) { _flag = flag; }

void    irc::Channel::setLimit(size_t limit)
{
    if (_modes & USER_LIMIT)
        _limitMember = limit;
}

void irc::Channel::removeLimit()
{
    if (_modes & USER_LIMIT)
        _limitMember = MAX_LIMIT;
}

void    irc::Channel::setKey(const std::string& key)
{
    std::string message = NULL;
    if (_modes & PRIVATE_KEY)
    {
        _key = key;
       message =  _name + " channel password changed.";
    }
    else
        message = "You cannot change " + _name + "  channel password in the current mode.";
    Log(message);
}

void irc::Channel::removeKey()
{
  std::string message = NULL;
   if (_modes & PRIVATE_KEY)
    {
        _key.clear();
        message =  _name + " channel password removed.";
    }
    else
        message = "You cannot remove " + _name + "  channel password in the current mode.";
    Log(message);
}

void irc::Channel::setTopic(const std::string& topic)
{
    std::string message = "";
    if (_modes & REST_TOPIC)
    {
        _topic = topic;
        message =  _name + " channel topic is set.";
    }
    else
        message = "You cannot set " + _name + "  channel topic in the current mode.";
    Log(message);
}

void irc::Channel::reSetTopic(const std::string& topic)
{
    std::string message = "";
    if (_modes & REST_TOPIC)
    {
        this->removeTopic();
        _topic = topic;
        message =  _name + " channel topic chenged.";
    }
    else
        message = "You cannot change " + _name + "  channel topic in the current mode.";
    Log(message);
}

void irc::Channel::removeTopic()
{
    std::string message = "";
    if (_modes & REST_TOPIC)
    {
        _topic = "";
        message =  _name + " channel topic removed.";
    }
    else
        message = "You cannot remove " + _name + "  channel topic in the current mode.";
    Log(message);
}

/**
 * @brief Eject(remove) a user from the channel
 *
 * @param user the user to remove, target the user from whose channel user should be removed, the reason for removal
 *
 * @return nothing
 */
void    irc::Channel::kick(irc::User* user, irc::User* target, const std::string& reason)
{
    this->broadcast(RPL_KICK(user->getPrefix(), _name, target->getNickName(), reason));
    target->leave();

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
void    irc::Channel::addUser(irc::User* puser)
{
    if (_modes & INV_ONLY)
        return ;
    if (_userVector.empty())
        giveOperator(puser);
    _userVector.push_back(puser);
}

/**
 * @brief deprive the operator of the position
 *
 * @param pointer of the user
 *
 * @return nothing
 */
void irc::Channel::takeOperator(User* puser)
{
    if (_modes & OPER_PRIVILEGE)
        puser->setPrivilege(false);
}

/**
 * @brief gives the user an operator role
 *
 * @param pointer of the user
 *
 * @return nothing
 */
void irc::Channel::giveOperator(User* puser)
{
    if (_modes & OPER_PRIVILEGE)
        puser->setPrivilege(true);
}

/**
 * @brief Deletes the given user from the vector
 *
 * @param pointer of the user
 *
 * @return nothing
 */
void    irc::Channel::removeUser(irc::User* puser)
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
    userConstIter it_b = _userVector.begin();
    userConstIter it_e = _userVector.end();

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
    userConstIter it_b = _userVector.begin();
    userConstIter it_e = _userVector.end();

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

/**
 * @brief mode is added using string
 * 
 * @param string
 * 
 * @return nothing
 */
void    irc::Channel::setModeString(const std::string& m)
{
    switch(m[0])
    {
        case 'i':
         _modes |= INV_ONLY;
         break ;
        case 't': 
         _modes |= REST_TOPIC;
         break ;
        case 'k': 
         _modes |= PRIVATE_KEY;
         break ;
        case 'o': 
         _modes |= OPER_PRIVILEGE;
         break ;
        case 'l': 
         _modes |= USER_LIMIT;
         break ;
    }
}

/**
 * @brief mode is added outside the class 
 * 
 * @param mode type
 * 
 * @return nothing
 */
void    irc::Channel::setMode(ChannelMode_t m)
{
    _modes |= m;
}

/**
 * @brief Invites the user to a channel
 * 
 * @param target the user who will invite the channel
 * 
 * @return nothing
 */
void    irc::Channel::invite(irc::User* user)
{
    user->join(this);

    std::string message = user->getNickName() + " was invated to the channel ";
    Log(message);
}

void    irc::Channel::mode(ChannelMode_t m)
{
    if (m & INV_ONLY)
        _modes |= INV_ONLY;
    if (m & REST_TOPIC)
        _modes |= REST_TOPIC;
    if (m & PRIVATE_KEY)
        _modes |= PRIVATE_KEY;
    if (m & OPER_PRIVILEGE)
        _modes |= OPER_PRIVILEGE;
    if (m & USER_LIMIT)
        _modes |= USER_LIMIT;
}
