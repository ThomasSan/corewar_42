# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/19 15:16:40 by ybeaure           #+#    #+#              #
#    Updated: 2017/01/02 16:37:06 by ybeaure          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		corewar

FILES =		main.c \
			boot.c \
			check_args.c \
			display.c \
			display_tools.c \
			exec.c \
			create.c \
			casts.c \
			find.c \
			place.c \
			read_file_content.c \
			tools.c \
			tools2.c \
			tools3.c \
			op_add.c\
			op_aff.c\
			op_and.c\
			op_fork.c\
			op_ld.c\
			op_ldi.c\
			op_live.c\
			op_lld.c\
			op_lldi.c\
			op_or.c\
			op_st.c\
			op_sti.c\
			op_sub.c\
			op_xor.c\
			op_zjmp.c\
			start_fight.c \
			switch.c \

SRCS =		$(addprefix srcs/, $(FILES))

OBJS =		$(SRCS:.c=.o)

DEBUG =		-fsanitize=address

GFLAG =		-lncurses

FLAGS =		-Wall -Werror -Wextra -g

CC =		gcc

all: libft/libft.a $(NAME)

libft/libft.a:
	make -C ./libft/

$(%.o): $(%.c)
	$(CC) $(FLAGS) -o $@ -c $^

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ -Llibft -lft $(GFLAG)

clean:
	@make -C ./libft/ clean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft/ fclean

re: fclean all clean

.PHONY: clean
