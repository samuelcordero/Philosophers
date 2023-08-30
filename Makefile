# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 15:21:07 by sacorder          #+#    #+#              #
#    Updated: 2023/08/30 01:04:21 by sacorder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/libft.a
LDFLAGS = -L libft -lft
NAME = philosophers
CFLAGS = -Wall -Wextra -Werror -O3 #-g3 -fsanitize=address
INCLUDE = inc/philosophers.h 
SRC = src/main.c src/utils.c
OBJ = $(SRC:.c=.o)
UNAME := $(shell uname -s)
CC = gcc

all: $(NAME)

$(LIBFT):
	@make bonus -C ./libft

	
$(NAME): $(LIBFT) $(OBJ) $(INCLUDE) 
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@make clean -C ./libft
	$(RM) $(OBJ)

fclean: clean
	@make fclean -C ./libft
	$(RM) $(NAME)

re:: fclean
re:: all

asan:: CFLAGS += -fsanitize=address -g3
asan:: LDFLAGS += -fsanitize=address
asan:: re


normi:
	@norminette src inc libft

.PHONY: all clean fclean re normi
