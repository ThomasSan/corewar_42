# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdebelle <tsanzey@student.42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/01 18:33:59 by tsanzey           #+#    #+#              #
#    Updated: 2017/01/24 17:06:00 by tsanzey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = assembleur
SRC = main.c gnl.c parser.c conversion_tables.c int_to_hexa.c labels.c\
		validity.c params_converter.c get_program.c write_file.c binary.c\
		write2.c misc.c free.c arg_validity.c

OBJ = $(SRC:%.c=obj/%.o)

CXX = gcc
CXXFLAGS = -g -Wall -Werror -Wextra

INC = -I includes
LIB = libft/

all: $(NAME)

$(NAME): obj $(OBJ)
	@make -s -C $(LIB)
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(INC) -L$(LIB) -lft

obj/%.o: %.c
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $< -I$(LIB)

obj:
	mkdir -p obj/

clean:
	@rm -rf obj

fclean: clean
	@make clean -s -C $(LIB)
	@rm -rf $(NAME)

re: fclean all
	@make re -s -C $(LIB)

.PHONY: fclean all clean re
