#ifndef  CHANNEL_HPP
# define CHANNEL_HPP

#include <string>
#include <vector>
namespace irc
{
	class Channel
	{
		public:
			Channel(const std::string& name);
			~Channel();

			const std::string& getName() const;

			void	addUser(const User& _user);
			void	delUser(const User& _user);

		private:
			std::string			_name;
			User				_admin;
			std::vector<User *>	_users;
	};

}

#endif