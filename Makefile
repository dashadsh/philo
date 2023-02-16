# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/29 23:08:26 by dgoremyk          #+#    #+#              #
#    Updated: 2023/02/16 15:04:23 by dgoremyk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc 
CFLAGS = -g -pthread -Wall -Werror -Wextra -fsanitize=thread

RM = rm -f

SRC_PATH = src/
OBJ_PATH = obj/

SRC = main.c utils.c eat_sleep_think.c monitoring.c arg_check.c init.c mutex.c message.c simulation.c
SRCS = $(addprefix $(SRC_PATH), $(SRC))
# addprefix adds path so we can access to files

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

DEPS = -I ./inc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
#linux sources instead of objs error

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(DEPS)
# @mkdir -p flag to supress error if directory already exists
	
clean: 
	$(RM) $(OBJS)
# folder will be not deleted, @mkdir -p needed to avoid error mssg

fclean: clean
	$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re