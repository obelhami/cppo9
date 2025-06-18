SRC = main.cpp PmergeMe.cpp

OBJ = $(SRC:.cpp=.o)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

NAME = PmergeMe

all: $(NAME)

$(NAME) : $(OBJ)
		$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean: 
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all