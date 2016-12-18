/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 21:00:01 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 19:04:11 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <stdlib.h>
# include <ncurses.h>
# include "op.h"
# include "../libft/includes/libft.h"

#define BUFF_SIZE 256

typedef struct		s_ram
{
	unsigned char	value;
	int				champ;
	int				execute;
}					t_ram;

typedef struct		s_champs
{
	int				position;
	int				number;
	int				len;
	t_header		header;
	char			*color;
	unsigned char	*data;
}					t_champs;

typedef struct		s_vm
{
	unsigned int	dump_cycle;
	int				o_dump;
	int				o_graphic;
	int				nbr_live;
	short			nbr_champs;
	int				last_to_live;
	char			**av;
	t_ram			*ram;
	t_champs		*champs;
	t_cycle			*cycle;
}					t_vm;
//ERROR
void			ft_error(char *str);

//BOOT
t_vm			*boot_vm(t_vm *vm, int ac, char **av);

//OTHERS
char			**ft_arrsub(char **src, unsigned int start, unsigned int len);
int				array_size(char **array);
char	*ft_strrev(char *s);

//INIT
t_champs		*init_champs(t_vm *vm);
t_ram			*init_ram(void);
//PLACE
void			put_champs_on_map(t_vm **vm);
//READ
void			read_header(unsigned char *data, t_champs *champs);
void			read_prog(unsigned char *data, t_champs *champs);
unsigned char	*read_file(char *fn, t_champs *champs);
//BSWAP
unsigned short	bswap_16(unsigned short value);
unsigned int	bswap_32(unsigned int value);
//START
void	start_fight(t_vm *vm);
//COUNT
int			count_champs(t_vm *vm);
void			(*g_exec_op[17])(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
//OP
void		ft_live(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_st(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_ld(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_and(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_sub(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_add(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_or(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_xor(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_ldi(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_lldi(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_sti(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_lld(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_lfork(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_fork(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_zjmp(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);
void		ft_aff(t_vm *vm, t_pro *pro, char p_code[4], int p_val[4]);

//CYCLE
void			init_cycle(t_cycle *cycle, t_vm *vm);
int		update_cycle(t_cycle *cycle, t_vm *vm);
//SEARCH_AND_DESTROY
t_pro	*find_dead_pro(t_pro **pro);
void		kill_pro(t_pro *pro, t_vm *vm);
//CONVERT
char		*ft_base16(unsigned char number);
//EXEC
void		exec_pro(t_pro **pro, t_vm *vm);
//CHECKS
int				get_new_p_val(t_pro *pro, t_vm *vm, int p_val, int p_code);
int			get_new_lp_val(t_pro *pro, t_vm *vm, int p_val, int p_code);
int				check_params(char opcode, char p_code[4], int p_val[4]);
//GET
int			get_p_len(char p_code, char op_code);
int			get_p_info(t_pro *pro, t_vm *vm, char p_code[4], int p_val[4]);


#endif
