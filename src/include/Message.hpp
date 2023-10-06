#ifndef  __MESSAGE_HPP__
# define __MESSAGE_HPP__

# include <string>
# include <vector>
# include <iostream>

namespace irc
{
	class Message
	{
		public:
			Message();
			Message(const std::string&);
			~Message();

		public:
			const std::string&              getPrefix()  const;
			const std::string&              getCommand() const;
			const std::vector<std::string>& getParams()  const;

			static std::vector<std::string> split(const std::string&, const char);

			std::size_t       paramSize()       const;
			const std::string createReplyForm() const;

		public:
			Message& operator<<(const std::string&);

		private:
			Message(const Message&);

			void _parse(const std::string&);

			std::string              _prefix;
			std::string              _command;
			std::vector<std::string> _params;
	};

	// std::ostream& operator<<(std::ostream&, const Message&);
}

#endif // __MESSAGE_HPP__
