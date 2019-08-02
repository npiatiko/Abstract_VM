#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/13 14:42:08 by npiatiko          #+#    #+#              #
#    Updated: 2019/06/13 14:42:08 by npiatiko         ###   ########.fr        #
#                                                                              #
#******************************************************************************#


# Name of the program
NAME = avm

# Compiling flags
FLAGS = -Wall -Wextra -Werror -std=c++14

# Folders
SRC_DIR = ./srcs/
OBJ_DIR = ./obj/
INC_DIR = ./includes/

# Source files and object files
SRC_FILES = Exceptions.cpp\
            Factory.cpp\
            InstFactory.cpp\
            Instruction.cpp\
            Machine.cpp\
            main.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# Libft and Minilibx linkers

# all rule
all: obj $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	g++ $(FLAGS) -I $(INC_DIR) -o $@ -c $<

# Compiling
$(NAME): $(OBJ)
	g++ $(OBJ) $(LNK) -lm -o $(NAME)

# clean rule
clean:
	rm -Rf $(OBJ_DIR)

# fclean rule
fclean: clean
	rm -f $(NAME)

# re rule
re: fclean all

# phony
.PHONY: all clean fclean re
