# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/25 09:52:13 by ybeaure           #+#    #+#              #
#    Updated: 2016/11/25 12:56:13 by cchameyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRCS =	srcs/main.c \
		srcs/op.c \
		srcs/init_vm.c \
		srcs/exit_corewar.c \
		srcs/get_arg.c

OBJS = $(SRCS:.c=.o)

FLAG = -Wall -Werror -Wextra

CC = gcc $(FLAG)

all : libft/libft.a $(NAME)

libft/libft.a:
	make -C ./libft/

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME) : $(OBJS)
	$(CC) -o $@ $^ -Llibft -lft

clean :
	@make -C ./libft/ clean
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)
	@make -C ./libft/ fclean

re : fclean all clean

.PHONY: clean
