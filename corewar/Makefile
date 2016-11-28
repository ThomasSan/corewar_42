# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/25 09:52:13 by ybeaure           #+#    #+#              #
#    Updated: 2016/11/28 17:39:48 by ybeaure          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		corewar

FILES =		main.c \
			add_sub_and.c \
			aff.c \
			exit_corewar.c \
			fork_lfork.c \
			get_chmps.c \
			init_vm.c \
			ld_lld_st.c \
			ldi_lldi_sti.c \
			live.c \
			op.c \
			or_xor.c \
			param_nfo.c \
			parse_exec_op.c \
			zjmp.c \

SRCS =		$(addprefix srcs/, $(FILES))

OBJS =		$(SRCS:.c=.o)

FLAGS =		-Wall -Werror -Wextra

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
