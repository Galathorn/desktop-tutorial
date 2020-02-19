# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguttin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/28 16:12:01 by tguttin           #+#    #+#              #
#    Updated: 2020/01/29 16:39:01 by tguttin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : clean, fclean, re, all, $(NAME), lanch, debug, install, uninstall
.SUFFIXES :

NAME = npuzzle

SYSTEM = $(shell uname -s)

DEBUG_FLAG = -pedantic -Weverything -std=c++98

CC = clang++
FLAG = -Wall -Wextra -Werror
INCLUDE_LIBS := -lncurses

SRC = src/

FILES = \
	main.cpp

OBJ_DIR = bin/
OBJ_PATHS = $(addprefix $(OBJ_DIR), $(dir $(OBJ)))
OBJ = $(FILES:.cpp=.o)

INC_DIR = ./includes
INC = $(SRC)

DEPS_DIR = dep
SDL_DIR = $(DEPS_DIR)/SDL2-2.0.8
FREE_TYPE_DIR = $(DEPS_DIR)/freetype-2.9
SDL_LIB_DIR = $(SDL_DIR)/build/.libs
SDL_LIB = $(SDL_LIB_DIR)/libSDL2.a
SDL_INCLUDES = $(SDL_DIR)/include
SDL_MAC_FLAGS = -lSDL2 -framework Cocoa -framework CoreAudio\
  				-framework AudioToolbox -framework ForceFeedback\
 				-framework CoreVideo -framework Carbon -framework Metal -framework IOKit -liconv

all : $(NAME)

$(NAME) : install $(OBJ_DIR)
	echo "name rule"
	($(CC) $(FLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) -I$(INC) $(INCLUDE_LIBS) -L $(SDL_LIB_DIR) $(SDL_MAC_FLAGS) -I $(SDL_INCLUDES) -o $(NAME))
	echo "name rule2"
	(echo creation de $(NAME))

$(OBJ_DIR)%.o :
	$(addprefix $(SRC), %.cpp)
	($(CC) $(FLAG) $(SPE_FLAGS) -I $(SDL_INCLUDES) -I $(INC) -c $< -o $@)
	(echo $< " created")

$(OBJ_DIR) :
	echo "swag"
	mkdir -p $(OBJ_PATHS)

clean :
	@(rm -f $(addprefix $(OBJ_DIR), $(OBJ)))
	@(rm -rf $(OBJ_DIR))
	@(echo suppression des $(OBJ_DIR).o)

fclean : clean
	@(rm -f $(NAME))
	@(echo suppression de $(NAME))

re : fclean all

debug :
	@($(CC) $(DEBUG_FLAG) $(addprefix $(SRC), $(FILES)) -I$(INC) -o $(NAME))
	./$(NAME)

lanch : re
	./$(NAME)

install : $(SDL_LIB)

$(SDL_LIB):
	@printf "\r  Building SDL2...                   \r";
	@$(shell tar -xzf $(SDL_DIR).tar.gz -C $(DEPS_DIR))

	@printf "\r Building SDL2: SDL2 core...           \r";
	@cd $(SDL_DIR) && ./configure > /dev/null
	@make -C $(SDL_DIR) -j4 > /dev/null 2> /dev/null

	@printf "\r Building SDL2: Removing dylib...   \r";
	@rm -rf $(SDL_LIB_DIR)/libSDL2-2.0.0.dylib
	@printf "\r Building SDL2: DONE !                 \n";

uninstall : fclean
	@(rm -rf $(SDL_DIR))
