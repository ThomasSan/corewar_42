/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:44:44 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/29 08:04:18 by ybeaure          ###   ########.fr       */
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

# define MAX_COR_SIZE	CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH

typedef struct	s_ram
{
	unsigned char	value;
	int				owner;
	bool			executed;
}				t_ram;

typedef struct	s_champ
{
	int				pos;
	int				number;
	int				color;
	t_header		header;
	unsigned char	data[MAX_COR_SIZE];
	int				len;
}				t_champ;

typedef struct	s_process
{
	int					pc;
	int					reg[REG_NUMBER];
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


void			(*exec_op[17])(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void			init_vm(t_vm *vm);
void			exit_corewar(t_vm *vm);
void			get_champ(t_vm *vm, t_champ *champ, char *path);

// PARSE / EXEC 
void		parse_exec_op(t_vm *vm, t_process *pro);
int		get_p_nfo(t_vm *vm, t_process *pro, char p_code[4], int p_val[4]);

// OP
void		ft_live(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_st(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_ld(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_and(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_sub(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_add(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_or(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_xor(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_ldi(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_lldi(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_sti(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_lld(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_lfork(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_fork(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_zjmp(t_vm *vm, t_process *pro, char p_code[4], int p_val[4]);
void		ft_aff(t_vm *vm, t_process *pro, char p_code[4], int p_val[4]);

int		check_params(char opcode, char p_code[4], int p_val[4]);

#endif
