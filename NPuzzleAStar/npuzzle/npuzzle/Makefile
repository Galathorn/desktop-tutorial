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

NAME = nPuzzle

PATH_SRC = ./src/

CFLAGS = -Wall -Wextra -Werror

COMP = g++

HEAD = includes/

SRC = main.cpp \
		Pos.class.cpp \
      	Node.class.cpp \
     	nPuzzle.class.cpp\
		Scrambler.class.cpp\
		Algorithm.class.cpp\
		Astar.class.cpp

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
