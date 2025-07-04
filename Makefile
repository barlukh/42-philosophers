# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/30 14:51:29 by bgazur            #+#    #+#              #
#    Updated: 2025/07/03 13:50:05 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo
CC =		cc
CFLAGS =	-Wall -Werror -Wextra
RM =		rm -f

INC_DIR =	include
OBJ_DIR =	objects
SRC_DIR =	src

HDR =		$(INC_DIR)/philosophers.h

OBJ =		$(SRC:%.c=$(OBJ_DIR)/%.o)

SRC =		lifecycle.c \
			main.c \
			parsing.c \
			routine.c

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ_DIR) $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
