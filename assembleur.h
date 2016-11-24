#ifndef ASSEMBLEUR_H
# define ASSEMBLEUR_H

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
	struct s_champ	*next;
}					t_champ;

#endif