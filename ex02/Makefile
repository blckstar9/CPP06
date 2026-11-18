NAME		= identify
TESTER_NAME	= ex02_tester
CPP			= c++
CPPFLAGS	= -Wall -Wextra -Werror -std=c++98
RM			= rm -f

SRC			= main.cpp Base.cpp Identify.cpp
OBJ			= $(SRC:.cpp=.o)
TESTER_SRC	= tester.cpp Base.cpp Identify.cpp
TESTER_OBJ	= $(TESTER_SRC:.cpp=.o)
DEP			= $(SRC:.cpp=.d) $(TESTER_SRC:.cpp=.d)

all: $(NAME)
tester: $(TESTER_NAME)
test: $(TESTER_NAME)
	./$(TESTER_NAME)

$(NAME): $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

$(TESTER_NAME): $(TESTER_OBJ)
	$(CPP) $(CPPFLAGS) $(TESTER_OBJ) -o $(TESTER_NAME)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -MMD -MP -c $< -o $@

clean:
	$(RM) $(OBJ) $(TESTER_OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME) $(TESTER_NAME)

re: fclean
	$(MAKE) all

-include $(DEP)

.PHONY: all tester test clean fclean re
