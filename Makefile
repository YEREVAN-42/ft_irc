###############################################################################
############################ Makefile Template ################################
###############################################################################

# Compiler settings - Can be customized
CXX      = c++

#INCLUDES := $(shell find include -maxdepth 4 -name *.hpp)
#SRC := $(shell find $(SRCDIR) -maxdepth 4 -name *.cpp)

CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address
LDFLAGS  :=

# Makefile settings - Can be customized
NAME   = ircserv
SRCDIR = $(shell find src -type d)
INCDIR = $(shell find include -type d)
OBJDIR = bin/obj
DEPDIR = bin/dep

vpath %.cpp $(foreach dir, $(SRCDIR), $(dir):)


SRC := $(foreach dir, $(SRCDIR), $(foreach file, $(wildcard $(dir)/*.cpp), $(notdir $(file))))
OBJ := $(addprefix $(OBJDIR)/, $(SRC:%.cpp=%.o))
DEP := $(addprefix $(DEPDIR)/, $(OBJ:%.o=%.d))

IFLAGS =	$(foreach dir, $(INCDIR), -I $(dir))


# UNIX-based OS variables & settings
RM = rm -rf

###############################################################################
########################### Targets beginning here ############################
###############################################################################

.DEFAULT_GOAL = all

# Builds the app
$(NAME): $(OBJ)
	@echo "-----\nCreating Binary File $(_YELLOW)$@$(_WHITE) ... \c"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@mv ircserv bin
	@echo "$(_GREEN)DONE$(_WHITE)\n-----"

# Creates the dependency rules
$(DEPDIR)/%.d: $(SRCDIR)/%.cpp
	@mkdir -p $(DEPDIR)
	@$(CXX) $(CXXFLAGS) $(IFLAGS) $< -MM -MT $(@:$(DEPDIR)/%.d=$(OBJDIR)/%.o) >$@

# Building rule for .o files and its *.c/cpp in combination with all *.h/hpp`
$(OBJDIR)/%.o:%.cpp Makefile
	@echo "Compiling $(_YELLOW)$@$(_WHITE) ... \c"
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXXFLAGS) $(IFLAGS) -o $@ -c $<
	@echo "$(_GREEN)DONE$(_WHITE)"

.PHONY: all
all: $(NAME)

# Includes all *.h/hpp files
-include $(DEP)

##################### Cleaning rules for Unix-based OS ########################

# Cleans complete project
.PHONY: clean
clean:
	@echo "$(_WHITE)Deleting Objects Directory $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... \c"
	@$(foreach file, $(OBJ), $(RM) $(file))
	@echo "$(_GREEN)DONE$(_WHITE)\n-----"

.PHONY: fclean
fclean: clean
	@echo "Deleting Binary File $(_YELLOW)$(NAME)$(_WHITE) ... \c"
	@$(RM) bin/
	@echo "$(_GREEN)DONE$(_WHITE)\n-----"

.PHONY: re
re: fclean all
#	$(MAKE)


# Show macro details
show:
	@echo "$(_BLUE)SRC :\n$(_YELLOW)$(SRC)$(_WHITE)"
	@echo "$(_BLUE)OBJ :\n$(_YELLOW)$(OBJ)$(_WHITE)"
	@echo "$(_BLUE)DEP :\n$(_YELLOW)$(OBJ)$(_WHITE)"
	@echo "$(_BLUE)CXXFLAGS :\n$(_YELLOW)$(CFLAGS)$(_WHITE)"
	@echo "$(_BLUE)IFLAGS :\n$(_YELLOW)$(IFLAGS)$(_WHITE)"
	@echo "\n-----\n"
	@echo "$(_BLUE)Compiling : \n$(_YELLOW)$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(_WHITE)"



###############################################################################
########################### Building with valgrind ############################
###############################################################################

LOGFILE	 = valgrind-out.txt

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


# #############################################################################
#
# Makefile misc
#
# #############################################################################

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
SUCCESS=$(GREEN)SUCCESS$(NC)
COMPILING=$(_BLUE)COMPILING$(NC)

# #############################################################################
