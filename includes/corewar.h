/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 15:24:16 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/19 18:02:28 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/includes/ft_printf.h"

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			(4*1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','
# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16
# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC 0xea83f3

typedef struct			s_lst
{
	void				*data;
	size_t				data_size;
	struct s_lst		*next;
}						t_lst;

typedef struct			s_process
{
	struct s_vm			*vm;
	int					order;
	int					numero;
	char				reg[REG_NUMBER][REG_SIZE];
	struct s_champ		*c;

}						t_process;

typedef struct			s_champ
{
	int					dead;
	int					id;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	char				memory[CHAMP_MAX_SIZE + 1];
	unsigned int		size;
	int					pc_number;
	t_process			*first_pc;
}						t_champ;

typedef struct			s_vm
{
	t_champ				champ[MAX_PLAYERS];
	t_lst				*lst_champs;
	int					cycle_to_exec;
	int					o_graphic;
	int					cycle_to_die;
	int					print_live;
	int					nbr_champs;
	int					argc[16];
	int					size_arg[16];
	int					nbr_cycle[16];
	void				(*op_function[16])(t_process *pro, struct s_vm *vm, char **arg, char *type);
}						t_vm;

t_vm					*boot_vm(void);
t_process	*read_file_content(char *file, int number, t_vm *vm, int i);
//OTHERS
void		ft_error(char *str);
int			ft_isint(char *s_int, int *result);
//OP

void		op_add(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_aff(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_and(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_fork(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_lfork(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_ld(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_ldi(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_live(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_lld(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_lldi(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_or(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_xor(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_st(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_sti(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_sub(t_process *pro, t_vm *vm, char **arg, char *type);
void		op_zjmp(t_process *pro, t_vm *vm, char **arg, char *type);



#endif
