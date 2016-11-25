#ifndef ASSEMBLEUR_H
# define ASSEMBLEUR_H

# define LABELS 100
# define OP 102
# define REG 103
# define DIR 104
# define IND 105

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
	struct s_champ	*next;
}					t_champ;

/*
** Parsing functions
*/
int					label_index(char *line);
int					get_op_code(char *str);
int					get_param_type(char *str);
int					params_types(char *str);
int					label_sizes(char *str);
void				calculate_address(t_champ *head);

#endif