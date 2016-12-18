/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:39:48 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/18 19:42:05 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op	g_op_tab[17];

void		get_p_code(unsigned char bit, char p_code[4])
{
	int		i;
	i = 4;
	while (--i >= 0)
	{
		p_code[i] = bit % 4;
		bit = bit >> 2;
	}
}

int			get_p_len(char p_code, char op_code)
{
	if (p_code == REG_CODE)
		return (1);
	if (p_code == DIR_CODE && g_op_tab[(int)op_code - 1].is_idx)
		return (IND_SIZE);
	if (p_code == DIR_CODE && g_op_tab[(int)op_code - 1].is_idx == 0)
		return (DIR_SIZE);
	if (p_code == IND_CODE)
		return (IND_SIZE);
	return (0);
}

int			get_p_val(int p_len, int p_val, t_vm *vm, int next_param_pc)
{
	int		i;

	i = -1;
	while (++i < p_len)
	{
		p_val = p_val << 8;
		p_val += vm->ram[(next_param_pc + i + MEM_SIZE) % MEM_SIZE].value;
	}
	return (p_val);
}

int			get_p_info(t_pro *pro, t_vm *vm, char p_code[4], int p_val[4])
{
	int		i;
	int		next_param_pc;
	int		p_len;

	next_param_pc = 1;
	if (g_op_tab[pro->curr_op - 1].is_p)
	{
		get_p_code(vm->ram[(pro->pc + 1) % MEM_SIZE].value, p_code);
		next_param_pc++;
	}
	else
		get_p_code(128, p_code);
	i = -1;
	while (++i < 4)
	{
		p_val[i] = 0;
		p_len = get_p_len(p_code[i], pro->curr_op);
		p_val[i] = get_p_val(p_len, p_val[i], vm, (pro->pc + next_param_pc) % MEM_SIZE);
		next_param_pc += p_len;
	}
	return ((next_param_pc) % MEM_SIZE);
}
