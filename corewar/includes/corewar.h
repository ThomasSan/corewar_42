/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:44:44 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/25 12:55:14 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# include "debug.h" //pas a la norme

# include "../libft/libft.h"
# include "op.h"

typedef struct	s_ram
{
	unsigned char	value;
	int				owner;
	bool			executed;
}				t_ram;

typedef struct	s_champ
{
	int			pos;
	int			number;
	int			color;
	t_header	header;
}				t_champ;

typedef struct	s_process
{
	int					pc;
	int					curr_op;
	bool				carry;
	struct s_process	*next;
}				t_process;

typedef struct	s_cycle
{
	int		cycles;
}				t_cycle;

typedef struct	s_vm
{
	t_champ		*champs;
	t_ram		*ram;
	int			nb_champ;
	bool		option_graph;
}				t_vm;


void			init_vm(t_vm *vm);

int				get_arg(t_vm *vm);

void			exit_corewar(t_vm *vm);

#endif
