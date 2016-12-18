# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/25 09:52:13 by ybeaure           #+#    #+#              #
#    Updated: 2016/12/18 20:03:26 by ybeaure          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		corewar

FILES =	add_sub_and.c \
		aff.c \
		b_swap.c \
		base_operations.c \
		boot_vm.c \
		checks.c \
		exec.c \
		file_parsing.c \
		fork_lfork.c \
		get.c \
		init_champs.c \
		init_cycle.c \
		init_ram.c \
		ld_lld_st.c \
		ldi_lldi_sti.c \
		live.c \
		main.c \
		op.c \
		or_xor.c \
		others.c \
		search_and_destroy.c \
		start_fight.c \
		update_cycle.c \
		zjmp.c \

SRCS =		$(addprefix srcs/, $(FILES))

OBJS =		$(SRCS:.c=.o)

DEBUG =		-fsanitize=address

FLAGS =		-Wall -Werror -Wextra $(DEBUG)

CC =		gcc

all: libft/libft.a $(NAME)

libft/libft.a:
	make -C ./libft/

$(%.o): $(%.c)
	$(CC) $(FLAGS) -o $@ -c $^

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ -Llibft -lft

clean:
	@make -C ./libft/ clean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft/ fclean

re: fclean all clean

.PHONY: clean
