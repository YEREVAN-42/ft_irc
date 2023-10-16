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

#endif // __IRC_HPP__
