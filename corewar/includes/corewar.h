/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:44:44 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/30 16:17:32 by cchameyr         ###   ########.fr       */
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

# define MAX_COR_SIZE		CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH

# define CARRY_ON_START		1

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
	int				reg[REG_NUMBER];
	unsigned char	data[CHAMP_MAX_SIZE];
	int				len;
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
	int		cycle_to_die;
	int		cycle_delta;
	int		nbr_live;
	int		max_checks;
}				t_cycle;

typedef struct	s_vm
{
	t_champ		*champs;
	t_process	*process;
	t_ram		*ram;
	t_cycle		cycle;
	int			nb_champ;
	bool		option_graph;
}				t_vm;


void			(*exec_op[17])(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void			init_vm(t_vm *vm);
void			init_start(t_vm *vm);
void			exit_corewar(t_vm *vm);
void			exit_corewar_msg(t_vm *vm, char *msg);
void			get_champ(t_vm *vm, t_champ *champ, char *path);

void			add_process(t_process **p, int pc, int curr_op, int carry);
void			free_process(t_process **p);

// DEBUG DISPLAYER
void			display_debug_champ(t_champ *champs, int number);
void			display_debug_ram(t_ram *ram);
void			display_debug_reg(int reg[REG_NUMBER]);

// PARSE / EXEC 
void		parse_exec_op(t_vm *vm, t_process *pro);
int		get_p_nfo(t_vm *vm, t_process *pro, char p_code[4], int p_val[4]);

// OP
void		ft_live(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_st(t_vm *vm, t_process *pro, char p_code[4], int p_val[4]);
void		ft_ld(t_vm *vm, t_process *pro, char p_code[4], int p_val[4]);
void		ft_and(t_vm *vm, t_process *pro, char p_code[4], int p_val[4]);
void		ft_sub(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_add(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_or(t_vm *vm, t_process *pro, char p_code[4], int p_val[4]);
void		ft_xor(t_vm *vm, t_process *pro, char p_code[4], int p_val[4]);
void		ft_ldi(t_vm *vm, t_process *pro, char p_code[4], int p_val[4]);
void		ft_lldi(t_vm *vm, t_process *pro, char p_code[4], int p_val[4]);
void		ft_sti(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_lld(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_lfork(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_fork(t_vm *vm, t_process *pr, char p_code[4], int p_val[4]);
void		ft_zjmp(t_vm *vm, t_process *pro, char p_code[4], int p_val[4]);
void		ft_aff(t_vm *vm, t_process *pro, char p_code[4], int p_val[4]);

int		check_params(char opcode, char p_code[4], int p_val[4]);
int		get_new_p_val(t_vm *vm, t_process *pro, char p_code, int p_val);

#endif
