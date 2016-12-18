# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/12 18:01:23 by ybeaure           #+#    #+#              #
#    Updated: 2016/05/25 10:25:55 by ybeaure          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re

NAME	=	libft.a
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror

SDIR	=	./src/
IDIR	=	./includes/
ODIR	=	./obj/

I		=	-I $(IDIR)

EXT		=	Makefile
EXT		+=	$(IDIR)libft.h

SRC=ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
	ft_memmove.c ft_memchr.c ft_memcmp.c \
	ft_strstr.c ft_strlen.c ft_strdup.c ft_strcpy.c \
	ft_strncpy.c ft_strcat.c ft_strncat.c \
	ft_putstr_fd.c ft_strchr.c ft_strlcat.c ft_strrchr.c \
	ft_strcmp.c ft_strncmp.c ft_strstr.c ft_strnstr.c ft_atoi.c \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_striter.c ft_striteri.c ft_putendl.c ft_toupper.c ft_tolower.c \
	ft_strsub.c ft_strclr.c ft_memdel.c ft_strnew.c ft_strdel.c \
	ft_strequ.c ft_strnequ.c ft_memalloc.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_putchar.c ft_putstr.c ft_putnbr.c ft_putchar_fd.c \
	ft_itoa.c ft_strsplit.c ft_strjoin.c ft_strtrim.c \
	ft_lstdelone.c ft_lstnew.c ft_strmap.c ft_strmapi.c \
	ft_putendtb.c ft_putendsp.c get_next_line.c \
	ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
	ft_freejoin.c ft_lstadd_end.c \
	ft_ishexa.c ft_isspace.c \

OBJ		=	$(SRC:.c=.o)
	S		=	$(addprefix $(SDIR), $(SRC))
	O		=	$(addprefix $(ODIR), $(OBJ))

all: $(NAME)

test: all
	@$(CC) $(FLAGS) test/main.c -o test/test $I -L. -lft
	@./test/test

creating:
	@echo " - compiling sources\c"

$(NAME): creating $(O) $(EXT)
	@echo "\n - Creating library..."
	@ar rc $(NAME) $(O)
	@echo " - Optimizing..."
	@ranlib $(NAME)
	@echo "libft done."


$(ODIR)%.o: $(SDIR)%.c $(EXT)
	@echo ".\c"
	@$(CC) $(FLAGS) -c -o $@ $< $(I)

$(O): | $(ODIR)
$(ODIR):
	@mkdir $(ODIR)

clean:
	@echo "cleaning object files..."
	@rm -rf $(ODIR)

fclean: clean
	@echo "cleaning $(NAME) binary..."
	@rm -rf $(NAME)

re: fclean all
