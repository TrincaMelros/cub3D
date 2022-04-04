# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 13:26:17 by fbarros           #+#    #+#              #
#    Updated: 2022/04/04 20:55:31 by fbarros          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS	+=	-s
#(https://www.gnu.org/software/make/manual/html_node/Options_002fRecursion.html)
# make -n for displaying commands but not running them

GREEN	= \033[0;32m
DEF = \033[0m

NAME = cub3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror

DEBUG = -g -DDEBUG_MODE

LIBS = -lm -L./libft -lft

INCLUDES = -Iinc/ -Imlx

SRCS = $(wildcard src/*.c)

RM = rm -f

FW = -framework AppKit -framework OpenGL

OBJ = $(SRCS:%.c=%.o)

LIBFT = libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBS) $(FW) -o $(NAME)
	echo "$(GREEN)[ cub3d COMPILED ]$(DEF)"

$(LIBFT):
	$(MAKE) -C libft
	echo "$(GREEN)[ libft COMPILED ]$(DEF)"

clean: 
	$(MAKE) clean -C libft
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) fclean -C libft
	$(RM) $(NAME)
	rm -rf *.dSYM

re: fclean all

debug: CFLAGS += $(DEBUG)
debug: re
memcheck: DEBUG += -fsanitize=address
memcheck: debug

.PHONY: all re clean fclean debug


# obj/ dir
# change libft makefile
# change gnl??