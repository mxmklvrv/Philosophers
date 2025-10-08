# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 17:02:31 by mklevero          #+#    #+#              #
#    Updated: 2025/10/08 14:50:34 by mklevero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc 
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj/
SRC_DIR = src/

HEADERS = -I ./include
PHILO_HEAD = ./include/philo.h

SRC = main.c utils.c

OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
.SECONDARY: $(OBJS)

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(PHILO_HEAD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(PHILO_HEAD)
	$(CC) $(OBJS)  $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

