# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmancero <jmancero@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/22 22:10:13 by jmancero          #+#    #+#              #
#    Updated: 2014/10/19 10:44:37 by jmancero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	redis

SRCDIR		=	src
EXCLUDE_COMP =
OBJDIR		=	$(addprefix obj, $(shell find src -type d | sed 's/^src//' ))
SRCTYPE		=	.cpp

INCDIR 		=	inc/ `sdl2-config --cflags`

SRC			=	$(shell find $(SRCDIR) -type f | grep \.cpp )

OBJ			=	$(SRC:.cpp=.o)

CC 			=	g++



LINK =

CFLAGS 		= -g -std=c++11

FILE = 0

#-Wextra -Werror -Wall lib/glew/libGLEW.a

OBJFLAG =  -g  -g3 -fno-inline -O0 -Wextra -Werror -Wall

RED = \033[33;31m
BLUE = \033[33;34m
GREEN = \033[33;32m
RESET = \033[0m

.PHONY: all re fclean

all: $(NAME)


$(NAME): $(OBJ)
		@$(CC) -o $(NAME) $(CFLAGS) -I$(INCDIR) $(OBJ) $(LINK)
		@echo "[$(GREEN)Compilation $(BLUE)$(NAME) $(GREEN)ok$(RESET)]"

%.o:%.cpp
		@$(CC) -c -o $@ $(OBJFLAG) $^ -I$(INCDIR)


clean:
	@rm -f $(shell find $(SRCDIR) -type f | grep -v \.cpp | grep \.o)
	@echo "[$(RED)Supression des .o de $(BLUE)$(NAME) $(GREEN)ok$(RESET)]"

fclean: clean
		@rm -f $(NAME)
		@echo "[$(RED)Supression de $(BLUE)$(NAME) $(GREEN)ok$(RESET)]"

re: fclean all
