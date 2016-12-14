#ifndef ASSEMBLEUR_H
# define ASSEMBLEUR_H

# define LABELS 100
# define OP 102
# define REG 103
# define DIR 104
# define IND 105
# define NAME 106
# define COMMENT 107

#include "get_next_line.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct		s_labels
{
	int				address;
	char			*name;
	struct s_labels	*next;
}					t_labels;

typedef struct		s_champ
{
	char			*line;
	int				address;
	int				type;
	int				value;
	int				encoding;
	int				len;
	char			*hex_value;
	struct s_champ	*next;
}					t_champ;

typedef struct		s_prog
{
	char			*file;
	char			*magic;
	char			*name;
	int				size;
	char			*comment;
	char			*program;
}					t_prog;

/*
** Parsing functions
*/
int					label_index(char *line);
int					get_op_code(char *str);
int					get_param_type(char *str);
int					params_types(char *str);
int					label_sizes(char *str);
void				calculate_address(t_champ *head);
void				calculate_value(t_champ *head, t_labels *labels);
int					index_of(char *str, char c);

/*
** Conversion Functions
*/
char				*str_itobase(int nb, int base);
char				*neg_itobase(int nb);
int					binary_todec(char *bin);

t_labels 			*parsing_champ(t_champ *head);
void				display_labels(t_labels *head);

#endif