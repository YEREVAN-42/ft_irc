# Colors
_GREY=	\033[1;30m
_RED=	\033[1;31m
_GREEN=	\033[1;32m
_YELLOW=\033[1;33m
_BLUE=	\033[1;34m
_PURPLE=\033[1;35m
_CYAN=	\033[1;36m
_WHITE=	\033[1;37m
_NC=	\033[0m

# Colored messages
SUCCESS=$(_GREEN)SUCCESS$(NC)
COMPILING=$(_BLUE)COMPILING$(NC)

# #############################################################################


# Makefile for C++ project

# Compiler
CXX = c++

# Compiler flags
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
LDFLAGS  :=

# UNIX-based OS variables & settings
RM = rm -rf


# Binary directory
BIN = .bin

# Source directory
SRCDIR = src

# Object directory
OBJDIR = $(BIN)/obj

# Include directory
INCDIR  = include
INC     = $(shell find $(INCDIR) -type d)
IFLAGS  = $(foreach dir, $(INC), -I $(dir))
INCLUDE = $(foreach dir, $(INC), $(dir)/*.hpp)

# Source files
SRC := $(wildcard $(SRCDIR)/***/**/*.cpp)
SRC += $(wildcard $(SRCDIR)/**/*.cpp)
SRC += $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

# Executable name
NAME = ircserv

# Default target
all: $(NAME)

# Rule to build the executable
$(NAME): $(OBJ)
	@echo "-----\nCreating Binary File $(_YELLOW)$@$(_WHITE) ... \c"
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@mv $(NAME) $(BIN)/
	@echo "$(SUCCESS)\n-----"

# Rule to build object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDE) Makefile
	@echo "$(COMPILING) $(_YELLOW)$@$(_WHITE) ... \c"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@
	@echo "$(_GREEN)DONE$(_WHITE)"

# Run rule
run:
	@$(BIN)/$(NAME)

# Show macro details
show:
	@echo "$(_BLUE)SRC :\n$(_YELLOW)$(SRC)$(_WHITE)"
	@echo "$(_BLUE)OBJ :\n$(_YELLOW)$(OBJ)$(_WHITE)"
	@echo "$(_BLUE)OBJ :\n$(_YELLOW)$(INCLUDE)$(_WHITE)"
	@echo "$(_BLUE)CXXFLAGS :\n$(_YELLOW)$(CXXFLAGS)$(_WHITE)"
	@echo "$(_BLUE)IFLAGS :\n$(_YELLOW)$(IFLAGS)$(_WHITE)"
	@echo "\n-----\n"
	@echo "$(_BLUE)Compiling : \n$(_YELLOW)$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) $(_WHITE)"

# Clean rule
clean:
	@echo "$(_WHITE)Deleting Objects Directory $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... \c"
	@$(RM) $(OBJ)
	@echo "$(_GREEN)DONE$(_WHITE)\n-----"

fclean: clean
	@echo "Deleting Binary File $(_YELLOW)$(NAME)$(_WHITE) ... \c"
	@$(RM) $(BIN)
	@echo "$(_GREEN)DONE$(_WHITE)\n-----"


re: clean all

PHONY: all re clean fclean run show

###############################################################################
########################### Building with valgrind ############################
###############################################################################

LOGFILE = valgrind-out.txt

# for Building/compiling with valgrind
# - you have to commeent out "-g -fsanitize=address" from CXXFLAGS

.PHONY: valgrind
valgrind: all
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=$(LOGFILE) \
         ./$(NAME)

############################ Cleaning with valgrind ###########################

.PHONY: valgrind_clean
valgrind_clean: fclean
	$(RM) $(LOGFILE)
