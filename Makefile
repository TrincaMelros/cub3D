# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 13:26:17 by fbarros           #+#    #+#              #
#    Updated: 2022/04/13 18:12:39 by fbarros          ###   ########.fr        #
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

LIBS = -lm -lmlx -Llibft -lft

INCLUDES = -Iinc -Imlx

SRCS = src/cub3d.c src/error.c src/gnl.c src/mem.c src/mlx_utils.c\
		src/map_parsing_utils.c src/map_parsing.c  src/utils.c\

RM = rm -f

MACFW = -framework AppKit -framework OpenGL

OBJ = $(SRCS:%.c=%.o)

LIBFT = libft/libft.a

DEBUG = -g -DDEBUG_MODE -Itest/

TESTSRCS = $(wildcard test/*.c)

TESTOBJ = $(TESTSRCS:%.c=%.o)

ifeq ($(shell uname), Darwin)
	LIBS += $(MACFW)
else ifeq ($(shell uname), Linux)
	LIBS += -lXext -lX11
endif

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBS) -o $(NAME)
	echo "$(GREEN)[ cub3d COMPILED ]$(DEF)"

$(LIBFT):
	@make -C ./libft
	echo "$(GREEN)[ libft COMPILED ]$(DEF)"

clean:
	$(MAKE) clean -C libft
	$(RM) $(OBJ) $(TESTOBJ)

fclean: clean
	$(MAKE) fclean -C libft
	$(RM) $(NAME) debug
	rm -rf *.dSYM

re: fclean all

debug: fclean
debug: NAME = debug
debug: CFLAGS += $(DEBUG)
debug: OBJ += $(TESTOBJ)
debug: $(TESTOBJ) all
memcheck: DEBUG += -fsanitize=address
memcheck: debug

.PHONY: all re clean fclean debug