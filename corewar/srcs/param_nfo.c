/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:09:16 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/02 12:26:30 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op		op_tab[17];

static void		get_p_code(unsigned char bit, char p_code[4])
{
	int		i;

	i = 4;
	while (--i >= 0)
	{
		p_code[i] = bit % 4;
		bit = bit >> 2;
	}
}

static int		get_p_len(char p_code, char op_code)
{
	if (p_code == REG_CODE)
		return (1);
	if (p_code == DIR_CODE && op_tab[(int)op_code - 1].is_idx == 1)
		return (IND_SIZE);
	if (p_code == DIR_CODE && op_tab[(int)op_code - 1].is_idx == 0)
		return (DIR_SIZE);
	if (p_code == IND_CODE)
		return (IND_SIZE);
	return (0);
}

static int		get_p_val(int p_len, int p_val, t_vm *vm, int param_pos)
{
	int		i;

	i = -1;
	while (++i < p_len)
	{
		p_val = p_val << 8;
		p_val = p_val + vm->ram[(param_pos + i + MEM_SIZE) % MEM_SIZE].value;
	}
	return (p_val);
}

int		get_p_nfo(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	int		i;
	int		param_pos;
	int		p_len;

	param_pos = 1;
	if (op_tab[pro->curr_op - 1].is_p)
	{
		get_p_code(vm->ram[(pro->pc + 1) % MEM_SIZE].value, p_code);
		param_pos++;
	}
	else
		get_p_code(128, p_code);
	i = -1;
	while (++i < 4)
	{
		p_val[i] = 0;
		p_len = get_p_len(p_code[i], pro->curr_op);
		p_val[i] = get_p_val(p_len, p_val[i], vm, (pro->pc + param_pos) % MEM_SIZE);
		param_pos = param_pos + p_len;
	}
	return ((param_pos) % MEM_SIZE);
}
