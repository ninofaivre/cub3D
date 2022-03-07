# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 10:25:16 by nfaivre           #+#    #+#              #
#    Updated: 2022/03/07 13:34:05 by nfaivre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL = all

NAME = cub3D

CC = clang
CFLAGS = -Wall -Wextra -Werror

VPATH =
DIR_SRC = src
DIR_OBJ = .obj

LIB = -lm
INCLUDE = -Iinclude

SRC = $(wildcard $(DIR_SRC)/*/*.c)
OBJ = $(addprefix $(DIR_OBJ)/, $(notdir $(SRC:.c=.o)))
GNL_OBJ = $(DIR_OBJ)/get_next_line*

mkdir_DIR_OBJ:
	mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o : $(DIR_SRC)/*/%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE) $(LIB)

$(NAME):
	make -C Get-Next-Line DIR_OBJ=$(addprefix $(PWD)/, $(DIR_OBJ))
	$(CC) $(CFLAGS) $(OBJ) $(GNL_OBJ) -o $(NAME)

all: mkdir_DIR_OBJ $(OBJ) $(NAME)

clean:
	make $@ -C Get-Next-Line DIR_OBJ=$(addprefix $(PWD)/, $(DIR_OBJ))
	rm -f $(OBJ)

fclean: clean
	make $@ -C Get-Next-Line DIR_OBJ=$(addprefix $(PWD)/, $(DIR_OBJ))
	rm -f $(NAME)
	rm -rf $(DIR_OBJ)

re: fclean all

.PHONY: all clean fclean re
