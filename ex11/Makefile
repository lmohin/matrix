NAME	= tester
SRC	= main.cpp Matrix.cpp Vector.cpp linearAlgebra.cpp mathsUtils.cpp
OBJ	= $(SRC:%.cpp=%.o)
HEADERS	= Matrix.hpp Vector.hpp linearAlgebra.hpp
CC	= c++
FLAGS	= -Wall -Werror -Wextra


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@

%.o: %.cpp $(HEADERS)
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
