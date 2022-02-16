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
CFLAGS = -Wall -Wextra -Werror -lm -g
INC = inc/
FW = -framework AppKit -framework OpenGL
OBJ = $(SRC:c=o)
LIBFT = libft.a

%.o: %.c
	$(CC) $(CFLAGS) -Imlx $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) 

$(LIBFT):

clean: 
	rm $(OBJ)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
