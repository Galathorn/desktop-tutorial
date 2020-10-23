# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguttin <tguttin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/30 14:18:45 by tguttin           #+#    #+#              #
#    Updated: 2018/03/29 18:15:33 by tguttin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RubiksCube

PATH_SRC = ./srcs/

CFLAGS = #-Wall -Wextra -Werror

COMP = g++

HEAD = includes/

SRC = main.cpp \
		cube.cpp\
		cubePrinter.cpp\
		cubeScrambler.cpp\
		configManager.cpp\
		nodeInfo.cpp\
		Solver.cpp


OBJ = $(addprefix $(PATH_SRC), $(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ) $(HEAD)
	$(COMP) $(CFLAGS) $(OBJ) -o $(NAME)

.PHONY: clean fclean

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
