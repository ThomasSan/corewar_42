/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:44:44 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/25 10:19:05 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# include "../libft/libft.h"
# include "op.h"

typedef struct	s_ram
{
	unsigned char	value;
	int				owner;
	int				executed;
}				t_ram;

typedef struct	s_champ
{
	int			pc;
	int			number;
	header_t	header;
}				t_champ;

typedef struct	s_process
{
	int			pc;
}

typedef struct	s_vm
{
	t_champ		*champs;
	int			nb_champ;
}				t_vm;

# include "debug.h"

#endif
