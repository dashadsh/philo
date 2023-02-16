# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/29 23:08:26 by dgoremyk          #+#    #+#              #
#    Updated: 2023/02/16 15:25:12 by dgoremyk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc 
CFLAGS = -g -pthread -Wall -Werror -Wextra -fsanitize=thread

RM = rm -f

SRC_PATH = src/
OBJ_PATH = obj/

SRC = main.c utils.c eat_sleep_think.c monitoring.c arg_check.c init.c mutex.c message.c simulation.c
# addprefix adds path so we can access to files
# when having files in a same folder could be used SRC=*.c
SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

DEPS = -I ./inc

all: $(NAME)

# creates /obj dir before compiling .o files
# compiles .c files into .o files, puts them in the /obj folder
# @mkdir -p flag to supress error if directory already exists
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@ $(DEPS)
	
# compiles all object files and builds executable file 'philo'
$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	@echo "$(NAME) compiled"
	@echo "expected input: ./philo int int int int (int)"
# CAN BE A PROBLEM ON LINUX: change to SRCS instead of objs
# UNCOMMENT 2 LINES BELOW:
#$(NAME): $(SRCS)
#	$(CC) $(SRCS) $(CFLAGS) -o $(NAME)

# removes all object files
# folder will be not deleted, @mkdir -p needed to avoid error mssg
clean: 
	@$(RM) $(OBJS)
	@echo ".o files deleted"

# calls 'clean', removes the executable
fclean: clean
	@$(RM) $(NAME)
	@echo "executable deleted"

# re-makes the whole compilation
re: fclean all

.PHONY: all clean fclean re