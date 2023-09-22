# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 15:21:07 by sacorder          #+#    #+#              #
#    Updated: 2023/09/22 15:11:56 by sacorder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
INCLUDE = inc
CFLAGS = -Wall -Wextra -Werror -O3 -I$(INCLUDE) -pthread
SRC = 	src/main.c \
		src/utils.c \
		src/time.c \
		src/philos.c \
		src/controller.c
OBJ = $(SRC:.c=.o)
CC = gcc

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE) 
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:: fclean
re:: all

asan:: CFLAGS += -fsanitize=address -g3
asan:: LDFLAGS += -fsanitize=address
asan:: re

tsan:: CFLAGS += -fsanitize=thread -g3
tsan:: LDFLAGS += -fsanitize=thread
tsan:: re

normi:
	@norminette src inc

.PHONY: all clean fclean re asan tsan normi
