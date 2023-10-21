########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized
CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address
LDFLAGS  =

# Makefile settings - Can be customized
NAME   = ircserv
SRCDIR = src
OBJDIR = obj
DEPDIR = dep

SRC = $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/*/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=$(DEPDIR)/%.d)

# UNIX-based OS variables & settings
RM     = rm -rf

# Check if OBJDIR exists before including dependencies
# ifeq ($(wildcard $(OBJDIR)),)
# GENERATE_DEPS =
# else
# GENERATE_DEPS = -include $(DEP)
# endif

########################################################################
####################### Targets beginning here #########################
########################################################################

.PHONY: all
all: $(NAME)

# Builds the app
$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependency rules only if OBJDIR exists
# $(DEPDIR)/%.d: $(SRCDIR)/%.cpp
# 	@if [ -d $(OBJDIR) ]; then \
# 		mkdir -p $(@D); \
# 		$(CXX) $(CXXFLAGS) $< -MM -MT $(@:$(DEPDIR)/%.d=$(OBJDIR)/%.o) >$@; \
# 	fi

# Creates the dependency rules
$(DEPDIR)/%.d: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) $< -MM -MT $(@:$(DEPDIR)/%.d=$(OBJDIR)/%.o) >$@

# Includes all *.h/hpp files
-include $(DEP)

# Building rule for .o files and its *.c/cpp in combination with all *.h/hpp`
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################

# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(OBJDIR) $(DEPDIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean
	$(MAKE)

########################################################################
######################## Building with valgrind ########################
########################################################################

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

######################## Cleaning with valgrind ########################

.PHONY: valgrind_clean
valgrind_clean: fclean
	$(RM) $(LOGFILE)

