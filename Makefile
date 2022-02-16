# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbarros <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 13:26:17 by fbarros           #+#    #+#              #
#    Updated: 2021/11/08 13:36:00 by fbarros          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror

DEBUG = -g

LIBS = -lm -L./libft -lft

INCLUDES = -I inc/ -Imlx

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

$(LIBFT):
	$(MAKE) -C libft

clean: 
	$(MAKE) clean -C libft
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) fclean -C libft
	$(RM) $(NAME)
	rm -rf *.dSYM

re: fclean all

.PHONY: all re clean fclean


# make quiet
# obj/ dir
# change libft makefile
# change gnl??