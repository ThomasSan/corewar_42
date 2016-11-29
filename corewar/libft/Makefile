SRCS	= ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memalloc.c ft_memccpy.c ft_memchr.c \
ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c \
ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c \
ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstiter.c ft_lstmap.c ft_lstadd.c \
ft_swap.c ft_memlen.c ft_pt_alloc.c ft_make_pt.c ft_make_pt3d.c ft_add_pt.c \
ft_add_pt3d.c ft_make_pt3df.c ft_add_pt3df.c ft_pt3d_alloc.c ft_make_ptll.c \
ft_add_ptll.c ft_make_ptd.c ft_add_ptd.c ft_lstline.c ft_make_ptd3d.c \
ft_add_ptd3d.c ft_power.c ft_strisdigit.c ft_memdel2.c ft_strisdouble.c \
ft_abs.c ft_atoi_base.c ft_ishexa.c ft_strishexa.c ft_putnstr.c ft_nblen.c \
ft_nblen_l.c ft_itoa_base.c ft_putnbr_l.c ft_itoa_base_l.c ft_binlen.c \
ft_upperstr.c ft_putnbr_ll.c ft_nblen_ll.c ft_itoa_base_ll.c ft_lowerstr.c \
ft_putwchar.c ft_atoi_nbase.c ft_putwstr.c ft_putnwstr.c ft_putnwchar.c \
ft_strwlen.c ft_charwlen.c ft_strnwlen.c ft_intdup.c ft_strrcmp.c \
ft_strrncmp.c ft_bswap.c

OBJS		= ft_atoi.o ft_bzero.o ft_isalnum.o ft_isalpha.o ft_isascii.o \
ft_isdigit.o ft_isprint.o ft_itoa.o ft_memalloc.o ft_memccpy.o ft_memchr.o \
ft_memcmp.o ft_memcpy.o ft_memdel.o ft_memmove.o ft_memset.o ft_putchar.o \
ft_putchar_fd.o ft_putendl.o ft_putendl_fd.o ft_putnbr.o ft_putnbr_fd.o \
ft_putstr.o ft_putstr_fd.o ft_strcat.o ft_strchr.o ft_strclr.o ft_strcmp.o \
ft_strcpy.o ft_strdel.o ft_strdup.o ft_strequ.o ft_striter.o ft_striteri.o \
ft_strjoin.o ft_strlcat.o ft_strlen.o ft_strmap.o ft_strmapi.o ft_strncat.o \
ft_strncmp.o ft_strncpy.o ft_strnequ.o ft_strnew.o ft_strnstr.o ft_strrchr.o \
ft_strsplit.o ft_strstr.o ft_strsub.o ft_strtrim.o ft_tolower.o ft_toupper.o \
ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstiter.o ft_lstmap.o ft_lstadd.o \
ft_swap.o ft_memlen.o ft_pt_alloc.o ft_make_pt.o ft_make_pt3d.o ft_add_pt.o \
ft_add_pt3d.o ft_make_pt3df.o ft_add_pt3df.o ft_pt3d_alloc.o ft_make_ptll.o \
ft_add_ptll.o ft_make_ptd.o ft_add_ptd.o ft_lstline.o ft_make_ptd3d.o \
ft_add_ptd3d.o ft_power.o ft_strisdigit.o ft_memdel2.o ft_strisdouble.o \
ft_abs.o ft_atoi_base.o ft_ishexa.o ft_strishexa.o ft_putnstr.o ft_nblen.o \
ft_nblen_l.o ft_itoa_base.o ft_putnbr_l.o ft_itoa_base_l.o ft_binlen.o \
ft_upperstr.o ft_putnbr_ll.o ft_nblen_ll.o ft_itoa_base_ll.o ft_lowerstr.o \
ft_putwchar.o ft_atoi_nbase.o ft_putwstr.o ft_putnwstr.o ft_putnwchar.o \
ft_strwlen.o ft_charwlen.o ft_strnwlen.o ft_intdup.o ft_strrcmp.o \
ft_strrncmp.o ft_bswap.o

GCC		= gcc

NAME	= libft.a

FT_PRINTF = ft_printf/ft_printf.a

FLAGS	= -Wextra -Werror -Wall

RM		= rm -f

all: $(NAME)

$(NAME): $(FT_PRINTF) $(OBJS)
	cp $(FT_PRINTF) $(NAME)
	ar r $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJS):
	$(GCC) $(FLAGS) -c -I./ $(SRCS)

$(FT_PRINTF):
	make -C ./ft_printf/

clean:
	$(RM) $(OBJS)
	make fclean -C ./ft_printf/

fclean: clean
	$(RM) $(NAME) $(FT_PRINTF)

re: fclean all

cc:
	clear

c: cc $(NAME)
