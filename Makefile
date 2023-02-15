# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/29 23:08:26 by dgoremyk          #+#    #+#              #
#    Updated: 2023/02/15 19:52:19 by dgoremyk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc 
CFLAGS = -g -pthread #-fsanitize=thread
#-Wall -Werror -Wextra

RM = rm -f
# rm -rf ???

SRC_PATH = src/
OBJ_PATH = obj/

SRC = main.c utils.c eat_sleep_think.c arg_check.c init.c mutex.c free.c message.c lone_philo.c
SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

#DEPS = inc/philo.h cannot specify -o when generating multiple output files
DEPS = -I ./inc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
#$@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(DEPS)
# @mkdir -p  - supress error if directory already exists
	
clean: 
	$(RM) $(OBJS)
# folder will be not deleted, @mkdir -p needed to avoid error mssg

fclean: clean
	$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re

#gcc -g -c src/main.c -o obj/main.o -I ./inc
#gcc -g -c src/utils.c -o obj/utils.o -I ./inc
#gcc -g -c src/error_check.c -o obj/error_check.o -I ./inc
#gcc obj/main.o obj/utils.o obj/error_check.o -g -o philo